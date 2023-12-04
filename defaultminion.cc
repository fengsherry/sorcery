#include <string>
#include <vector>
#include <string>
#include "defaultminion.h"
#include "sorceryutil.h"
using namespace std;

DefaultMinion::DefaultMinion(CardName cardName, int cost, int attack, int defense,
                                variant<ActivatedAbility*, TriggeredAbility*, monostate> ability, string desc):
    Minion {cardName, cost, desc}, // Minion fields
    cardName{cardName}, attack {attack}, defense {defense}, // DefaultMinion fields
    ability{ability} // either Activated or TriggeredAbility
    {}

string DefaultMinion::getDefaultMinionName() const {
    return cardNameToString(cardName);
}

Minion* DefaultMinion::getDefaultMinion() {
    return this;
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

void DefaultMinion::setTrigOwnerMinion(MinionPtr m) {
    // maybe add exception check here
    get<TriggeredAbility*>(ability)->setOwnerMinion(m);
}

variant<ActivatedAbility*, TriggeredAbility*, monostate> DefaultMinion::getAbility() {
    return ability;
}

void DefaultMinion::setAction(int n) {
    action = n;
}

void DefaultMinion::setDefense(int n) {
    defense = n;
}

//Ability getAbility();
