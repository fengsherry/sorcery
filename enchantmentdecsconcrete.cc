#include "enchantmentdecsconcrete.h"

GiantStrength::GiantStrength(Minion* next) : EnchantmentDec{CardName::GiantStrength, 1, "", next} {}
int GiantStrength::getAttack() const { return 2 + next->getAttack(); }
int GiantStrength::getDefense() const { return 2 + next->getDefense(); }
int GiantStrength::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

Enrage::Enrage(Minion* next) : EnchantmentDec{CardName::Enrage, 2, "", next} {}
int Enrage::getAttack() const { return 2 * next->getAttack(); }
int Enrage::getDefense() const { return 2 * next->getDefense(); }
int Enrage::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

// does nothing for now, we need to make this into a triggered ability and add it to the list of observers
Haste::Haste(Minion* next) : EnchantmentDec{
    CardName::Haste, 
    1, 
    "Enchanted minion gains +1 action each turn", 
    next} {}
int Haste::getAttack() const { return next->getAttack(); }
int Haste::getDefense() const { return next->getDefense(); }
int Haste::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

// does nothing for now, we need to implement Abilities so that we can modify the cost field in the Ability object.
MagicFatigue::MagicFatigue(Minion* next) : EnchantmentDec{
    CardName::MagicFatigue, 
    0, 
    "Enchanted minion's activated ability costs 2 more", 
    next} {}
int MagicFatigue::getAttack() const { return next->getAttack(); }
int MagicFatigue::getDefense() const { return next->getDefense(); }
int MagicFatigue::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

// does nothing for now, we need to implement Abilities so that we can modify the method ?? in the Ability object.
Silence::Silence(Minion* next) : EnchantmentDec{
    CardName::Silence, 
    0, 
    "Enchanted minion cannot use abilities", 
    next} {}
int Silence::getAttack() const { return next->getAttack(); }
int Silence::getDefense() const { return next->getDefense(); }
int Silence::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
