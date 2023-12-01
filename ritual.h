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
    //     Card(CardName cardName, int cost, CardType type, bool needTarget, string desc = "");

        Ritual(CardName cardName, string desc, int cost, int ac, int charge);

        int getActivationCost();
        int getCharge();

        void decreaseCharge(int n);
        void increaseCharge(int n);
        void printRitual();
};

typedef shared_ptr<Ritual>  RitualPtr;

#endif