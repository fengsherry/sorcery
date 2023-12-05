// Public interface for Minion

#ifndef __MINION_H__
#define __MINION_H__
#include <string>
#include <iostream>
#include <variant>
#include "card.h"
#include "activatedability.h"
#include "triggeredability.h"

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
    virtual Minion* getDefaultMinion() = 0;
    virtual int getAttack() const = 0;
    virtual int getDefense() const = 0;
    virtual int getAction() const = 0;
    virtual variant<ActivatedAbility*, TriggeredAbility*, monostate> getAbility() = 0;

    void setBoard(Board* b);
    virtual void setAbility(variant<ActivatedAbility*, TriggeredAbility*, monostate> a) = 0;

    void destroy();
    void modifyAttack(int n);
    void modifyDefence(int n);
    virtual void modifyAction(int n) = 0; // lol can't tell if this is supposed to be pure virtual
    // virtual Ability getAbility() = 0;
    virtual void setAction(int n) = 0;
    // void enchant(string minionName);
    // void decreaseLife(int n);
    
    // void decreaseDefense(int n);
    bool isDead();
    
    void TEST_printInspectMinion();

};
typedef std::shared_ptr<Minion> MinionPtr;

std::ostream& operator<<(std::ostream& out, const MinionPtr m);


#endif