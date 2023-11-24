// Public interface for Spell

#ifndef __SPELL_H__
#define __SPELL_H__
#include "card.h"
#include <string>
using namespace std;

class Spell: public Card {
    ActivatedAbility* aa;
    
    public:
        Spell(CardName cardName, int cost, CardType type, string desc, ActivatedAbility* aa);
    
};

#endif