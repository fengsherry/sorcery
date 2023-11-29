#include "enchantmentdecsconcrete.h"

/* non-hidden Enchantments (i.e. have a card representation) */

GiantStrength::GiantStrength(Minion* next) : EnchantmentDec{CardName::GiantStrength, 1, "", next, false} {}
int GiantStrength::getAttack() const { return 2 + next->getAttack(); }
int GiantStrength::getDefense() const { return 2 + next->getDefense(); }
int GiantStrength::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
void GiantStrength::setAction(int n) { next->setAction(n); }

Enrage::Enrage(Minion* next) : EnchantmentDec{CardName::Enrage, 2, "", next, false} {}
int Enrage::getAttack() const { return 2 * next->getAttack(); }
int Enrage::getDefense() const { return 2 * next->getDefense(); }
int Enrage::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
void Enrage::setAction(int n) { next->setAction(n); }

// does nothing for now, we need to make this into a triggered ability and add it to the list of observers
Haste::Haste(Minion* next) : EnchantmentDec{
    CardName::Haste, 
    1, 
    "Enchanted minion gains +1 action each turn", 
    next,
    false} {}
int Haste::getAttack() const { return next->getAttack(); }
int Haste::getDefense() const { return next->getDefense(); }
int Haste::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
void Haste::setAction(int n) { next->setAction(n); }

// does nothing for now, we need to implement Abilities so that we can modify the cost field in the Ability object.
MagicFatigue::MagicFatigue(Minion* next) : EnchantmentDec{
    CardName::MagicFatigue, 
    0, 
    "Enchanted minion's activated ability costs 2 more", 
    next,
    false} {}
int MagicFatigue::getAttack() const { return next->getAttack(); }
int MagicFatigue::getDefense() const { return next->getDefense(); }
int MagicFatigue::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
void MagicFatigue::setAction(int n) { next->setAction(n); }

// does nothing for now, we need to implement Abilities so that we can modify the method ?? in the Ability object.
Silence::Silence(Minion* next) : EnchantmentDec{
    CardName::Silence, 
    0, 
    "Enchanted minion cannot use abilities", 
    next,
    false} {}
int Silence::getAttack() const { return next->getAttack(); }
int Silence::getDefense() const { return next->getDefense(); }
int Silence::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
void Silence::setAction(int n) { next->setAction(n); }

/* hidden Enchantments */

ModifyAttack::ModifyAttack(Minion* next, int ModifyAttackVal) : 
    EnchantmentDec{CardName::ModifyAttack, 0, "", next, true}, 
    ModifyAttackVal{ModifyAttackVal} {}
int ModifyAttack::getAttack() const { return ModifyAttackVal + next->getAttack();}
int ModifyAttack::getDefense() const { return next->getDefense();}
int ModifyAttack::getAction() const { return next->getAction(); }
// Ability ModifyAttack::getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
void ModifyAttack::setAction(int n) { next->setAction(n); }

ModifyDefense::ModifyDefense(Minion* next, int ModifyDefenseVal) : 
    EnchantmentDec{CardName::ModifyDefense, 0, "", next, true}, 
    ModifyDefenseVal{ModifyDefenseVal} {}
int ModifyDefense::getAttack() const { return next->getAttack();}
int ModifyDefense::getDefense() const { return ModifyDefenseVal + next->getDefense();}
int ModifyDefense::getAction() const { return next->getAction(); }
// Ability ModifyDefense::getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
void ModifyDefense::setAction(int n) { next->setAction(n); }
