#ifndef __DEFAULTMINION_H__
#define __DEFAULTMINION_H__
#include <string>
#include <vector>
#include <iostream> // delete later
#include <string>
#include <variant>
// #include <bits/stdc++.h>
#include "minion.h"
#include "card.h"
#include "activatedability.h"
#include "triggeredability.h"
using namespace std;

class DefaultMinion : public Minion {
    CardName cardName;
    int attack, defense;
    int action = 0;
    variant<ActivatedAbility*, TriggeredAbility*, monostate> ability;

 public:
    DefaultMinion(CardName cardName, int cost, int attack, int defense,
                    variant<ActivatedAbility*, TriggeredAbility*, monostate> ability,
                    string desc = ""); // optional parameter is last

    string getDefaultMinionName() const override;
    Minion* getDefaultMinion() override;
    int getAttack() const override;
    int getDefense() const override;
    int getAction() const override;
    variant<ActivatedAbility*, TriggeredAbility*, monostate> getAbility();

    void modifyAction(int n) override;
    void setTrigOwnerMinion(MinionPtr m);
    void setAbility(variant<ActivatedAbility*, TriggeredAbility*, monostate> a);
    void setAction(int n);
    void setDefense(int n);
};
typedef shared_ptr<DefaultMinion> DefaultMinionPtr;

#endif
