// Public interface for Minion

#ifndef __MINION_H__
#define __MINION_H__
#include "card.h"
// #inlcude "ability.h"
#include <string>
using namespace std;

class Minion: public Card {
 public:
    // constructor
    // destructor

    virtual int getAttack() = 0;
    virtual int getDefense() = 0;
    // Ability getAbility() = 0;

};

#endif