#include "ritual.h"
#include "exceptions.h"
#include <iostream>
using namespace std;

Ritual::Ritual(CardName cardName, string desc, int cost, int ac, int charge, TriggeredAbility* ta) :
 Card{cardName, cost, CardType::Ritual, false, desc}, activationCost{ac}, charge{charge}, trigAbility{ta} {}


int Ritual::getActivationCost() {return activationCost;}
int Ritual::getCharge() {return charge;}
TriggeredAbility* Ritual::getAbility() {return trigAbility;}


void Ritual::decreaseCharge(int n) {
    cout << "n: " << n << "charge: " << charge << endl;
    if (n > charge) {
        trigAbility->setEnoughCharge(false);
        cout << "SETTING ENOUGH CHARGE TO FALSE" << endl;
        throw not_enough_charge(this);
    } else if (n == charge) {
        trigAbility->setEnoughCharge(false); charge -= n;
    } else charge -= n;

    // if (n == charge) charge -= n;
}

void Ritual::increaseCharge(int n) {
    charge += n;
    if (charge > 0) trigAbility->setEnoughCharge(true);
}

void Ritual::trigger() {decreaseCharge(activationCost);}

void Ritual::printRitual() {
    if (this) cout << this->getName() << " [" << this->getCharge() << " charge | " << this->getActivationCost() << " activation cost]" << endl;
    else cout << "no ritual" << endl;
    
}
