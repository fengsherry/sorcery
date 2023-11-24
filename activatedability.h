// Public interface for Ability

#ifndef __ACTIVATEDABILITY_H__
#define __ACTIVATEDABILITY_H__
#include "card.h"
#include <vector>
using namespace std;

class ActivatedAbility {
    int activationCost;

    public:
        ActivatedAbility(int activationCost = 0);
}

class BanishAbility : public ActivatedAbility{
    public:
        bool applyAbility() override;
}