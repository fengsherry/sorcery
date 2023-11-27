#ifndef __DEFAULTMINION_H__
#define __DEFAULTMINION_H__
#include <string>
#include <vector>
#include <iostream> // delete later
#include "minion.h"
#include "card.h"
using namespace std;

class DefaultMinion : public Minion {
    int attack, defense;
    int action = 0;
    // Ability ability;

 public:
    // without ability for now
    DefaultMinion(CardName cardName, int cost, int attack, int defense, string desc = "");
    int getAttack() const override;
    int getDefense() const override;
    int getAction() const override;
    //Ability getAbility();

    void setAction(int n);
};

#endif