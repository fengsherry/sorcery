#include "enchantmentdecsconcrete.h"

/* non-hidden Enchantments (i.e. have a card representation) */

GiantStrength::GiantStrength(MinionPtr next) : EnchantmentDec{CardName::GiantStrength, 1, "", next, false} {}
int GiantStrength::getAttack() const { return 2 + next->getAttack(); }
int GiantStrength::getDefense() const { return 2 + next->getDefense(); }
int GiantStrength::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIESvoid GiantStrength::setAction(int n) { next->setAction(n); }

Enrage::Enrage(MinionPtr next) : EnchantmentDec{CardName::Enrage, 2, "", next, false} {}
int Enrage::getAttack() const { return 2 * next->getAttack(); }
int Enrage::getDefense() const { return 2 * next->getDefense(); }
int Enrage::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

// does nothing for now, we need to make this into a triggered ability and add it to the list of observers
Haste::Haste(MinionPtr next) : EnchantmentDec{
    CardName::Haste, 
    1, 
    "Enchanted minion gains +1 action each turn", 
    next,
    false} {
        next->setAbility(new HasteAbility{next}); // idk if this is suppoed to attack to base minion instead
    }
int Haste::getAttack() const { return next->getAttack(); }
int Haste::getDefense() const { return next->getDefense(); }
int Haste::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

// does nothing for now, we need to implement Abilities so that we can modify the cost field in the Ability object.
MagicFatigue::MagicFatigue(MinionPtr next) : EnchantmentDec{
    CardName::MagicFatigue, 
    0, 
    "Enchanted minion's activated ability costs 2 more", 
    next,
    false} {}
int MagicFatigue::getAttack() const { return next->getAttack(); }
int MagicFatigue::getDefense() const { return next->getDefense(); }
int MagicFatigue::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

// does nothing for now, we need to implement Abilities so that we can modify the method ?? in the Ability object.
Silence::Silence(MinionPtr next) : EnchantmentDec{
    CardName::Silence, 
    0, 
    "Enchanted minion cannot use abilities", 
    next,
    false} {}
int Silence::getAttack() const { return next->getAttack(); }
int Silence::getDefense() const { return next->getDefense(); }
int Silence::getAction() const { return next->getAction(); }
// Ability GiantStrength::getAbility() const; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES


/* Hidden Enchantments */

ModifyAttack::ModifyAttack(MinionPtr next, int ModifyAttackVal) : 
    EnchantmentDec{CardName::ModifyAttack, 0, "", next, true}, 
    ModifyAttackVal{ModifyAttackVal} {}
int ModifyAttack::getAttack() const { return ModifyAttackVal + next->getAttack();}
int ModifyAttack::getDefense() const { return next->getDefense();}
int ModifyAttack::getAction() const { return next->getAction(); }
// Ability ModifyAttack::getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

ModifyDefense::ModifyDefense(MinionPtr next, int ModifyDefenseVal) : 
    EnchantmentDec{CardName::ModifyDefense, 0, "", next, true}, 
    ModifyDefenseVal{ModifyDefenseVal} {}
int ModifyDefense::getAttack() const { return next->getAttack();}
int ModifyDefense::getDefense() const { return ModifyDefenseVal + next->getDefense();}
int ModifyDefense::getAction() const { return next->getAction(); }
// Ability ModifyDefense::getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES

// need to implement this later

// ModifyAbility::ModifyAbility(MinionPtr next, int ModifyDefenseVal) :
//     EnchantmentDec{CardName::ModifyAbility, 0, "", next, true}
// int ModifyAbility::getAttack() const { return next->getAttack(); }
// int ModifyAbility::getDefense() const { return next->getDefense(); }
// int ModifyAbility::getAction() const { return next->getAction(); }
// // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
// //void ModifyAbility::setAction(int n) {next->setAction(n); }
