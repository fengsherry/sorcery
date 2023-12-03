#include <variant>
#include "player.h"
#include "exceptions.h"
#include "activatedability.h"
#include "triggeredability.h"
using namespace std;

Player::Player() {}

// Player::Player(string name, int id) : name{name}, id{id} {}

Player::~Player() {}

void Player::init(string name, int id, ifstream& deckIn) {
    this->name = name;
    this->id = id;
    deck.init(deckIn, this);
    hand.init(deck);
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
    if (life <= 0) cout << this->getName() << " is dead D:" << endl; 
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

TriggeredAbility* Player::play(int i, Player& nonActivePlayer) {
    CardPtr cardToPlay = hand.getCard(i);

    // check if the card can be played without target
    if (cardToPlay->getNeedTarget() == true) throw no_target_provided(*cardToPlay);
    
    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (cost > magic) throw not_enough_magic(*this); // why *this not this

    magic -= cost;

    if (cardToPlay->getType() == CardType::Minion) {
        MinionPtr minionToPlay = dynamic_pointer_cast<Minion>(cardToPlay); // fails if cardToPlay is not MinionPtr type
        board.addCard(minionToPlay);
    } else if (cardToPlay->getType() == CardType::Ritual) {
        RitualPtr ritualToPlay = dynamic_pointer_cast<Ritual>(cardToPlay);
        // cout << "this is not a minion" << endl;
        ritual = ritualToPlay;
    } else if (cardToPlay->getType() == CardType::Spell) {
        SpellPtr spellToPlay = dynamic_pointer_cast<Spell>(cardToPlay);
        spellToPlay->applyAbility(*this, nonActivePlayer);
    }
    return nullptr;
}

// with target
void Player::play(int i, int j, Player& p) {
    CardPtr cardToPlay = hand.getCard(i);
    CardPtr targetCard = p.getBoard().getCard(j);

    // check if the card needs a target to be played
    if (cardToPlay->getNeedTarget() == false) throw no_target_needed(*cardToPlay);

    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (cost > magic) throw not_enough_magic(*this);

    magic -= cost;
    
    if (EnchantmentPtr enchantToPlay = dynamic_pointer_cast<Enchantment>(cardToPlay)) { // enchantment
        if (MinionPtr targetMinion = dynamic_pointer_cast<Minion>(targetCard)) {         
            // enchant the minion. Note the conversion from Enchantment (Card) to EnchantmentDec (Decorator)
            p.getBoard().enchantMinion(j, enchantToPlay->getName());

        } else { throw invalid_play{"You cannot play " + cardToPlay->getName() + " on " + targetCard->getName()}; }
    } else if (SpellPtr spellToPlay = dynamic_pointer_cast<Spell>(cardToPlay)) { // spell with target
        spellToPlay->applyAbility(p, *this, j); // might be sus - *this is a dummy value - should be nullptr but that means the argument needs to be a pointer, will do later if have time
    }
}

void Player::useAbility(int i, Player& nonActivePlayer) {
    MinionPtr minionToUse = dynamic_pointer_cast<Minion>(board.getCard(i));
    
    try {
        // check if minion has an activated ability
        ActivatedAbility* aaToUse = get<ActivatedAbility*>(minionToUse->getAbility());
        // check if ability can be used without target
        if (aaToUse->getNeedTarget()) throw no_target_provided(*minionToUse);
        // check if player has enough action
        if (minionToUse->getAction() == 0) throw not_enough_action{*this}; 
        // check if player has enough magic to play the card
        int cost = aaToUse->getActivationCost();
        if (cost > magic) throw not_enough_magic(*this);
        magic -= cost;

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
        if (minionToUse->getAction() == 0) throw not_enough_action{*this}; 
        // check if player has enough magic to play the card
        int cost = aaToUse->getActivationCost();
        if (cost > magic) throw not_enough_magic(*this);
        magic -= cost;

        // use the ability
        aaToUse->applyAbility(p, *this, j);
    } catch (bad_variant_access&) {
        throw invalid_play(minionToUse->getName() + " has no activated ability");
    }

}
