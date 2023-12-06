#include <variant>
#include "player.h"
#include "exceptions.h"
#include "activatedability.h"
#include "triggeredability.h"
using namespace std;

Player::Player() {}

// Player::Player(string name, int id) : name{name}, id{id} {}

Player::~Player() {}

void Player::init(string name, int id, ifstream& deckIn, observersList* ol, bool testing) {
    this->name = name;
    this->id = id;
    this->testing = testing;
    deck.init(deckIn, this, !testing); // if testing is on, set random field to false
    hand.init(deck);
    board.init(ol, &grave);
}

void Player::TEST_printPlayerDeck() {
    cout << "Player " << id << " " << name << "'s Deck: " << endl;
    deck.TEST_printDeck();
    cout << endl;
}

void Player::TEST_printPlayerHand() {
    cout << "Player " << id << " " << name << "'s Hand: " << endl;
    hand.TEST_printHand();
    cout << endl;
}

void Player::TEST_printPlayerBoard() {
    cout << "Player " << id << " " << name << "'s Board: " << endl;
    board.TEST_printBoard();

    TEST_printPlayerRitual();

    TEST_printPlayerGrave();

    TEST_printPlayerHand();
    cout << endl;
}

void Player::TEST_printPlayerRitual() {
    cout << "Player " << id << " " << name << "'s Ritual: " << endl;
    ritual->printRitual();
    cout << endl;
}

void Player::TEST_printPlayerGrave() {
    cout << "Player " << id << " " << name << "'s Graveyard: " << endl;
    grave.TEST_printGrave();
    cout << endl;
}

string Player::getName() const {return name;}
int Player::getId() const {return id;}
int Player::getLife() const {return life;}
int Player::getMagic() const {return magic;}

Hand& Player::getHand() {return hand;}
size_t Player::getHandSize() {return hand.getSize();}
Board& Player::getBoard() {return board;}
RitualPtr Player::getRitual() {return ritual;}
Graveyard& Player::getGrave() {return grave;}


void Player::setLife(int n) {life = n;}
void Player::setMagic(int n) {magic = n;}
void Player::increaseMagic(int n) {magic += n;}
void Player::decreaseLife(int n) {
    life -= n;

    // checks if player is still alive
    if (life <= 0) throw game_over(this);
    // we should throw an exception here
}

void Player::increaseLife(int n) {life += n;}

void Player::destroyRitual() {
    RitualPtr temp = ritual; // will go out of scope after method goes out of scope
    ritual = nullptr;
}

CardPtr Player::drawCard() {
    if (deck.getSize() == 0) throw deck_empty(this);
    CardPtr c = deck.drawCard();
    hand.addCard(c);
    return c;
}

void Player::removeTrigger(TriggeredAbility* ta) {
    // TriggerType tt = ta->getType();
    // if (tt == TriggerType::MinionEnter || tt == TriggerType::MinionLeave) board.detach(ta);
    
    // else throw detach_game_observer(ta);
    board.detach(ta);
}

// without target
TriggeredAbility* Player::play(int i, Player& nonActivePlayer) {
    CardPtr cardToPlay = hand.getCard(i);

    // check if the card can be played without target
    if (cardToPlay->getNeedTarget() == true) throw no_target_provided(*cardToPlay);
    
    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (!testing && cost > magic) throw not_enough_magic(*this); // why *this not this
    else if (testing && cost > magic) magic = 0;
    else magic -= cost;

    if (MinionPtr minionToPlay = dynamic_pointer_cast<Minion>(cardToPlay)) { // false if cardToPlay is not Minion* type
        board.addCard(minionToPlay);

        // determine if minion has a triggered ability, return the ta if it does
        auto a = minionToPlay->getAbility();
        if (holds_alternative<TriggeredAbility*>(a) && 
        (get<TriggeredAbility*>(a)->getType() == TriggerType::StartTurn || 
        get<TriggeredAbility*>(a)->getType() == TriggerType::EndTurn)) 
            return(get<TriggeredAbility*>(a));

    } else if (cardToPlay->getType() == CardType::Ritual) {
        RitualPtr ritualToPlay = dynamic_pointer_cast<Ritual>(cardToPlay);
        // cout << "this is not a minion" << endl;

        // remove old triggered ability if we are replacing a ritual
        if (ritual) {
            TriggeredAbility* ta = ritual->getAbility();
            ritual = nullptr;
            removeTrigger(ta);            
        }

        ritual = ritualToPlay;
        return ritualToPlay->getAbility();
    } else if (cardToPlay->getType() == CardType::Spell) {
        SpellPtr spellToPlay = dynamic_pointer_cast<Spell>(cardToPlay);
        spellToPlay->applyAbility(*this, nonActivePlayer);
    }
    return nullptr;
}

