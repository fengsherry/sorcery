#include <string>
#include <vector>
#include "defaultminion.h"
using namespace std;

DefaultMinion::DefaultMinion(string cardName, int attack, int defense):
    Minion {cardName}, attack {attack}, defense {defense} {}

int DefaultMinion::getAttack() const {
    return attack;
}

int DefaultMinion::getDefense() const {
    return defense;
}

int DefaultMinion::getAction() const {
    return action;
}


void DefaultMinion::setAction(int n) {
    action = n;
}
//Ability getAbility();