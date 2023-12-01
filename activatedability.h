// Public interface for Ability

#ifndef __ACTIVATEDABILITY_H__
#define __ACTIVATEDABILITY_H__

#include "card.h"
#include <vector>
using namespace std;

class Player;

class ActivatedAbility {
    int activationCost;
    virtual void doEffect(Player& player, int i = 0) = 0;
    bool hitBoth = false;

    public:
        explicit ActivatedAbility(int activationCost = 0, bool hitBoth = false);
        virtual ~ActivatedAbility() = default;
        virtual void applyAbility(Player& player1, Player& player2, int i = 0);
};

/* Abilities for Spells with targets: */

class BanishAbility : public ActivatedAbility{
    void doEffect(Player& player, int i = 0) override;
    public:
        BanishAbility();
        ~BanishAbility();
};

class UnsummonAbility : public ActivatedAbility{
    void doEffect(Player& player, int i = 0) override;
    public:
        UnsummonAbility();
        ~UnsummonAbility(); 
};

class DisenchantAbility : public ActivatedAbility{
    void doEffect(Player& player, int i = 0) override;
    public:
        DisenchantAbility();
        ~DisenchantAbility();
};

/* Abilities for Spells without targets: */

class RechargeAbility : public ActivatedAbility {
    void doEffect(Player& player, int i = 0) override;
    public:
        RechargeAbility();
        ~RechargeAbility();
};

class RaiseDeadAbility : public ActivatedAbility {
    void doEffect(Player& player, int i = 0) override;
    public:
        RaiseDeadAbility();
        ~RaiseDeadAbility();
};

// note: this is an ability that effects more than one player
class BlizzardAbility : public ActivatedAbility {
    void doEffect(Player& player, int i = 0) override;
    public:
        BlizzardAbility();
        ~BlizzardAbility();
};



#endif
