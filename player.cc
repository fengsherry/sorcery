#include "player.h"

Player::Player() {
    name = "DEFAULT PLAYER";
    id = 0;
}

// Player::Player(string name, int id) : name{name}, id{id} {}

Player::~Player() {}

void Player::init(string name, int id) {
    this->name = name;
    this->id = id;
}

string Player::getName() {return name;}
int Player::getId() {return id;}
int Player::getLife() {return life;}
int Player::getMagic() {return magic;}

Minion* Player::getMinion(int i) {return board.getMinion(i);}

void Player::decreaseLife(int n) {life -= n;}

