#include <string>
#include <vector>
#include <string>
#include "defaultminion.h"
#include "sorceryutil.h"
using namespace std;

DefaultMinion::DefaultMinion(CardName cardName, int cost, int attack, int defense,
                                variant<ActivatedAbility*, TriggeredAbility*, monostate> ability, string desc):
    Minion {cardName, cost, desc}, // Minion fields
    cardName{cardName}, attack {attack}, defense {defense}, desc{desc}, // DefaultMinion fields
    ability{ability} // either Activated or TriggeredAbility
    {}

string DefaultMinion::getDefaultMinionName() const {
    return cardNameToString(cardName);
}

string DefaultMinion::getDefaultMinionDesc() const {
    return desc;
}

// const Minion* DefaultMinion::getDefaultMinion() const { return this; }

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

int DefaultMinion::getCost() const {
    return cost;
}

void DefaultMinion::modifyAction(int n){
    action += n;
}

void DefaultMinion::setAbility(variant<ActivatedAbility*, TriggeredAbility*, monostate> a) {
    ability = a;
}

int DefaultMinion::getActivatedAbilityCost() const { 
    ActivatedAbility* aa = get<ActivatedAbility*>(ability);
    return aa->getActivationCost();
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

void DefaultMinion::setAttack(int n) {
    attack = n;
}
//Ability getAbility();
