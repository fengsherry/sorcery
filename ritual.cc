#include "ritual.h"
#include <iostream>
using namespace std;

Ritual::Ritual(CardName cardName, string desc, int cost, int ac, int charge) :
 Card{cardName, cost, CardType::Ritual, false, desc}, activationCost{ac}, charge{charge} {}

int Ritual::getActivationCost() {return activationCost;}
int Ritual::getCharge() {return charge;}

void Ritual::decreaseCharge(int n) {charge -= n;}
void Ritual::increaseCharge(int n) {charge += n;}

void Ritual::printRitual() {
    if (this) cout << this->getName() << " [" << this->getCharge() << " charge | " << this->getActivationCost() << " activation cost]" << endl;
    else cout << "no ritual" << endl;

}
