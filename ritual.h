// Public interface for Ritual

#ifndef __RITUAL_H__
#define __RITUAL_H__
#include "card.h"
#include "triggeredability.h"
#include <string>
using namespace std;

class Ritual: public Card {
    int activationCost;
    int charge;
    TriggeredAbility* trigAbility;

    public:
    //     Card(CardName cardName, int cost, CardType type, bool needTarget, string desc = "");

        Ritual(CardName cardName, string desc, int cost, int ac, int charge, TriggeredAbility* ta);

        int getActivationCost();
        int getCharge();
        TriggeredAbility* getAbility();

        void decreaseCharge(int n);
        void increaseCharge(int n);
        void printRitual();
        void trigger(); // decreases charge by activation cost
};

typedef shared_ptr<Ritual>  RitualPtr;

#endif