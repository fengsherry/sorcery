#ifndef __DEFAULTMINION_H__
#define __DEFAULTMINION_H__
#include <string>
#include <vector>
#include "minion.h"
#include "card.h"
using namespace std;

class DefaultMinion : public Minion {
    int attack, defense;
    int action = 0;
    // Ability ability;

 public:
    // without ability for now
    DefaultMinion(string cardName, int attack, int defense, int action);
    int getAttack();
    int getDefense();
    int getAction();
    //Ability getAbility();
};

#endif