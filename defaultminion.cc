#include <string>
#include <vector>
#include <string>
#include "defaultminion.h"
#include "sorceryutil.h"
using namespace std;

DefaultMinion::DefaultMinion(CardName cardName, int cost, int attack, int defense, string desc):
    Minion {cardName, cost, desc}, cardName{cardName}, attack {attack}, defense {defense} {}

string DefaultMinion::getDefaultMinionName() const {
    return cardNameToString(cardName);
}

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