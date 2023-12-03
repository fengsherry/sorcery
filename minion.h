// Public interface for Minion

#ifndef __MINION_H__
#define __MINION_H__
#include "card.h"
// #include "activatedability.h"
// #include "triggeredability.h"
#include <string>
#include <iostream>
using namespace std;

class DefaultMinion;
class EnchantmentDec;
class Board;

class Minion: public Card {
    CardType type = CardType::Minion;
    bool needTarget = false;
    Board* board = nullptr;

 public:
    Minion(CardName cardName, int cost, string desc = "");
    virtual ~Minion() = default;

    // string getName() const override;
    virtual string getDefaultMinionName() const = 0;
    virtual int getAttack() const = 0;
    virtual int getDefense() const = 0;
    virtual int getAction() const = 0;
    void setBoard(Board* b);
    void destroy();
    void increaseAttack(int n);
    void increaseDefence(int n);
    // virtual Ability getAbility() = 0;

    virtual void setAction(int n) = 0;
    // void enchant(string minionName);
    // void decreaseLife(int n);
    
    // void decreaseDefense(int n);
    bool isDead();
    
    void TEST_printInspectMinion();

};


std::ostream& operator<<(std::ostream& out, const Minion* m);

#endif