// with target
TriggeredAbility* Player::play(int i, int j, Player& p, bool targetRitual) {
    if (targetRitual) j =-1;
    CardPtr cardToPlay = hand.getCard(i);
    CardPtr targetCard;
    if (targetRitual) targetCard = p.getRitual();
    else targetCard = p.getBoard().getCard(j);

    // check if the card needs a target to be played
    if (cardToPlay->getNeedTarget() == false) throw no_target_needed(*cardToPlay);

    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (!testing && cost > magic) throw not_enough_magic(*this); // why *this not this
    else if (testing && cost > magic) magic = 0;
    else magic -= cost;
    
    if (EnchantmentPtr enchantToPlay = dynamic_pointer_cast<Enchantment>(cardToPlay)) { // enchantment
        if (MinionPtr targetMinion = dynamic_pointer_cast<Minion>(targetCard)) {         
            // enchant the minion. Note the conversion from Enchantment (Card) to EnchantmentDec (Decorator)
            // check if the enchantment contains a trigger
            // TriggeredAbility* a = p.getBoard().enchantMinion(j, enchantToPlay->getName());
            // if (a) return a;
  
        } else { throw invalid_play{"You cannot play " + cardToPlay->getName() + " on " + targetCard->getName()}; }
    } else if (SpellPtr spellToPlay = dynamic_pointer_cast<Spell>(cardToPlay)) { // spell with target
        spellToPlay->applyAbility(p, *this, j); 
    }
    return nullptr;
}

void Player::useAbility(int i, Player& nonActivePlayer) {
    MinionPtr minionToUse = dynamic_pointer_cast<Minion>(board.getCard(i));
    
    try {
        // check if minion has an activated ability
        ActivatedAbility* aaToUse = get<ActivatedAbility*>(minionToUse->getAbility());
        // check if ability can be used without target
        if (aaToUse->getNeedTarget()) throw no_target_provided(*minionToUse);
        // check if player has enough action
        if (minionToUse->getAction() == 0) throw not_enough_action{*this, minionToUse}; 
        // check if player has enough magic to play the card
        int cost = aaToUse->getActivationCost();
        if (!testing && cost > magic) throw not_enough_magic(*this); // why *this not this
        else if (testing && cost > magic) magic = 0;
        else magic -= cost;

        // use the ability
        aaToUse->applyAbility(*this, nonActivePlayer);
    } catch (bad_variant_access&) {
        throw invalid_play(minionToUse->getName() + " has no activated ability");
    }

    // check if activated ability can be 
}

void Player::useAbility(int i, int j, Player &p) {
    MinionPtr minionToUse = dynamic_pointer_cast<Minion>(board.getCard(i));

    try {
        // check if minion has an activated ability
        ActivatedAbility* aaToUse = get<ActivatedAbility*>(minionToUse->getAbility());
        // check if ability can be played on a target
        if (!aaToUse->getNeedTarget()) throw no_target_needed(*minionToUse);
        // check if player has enough action
        if (minionToUse->getAction() == 0) throw not_enough_action{*this, minionToUse}; 
        // check if player has enough magic to play the card
        int cost = aaToUse->getActivationCost();
        if (!testing && cost > magic) throw not_enough_magic(*this); // why *this not this
        else if (testing && cost > magic) magic = 0;
        else magic -= cost;

        // use the ability
        aaToUse->applyAbility(p, *this, j);
    } catch (bad_variant_access&) {
        throw invalid_play(minionToUse->getName() + " has no activated ability");
    }

}

bool Player::onBoard(MinionPtr m) {
    return board.contains(m);
}



