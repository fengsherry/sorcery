#include "player.h"

Player::Player() {
    name = "DEFAULT PLAYER";
    id = 0;
}

Player::Player(string name, int id) : name{name}, id{id} {

}

Player::~Player() {}

string Player::getName() {return name;}
int Player::getId() {return id;}
int Player::getLife() {return life;}
int Player::getMagic() {return magic;}


