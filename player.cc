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
}

void Player::TEST_printPlayerDeck() {
    cout << "Player " << id << "'s Deck: " << endl;
    deck.TEST_printDeck();
}

string Player::getName() {return name;}
int Player::getId() {return id;}
int Player::getLife() {return life;}
int Player::getMagic() {return magic;}

Minion* Player::getMinion(int i) {return board.getMinion(i);}

void Player::decreaseLife(int n) {life -= n;}

void Player::play(int i) {
    Card* cardToPlay = hand.getCard(i);
    Minion* minionToPlay = dynamic_cast<Minion*>(cardToPlay);
    board.addCard(minionToPlay);
}

