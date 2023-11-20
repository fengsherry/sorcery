// Public interface for Minion

#ifndef __MINION_H__
#define __MINION_H__
#include "card.h"
#include <string>
using namespace std;

class Minion: public Card {
 private:
    // add to UML:
    int attack;
    int ability;
    //Ability ability;

 public:
    // constructor
    // destructor
    int getAttack();
    int getDefense();
    // Ability getAbility();

};

#endif