// Public interface for Ritual

#ifndef __RITUAL_H__
#define __RITUAL_H__
#include "card.h"
#include <string>
using namespace std;

class Ritual: public Card {
    int activationCost;
    int charge;
    bool needTarget = false;
    //TriggeredAbility trigAbility;
 
};

#endif