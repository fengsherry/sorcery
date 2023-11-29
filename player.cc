#include "player.h"
#include "exceptions.h"

Player::Player() {
    name = "DEFAULT PLAYER";
    id = 0;
}

// Player::Player(string name, int id) : name{name}, id{id} {}

Player::~Player() {}

void Player::init(string name, int id, ifstream& deckIn) {
    this->name = name;
    this->id = id;
    deck.init(deckIn);
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

string Player::getName() const {return name;}
int Player::getId() const {return id;}
int Player::getLife() const {return life;}
int Player::getMagic() const {return magic;}

Hand& Player::getHand() {return hand;}
Board& Player::getBoard() {return board;}
Ritual* Player::getRitual() {return ritual;}


void Player::setLife(int n) {life = n;}
void Player::setMagic(int n) {magic = n;}
void Player::increaseMagic(int n) {magic += n;}
void Player::decreaseLife(int n) {
    life -= n;

    // checks if player is still alive
    if (life <= 0) cout << this->getName() << " is dead D:" << endl; 
    // we should throw an exception here
}

void Player::destroyRitual() {
    Ritual* temp = ritual; // will go out of scope after method goes out of scope
    ritual = nullptr;
}

Card* Player::drawCard() {
    Card* c = deck.drawCard();
    hand.addCard(c);
    return c;
}

// without target
void Player::play(int i) {
    Card* cardToPlay = hand.getCard(i);

    // check if the card can be played without target
    if (cardToPlay->getNeedTarget() == true) throw no_target_provided(*cardToPlay);
    
    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (cost > magic) throw not_enough_magic(*this);

    magic -= cost;

    if (Minion* minionToPlay = dynamic_cast<Minion*>(cardToPlay)) { // false if cardToPlay is not Minion* type
        board.addCard(minionToPlay);
    } else if (Ritual* ritualToPlay = dynamic_cast<Ritual*>(cardToPlay)) {
        ritual = ritualToPlay;
    } else if (Spell* spellToPlay = dynamic_cast<Spell*>(cardToPlay)) {
        spellToPlay->applyAbility(*this);
    }
}

// with target
void Player::play(int i, int j, Player& p) {
    Card* cardToPlay = hand.getCard(i);
    Card* targetCard = p.getBoard().getCard(j);

    // check if the card needs a target to be played
    if (cardToPlay->getNeedTarget() == false) throw no_target_needed(*cardToPlay);

    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (cost > magic) throw not_enough_magic(*this);

    magic -= cost;
    
    if (Enchantment* enchantToPlay = dynamic_cast<Enchantment*>(cardToPlay)) { // enchantment
        if (Minion* targetMinion = dynamic_cast<Minion*>(targetCard)) {         
            // enchant the minion. Note the conversion from Enchantment (Card) to EnchantmentDec (Decorator)
            p.getBoard().enchantMinion(j, enchantToPlay->getName());

        } else { throw invalid_play{"You cannot play " + cardToPlay->getName() + " on " + targetCard->getName()}; }
    } else if (Spell* spellToPlay = dynamic_cast<Spell*>(cardToPlay)) { // spell with target
        spellToPlay->applyAbility(p);
    }
}

