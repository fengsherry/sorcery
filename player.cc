#include <variant>
#include "player.h"
#include "exceptions.h"
#include "activatedability.h"
#include "triggeredability.h"
using namespace std;

Player::Player() {}

// Player::Player(string name, int id) : name{name}, id{id} {}

Player::~Player() {}

void Player::init(string name, int id, ifstream& deckIn, vector<TriggeredAbility*>* boardObservers) {
    this->name = name;
    this->id = id;
    deck.init(deckIn, this);
    hand.init(deck);
    board.init(boardObservers);
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

    if (Minion* minionToPlay = dynamic_cast<Minion*>(cardToPlay)) { // false if cardToPlay is not Minion* type
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

