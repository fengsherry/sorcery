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
        void setAction(int n);
};

class Enrage : public EnchantmentDec {
    public:
        Enrage(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class Haste : public EnchantmentDec {
    public:
        Haste(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class MagicFatigue : public EnchantmentDec {
    public:
        MagicFatigue(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

class Silence : public EnchantmentDec {
    public:
        Silence(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        void setAction(int n);
};

#endif
