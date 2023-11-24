#include "ritual.h"
using namespace std;

Ritual::Ritual(int ac, int charge): activationCost{ac}, charge{charge} {}

int Ritual::getActivationCost() {return activationCost;}
int Ritual::getCharge() {return charge;}

void Ritual::decreaseCharge(int n) {charge -= n;}
void Ritual::increaseCharge(int n) {charge += n;}
