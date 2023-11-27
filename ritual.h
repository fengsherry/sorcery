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
    public:
        Ritual(int ac, int charge);

        int getActivationCost();
        int getCharge();

        void decreaseCharge(int n);
        void increaseCharge(int n);
};

#endif