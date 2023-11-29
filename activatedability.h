// Public interface for Ability

#ifndef __ACTIVATEDABILITY_H__
#define __ACTIVATEDABILITY_H__

#include "card.h"
#include <vector>
using namespace std;

class Player;

class ActivatedAbility {
    int activationCost;
    
    public:
        explicit ActivatedAbility(int activationCost = 0);
        virtual ~ActivatedAbility() = default;
        virtual void applyAbility(Player& player, int i = 0) = 0;
};

/* Abilities for Spells with targets: */

class BanishAbility : public ActivatedAbility{
    public:
        BanishAbility();
        ~BanishAbility();
        void applyAbility(Player& player, int i = 0) override;
};

class UnsummonAbility : public ActivatedAbility{
    public:
        UnsummonAbility();
        ~UnsummonAbility(); 
        void applyAbility(Player& player, int i = 0) override;
};

class DisenchantAbility : public ActivatedAbility{
    public:
        DisenchantAbility();
        ~DisenchantAbility();
        void applyAbility(Player& player, int i = 0) override;
};

/* Abilities for Spells without targets: */

class RechargeAbility : public ActivatedAbility {
    public:
        RechargeAbility();
        ~RechargeAbility();
        void applyAbility(Player& player, int i = 0) override;
};

class RaiseDeadAbility : public ActivatedAbility {
    public:
        RaiseDeadAbility();
        ~RaiseDeadAbility();
        void applyAbility(Player& player, int i = 0) override;

};

// note: this is an ability that effects more than one player
class BlizzardAbility : public ActivatedAbility {
    public:
        BlizzardAbility();
        ~BlizzardAbility();
        void applyAbility(Player& player, int i = 0) override;

};

#endif
