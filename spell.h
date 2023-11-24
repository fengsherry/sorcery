// Public interface for Spell

#ifndef __SPELL_H__
#define __SPELL_H__
#include "card.h"
#include "activatedability.h"
#include <string>
using namespace std;

class Spell: public Card {
    ActivatedAbility* aa;
    bool needTarget;
    
    public:
        Spell(CardName cardName, int cost, string desc, ActivatedAbility* aa, bool needTarget, Player* target = nullptr);
        bool getNeedTarget();
        void applyAbility(Player& player);

};

#endif