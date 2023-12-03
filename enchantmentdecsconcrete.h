// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDECCONCRETE_H__
#define __ENCHANTMENTDECCONCRETE_H__
#include <string>
#include "enchantmentdec.h"

class GiantStrength : public EnchantmentDec {
    public:
        GiantStrength(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class Enrage : public EnchantmentDec {
    public:
        Enrage(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class Haste : public EnchantmentDec {
    public:
        Haste(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class MagicFatigue : public EnchantmentDec {
    public:
        MagicFatigue(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class Silence : public EnchantmentDec {
    public:
        Silence(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class ModifyAttack : public EnchantmentDec {
    int ModifyAttackVal;
    public:
        ModifyAttack(MinionPtr next, int ModifyAttackVal);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class ModifyDefense : public EnchantmentDec {
    int ModifyDefenseVal;
    public:
        ModifyDefense(MinionPtr next, int ModifyDefenseVal);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

// doesn't work yet
class ModifyAbility : public EnchantmentDec {
    public:
        ModifyAbility(Minion* next, int ModifyDefenseVal);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        // //void setAction(int n);
};

#endif
