#include <string>
#include "enchantmentdec.h"

EnchantmentDec::EnchantmentDec(CardName cardName, int cost, string desc, MinionPtr next, bool hidden, TriggeredAbility* ta) : 
    Minion{cardName, cost, desc}, next{next}, hidden{hidden}, ta{ta} {}

EnchantmentDec::~EnchantmentDec() { next.reset(); }

void EnchantmentDec::setAction(int n) { next->setAction(n); }

void EnchantmentDec::setAbility(variant<ActivatedAbility*, TriggeredAbility*, monostate> a) {
    next->setAbility(a);
}

void EnchantmentDec::modifyAction(int n) { next->modifyAction(n); }

bool EnchantmentDec::isHidden() { return hidden; }

string EnchantmentDec::getDefaultMinionName() const { return next->getDefaultMinionName(); }

string EnchantmentDec::getDefaultMinionDesc() const { return next->getDefaultMinionDesc(); }

int EnchantmentDec::getCost() const { return next->getCost(); }

// int EnchantmentDec::getActivatedAbilityCost() const {return next->getActivatedAbilityCost(); }

// const Minion* EnchantmentDec::getDefaultMinion() const { return next->getDefaultMinion(); }

Minion* EnchantmentDec::getDefaultMinion() { return next->getDefaultMinion(); }

MinionPtr EnchantmentDec::getNext() { return next; }

variant<ActivatedAbility*, TriggeredAbility*, monostate> EnchantmentDec::getAbility() {
    return next->getAbility();
}

void EnchantmentDec::setNext(MinionPtr newnext) { next = newnext; }

TriggeredAbility* EnchantmentDec::getEnchantmentAbility() { return ta;}
// CardName EnchantmentDec::getDefaultMinionName() { return next->getDefaultMinionName(); }


/* non-hidden Enchantments (i.e. have a card representation) */

GiantStrength::GiantStrength(MinionPtr next) : EnchantmentDec{CardName::GiantStrength, 1, "", next, false} {}
int GiantStrength::getAttack() const { return 2 + next->getAttack(); }
int GiantStrength::getDefense() const { return 2 + next->getDefense(); }
int GiantStrength::getAction() const { return next->getAction(); }
int GiantStrength::getActivatedAbilityCost() const {return next->getActivatedAbilityCost();}
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
// void GiantStrength::setAction(int n) { next->setAction(n); }

Enrage::Enrage(MinionPtr next) : EnchantmentDec{CardName::Enrage, 2, "", next, false} {}
int Enrage::getAttack() const { return 2 * next->getAttack(); }
int Enrage::getDefense() const { return 2 * next->getDefense(); }
int Enrage::getAction() const { return next->getAction(); }
int Enrage::getActivatedAbilityCost() const {return next->getActivatedAbilityCost();}
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

// does nothing for now, we need to make this into a triggered ability and add it to the list of observers
Haste::Haste(MinionPtr next) : EnchantmentDec{
    CardName::Haste, 
    1, 
    "Enchanted minion gains +1 action each turn", 
    next,
    false,
    new HasteAbility{next}} // idk if this is suppoed to attack to base minion instead
    {}
int Haste::getAttack() const { return next->getAttack(); }
int Haste::getDefense() const { return next->getDefense(); }
int Haste::getAction() const { return next->getAction(); }
int Haste::getActivatedAbilityCost() const {return next->getActivatedAbilityCost();}
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES


MagicFatigue::MagicFatigue(MinionPtr next) : EnchantmentDec{
    CardName::MagicFatigue, 
    0, 
    "Enchanted minion's activated ability costs 2 more", 
    next,
    false} {}
int MagicFatigue::getAttack() const { return next->getAttack(); }
int MagicFatigue::getDefense() const { return next->getDefense(); }
int MagicFatigue::getAction() const { return next->getAction(); }
int MagicFatigue::getActivatedAbilityCost() const {
    return 2 + next->getActivatedAbilityCost(); 
}



Silence::Silence(MinionPtr next) : EnchantmentDec{
    CardName::Silence, 
    0, 
    "Enchanted minion cannot use abilities", 
    next,
    false} {}
int Silence::getAttack() const { return next->getAttack(); }
int Silence::getDefense() const { return next->getDefense(); }
int Silence::getAction() const { return next->getAction(); }
int Silence::getActivatedAbilityCost() const {return next->getActivatedAbilityCost();}
variant<ActivatedAbility*, TriggeredAbility*, monostate> Silence::getAbility(){
    //cout << "hi" << endl;
    return new SilenceAbility{};
}
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES


/* Hidden Enchantments */

ModifyAttack::ModifyAttack(MinionPtr next, int ModifyAttackVal) : 
    EnchantmentDec{CardName::ModifyAttack, 0, "", next, true}, 
    ModifyAttackVal{ModifyAttackVal} {}
int ModifyAttack::getAttack() const { return ModifyAttackVal + next->getAttack();}
int ModifyAttack::getDefense() const { return next->getDefense();}
int ModifyAttack::getAction() const { return next->getAction(); }
int ModifyAttack::getActivatedAbilityCost() const {return next->getActivatedAbilityCost();}
// Ability ModifyAttack::getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

ModifyDefense::ModifyDefense(MinionPtr next, int ModifyDefenseVal) : 
    EnchantmentDec{CardName::ModifyDefense, 0, "", next, true}, 
    ModifyDefenseVal{ModifyDefenseVal} {}
int ModifyDefense::getAttack() const { return next->getAttack();}
int ModifyDefense::getDefense() const { return ModifyDefenseVal + next->getDefense();}
int ModifyDefense::getAction() const { return next->getAction(); }
int ModifyDefense::getActivatedAbilityCost() const {return next->getActivatedAbilityCost();}
// Ability ModifyDefense::getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
