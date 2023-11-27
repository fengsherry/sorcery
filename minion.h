// Public interface for Minion

#ifndef __MINION_H__
#define __MINION_H__
#include "card.h"
// #inlcude "ability.h"
#include <string>
using namespace std;

class Minion: public Card {
    CardType type = CardType::Minion;
    bool needTarget = false;
 public:
    Minion(CardName cardName, int cost, string desc = "");
    // destructor

    virtual int getAttack() const = 0;
    virtual int getDefense() const = 0;
    virtual int getAction() const = 0;
    // virtual Ability getAbility() = 0;

    virtual void setAction(int n) = 0;
    void decreaseLife(int n);
    

};

#endif