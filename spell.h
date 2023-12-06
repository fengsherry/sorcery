// Public interface for Spell

#ifndef __SPELL_H__
#define __SPELL_H__
#include "card.h"
#include "activatedability.h"
#include <string>
using namespace std;

class Spell: public Card {
    ActivatedAbility* aa;
    
    public:
        Spell(CardName cardName, int cost, bool needTarget, string desc, ActivatedAbility* aa, Player* target = nullptr);
        void applyAbility(Player& player1, Player& player2);
        void applyAbility(Player& player1, Player& player2, int i);
};

typedef shared_ptr<Spell> SpellPtr;

#endif

