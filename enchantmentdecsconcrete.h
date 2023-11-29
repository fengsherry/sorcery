// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDECCONCRETE_H__
#define __ENCHANTMENTDECCONCRETE_H__
#include <string>
#include "enchantmentdec.h"

class GiantStrength : public EnchantmentDec {
    public:
        GiantStrength(Minion* next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class Enrage : public EnchantmentDec {
    public:
        Enrage(Minion* next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class Haste : public EnchantmentDec {
    public:
        Haste(Minion* next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class MagicFatigue : public EnchantmentDec {
    public:
        MagicFatigue(Minion* next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class Silence : public EnchantmentDec {
    public:
        Silence(Minion* next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class ModifyAttack : public EnchantmentDec {
    int ModifyAttackVal;
    public:
        ModifyAttack(Minion* next, int ModifyAttackVal);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class ModifyDefense : public EnchantmentDec {
    int ModifyDefenseVal;
    public:
        ModifyDefense(Minion* next, int ModifyDefenseVal);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

#endif
