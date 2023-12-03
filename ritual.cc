#include "ritual.h"
#include <iostream>
using namespace std;

Ritual::Ritual(CardName cardName, string desc, int cost, int ac, int charge, TriggeredAbility* ta) :
 Card{cardName, cost, CardType::Ritual, false, desc}, activationCost{ac}, charge{charge}, trigAbility{ta} {}


int Ritual::getActivationCost() {return activationCost;}
int Ritual::getCharge() {return charge;}
TriggeredAbility* Ritual::getAbility() {return trigAbility;}


void Ritual::decreaseCharge(int n) {charge -= n;}
void Ritual::increaseCharge(int n) {charge += n;}

void Ritual::printRitual() {
    if (this) cout << this->getName() << " [" << this->getCharge() << " charge | " << this->getActivationCost() << " activation cost]" << endl;
    else cout << "no ritual" << endl;
    
}
