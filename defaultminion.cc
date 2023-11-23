#include <string>
#include <vector>
#include "defaultminion.h"
using namespace std;

DefaultMinion::DefaultMinion(string cardName, int attack, int defense, int action):
    Minion {cardName}, attack {attack}, defense {defense}, action {action} {}

int DefaultMinion::getAttack() {
    return attack;
}

int DefaultMinion::getDefense() {
    return defense;
}

int DefaultMinion::getAction() {
    return action;
}

//Ability getAbility();