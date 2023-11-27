// Public interface for Spell

#ifndef __SPELL_H__
#define __SPELL_H__
#include "card.h"
#include <string>
using namespace std;

class Spell: public Card {
    bool needTarget; // spell may or may not need target
    // do something
    
};

#endif