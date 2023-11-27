#include "player.h"

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

string Player::getName() const {return name;}
int Player::getId() const {return id;}
int Player::getLife() const {return life;}
int Player::getMagic() const {return magic;}

Hand& Player::getHand() {return hand;}
Board& Player::getBoard() {return board;}

void Player::setLife(int n) {life = n;}
void Player::setMagic(int n) {magic = n;}
void Player::increaseMagic(int n) {magic += n;}
void Player::decreaseLife(int n) {
    life -= n;

    // checks if player is still alive
    if (life <= 0) cout << this->getName() << " is dead D:" << endl; 
    // we should throw an exception here
}

void Player::play(int i) {
    Card* cardToPlay = hand.getCard(i);

    // check if the card can be played without target
    // if (cardToPlay->getNeedTarget() == true) return false;
    if (cardToPlay->getNeedTarget() == true) throw no_target_provided(*cardToPlay);
    
    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    // if (cost > magic) return false;
    if (cost > magic) throw not_enough_magic(*this);

    magic -= cost;

    // currently only considers minions
    if (cardToPlay->getType() == CardType::Minion) {
        Minion* minionToPlay = dynamic_cast<Minion*>(cardToPlay); // fails if cardToPlay is not Minion* type
        board.addCard(minionToPlay);
    } else {
        cout << "this is not a minion" << endl;
    }
}

