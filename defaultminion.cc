#include <string>
#include <vector>
#include "defaultminion.h"
using namespace std;

DefaultMinion::DefaultMinion(CardName cardName, int cost, int attack, int defense, string desc):
    Minion {cardName, cost, desc}, attack {attack}, defense {defense} {}

// CardName DefaultMinion::getDefaultMinionName() {
//     return cardName;
// }

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