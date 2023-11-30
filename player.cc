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
Ritual* Player::getRitual() {return ritual;}
Graveyard& Player::getGrave() { return grave; }


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

Card* Player::drawCard() {
    if (deck.getSize() == 0) throw deck_empty(this);
    Card* c = deck.drawCard();
    hand.addCard(c);
    return c;
}

TriggeredAbility* Player::play(int i) {
    Card* cardToPlay = hand.getCard(i);

    // check if the card can be played without target
    if (cardToPlay->getNeedTarget() == true) throw no_target_provided(*cardToPlay);
    
    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (cost > magic) throw not_enough_magic(*this); // why *this not this

    magic -= cost;

    if (cardToPlay->getType() == CardType::Minion) {
        Minion* minionToPlay = dynamic_cast<Minion*>(cardToPlay); // fails if cardToPlay is not Minion* type
        board.addCard(minionToPlay);
    } else if (Ritual* ritualToPlay = dynamic_cast<Ritual*>(cardToPlay)) {
        ritual = ritualToPlay;
        return ritual->getAbility();
    } else if (Spell* spellToPlay = dynamic_cast<Spell*>(cardToPlay)) {
        spellToPlay->applyAbility(*this);
    }
    return nullptr;
}

void Player::play(int i, int j, Player& p) {
    Card* cardToPlay = hand.getCard(i);
    Card* targetCard = p.getBoard().getCard(j);

    // check if the card needs a target to be played
    if (cardToPlay->getNeedTarget() == false) throw no_target_needed(*cardToPlay);

    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (cost > magic) throw not_enough_magic(*this);

    magic -= cost;
    
    if (Enchantment* enchantCard = dynamic_cast<Enchantment*>(cardToPlay)) { // enchantment
        if (Minion* targetMinion = dynamic_cast<Minion*>(targetCard)) {         
            // place enchantment decorator on the Minion card, converting from enchantment's Card to its Decorator version
            p.getBoard().enchantMinion(j, enchantCard->getName());

        } else { throw invalid_play{"You cannot play " + cardToPlay->getName() + " on " + targetCard->getName()}; }
    } else if (cardToPlay->getType() == CardType::Spell) { // spell with target
        // do something
    }
}

