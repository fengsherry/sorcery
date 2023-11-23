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
    cout << "Player " << id << "'s Deck: " << endl;
    deck.TEST_printDeck();
}

void Player::TEST_printPlayerHand() {
    cout << "Player " << id << "'s Hand: " << endl;
    hand.TEST_printHand();
}

string Player::getName() {return name;}
int Player::getId() {return id;}
int Player::getLife() {return life;}
int Player::getMagic() {return magic;}

Minion* Player::getMinion(int i) {return board.getMinion(i);}
Hand& Player::getHand() {return hand;}


void Player::setLife(int n) {life = n;}
void Player::setMagic(int n) {magic = n;}
void Player::increaseMagic(int n) {magic += n;}
void Player::decreaseLife(int n) {
    life -= n;

    // checks if player is still alive
    if (life <= 0) cout << this->getName() << " is dead D:";
}

void Player::play(int i) {
    Card* cardToPlay = hand.getCard(i);
    Minion* minionToPlay = dynamic_cast<Minion*>(cardToPlay);
    board.addCard(minionToPlay);
}

