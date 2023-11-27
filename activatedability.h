// Public interface for Ability

#ifndef __ACTIVATEDABILITY_H__
#define __ACTIVATEDABILITY_H__
#include "player.h"
#include "card.h"
#include <vector>
using namespace std;

class ActivatedAbility {
    int activationCost;
    Player& target;
    
    public:
        ActivatedAbility(Player& target, int activationCost = 0);
        virtual void applyAbility(Player& player);
};

// class BanishAbility : public ActivatedAbility{
//     public:
//         void applyAbility(Card* c);
// }

class RechargeAbility : public ActivatedAbility {
    public:
        RechargeAbility();
        void applyAbility(Player& player) override;

};
#endif
