#ifndef __DEFAULTMINION_H__
#define __DEFAULTMINION_H__
#include <string>
#include <vector>
#include "minion.h"
#include "card.h"
using namespace std;

class DefaultMinion : public Minion {
    int attack, defense, action;
    // Ability ability;

 public:
    // Default constructor
    int getAttack();
    int getDefense();
    int getAction();
    //Ability getAbility();
};

#endif
