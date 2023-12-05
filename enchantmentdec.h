// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDEC_H__
#define __ENCHANTMENTDEC_H__
#include <string>
#include <variant>
#include "minion.h"

class EnchantmentDec : public Minion {
    bool hidden;
    TriggeredAbility* ta;

    protected:
        MinionPtr next;
    public:
        EnchantmentDec(CardName cardName, int cost, string desc, MinionPtr next, bool hidden, TriggeredAbility* ta=nullptr);
        virtual ~EnchantmentDec();

        void setAction(int n) override;
        void modifyAction(int n) override;
        bool isHidden();
        
        string getDefaultMinionName() const override;
        string getDefaultMinionDesc() const override;
        // int getActivatedAbilityCost() const;

        // const Minion* getDefaultMinion() const override;
        variant<ActivatedAbility*, TriggeredAbility*, monostate> getAbility();
        // string getDefaultMinionName() const ;
        Minion* getDefaultMinion() override;
        int getCost() const override;
        TriggeredAbility* getEnchantmentAbility();
        MinionPtr getNext();
        void setNext(MinionPtr newnext);
        void setAbility(variant<ActivatedAbility*, TriggeredAbility*, monostate> a);

        // CardName getDefaultMinionName() override;
};
typedef std::shared_ptr<EnchantmentDec> EnchantmentDecPtr;

/* CONCRETE ENCHANTMENTDEC: */
class GiantStrength : public EnchantmentDec {
    public:
        GiantStrength(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        int getActivatedAbilityCost() const;
        // std::variant<ActivatedAbility*, TriggeredAbility*, std::monostate> getAbility() const override; // no longer neededADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class Enrage : public EnchantmentDec {
    public:
        Enrage(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        int getActivatedAbilityCost() const;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class Haste : public EnchantmentDec {
    public:
        Haste(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        int getActivatedAbilityCost() const;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class MagicFatigue : public EnchantmentDec {
    public:
        MagicFatigue(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        int getActivatedAbilityCost() const;
        // variant<ActivatedAbility*, TriggeredAbility*, monostate> getAbility();

        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

class Silence : public EnchantmentDec {
    public:
        Silence(MinionPtr next);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        int getActivatedAbilityCost() const;
        variant<ActivatedAbility*, TriggeredAbility*, monostate> getAbility();
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

/* Hidden Enchantments */
class ModifyAttack : public EnchantmentDec {
    int ModifyAttackVal;
    public:
        ModifyAttack(MinionPtr next, int ModifyAttackVal);
        int getAttack() const override;
        int getDefense() const override;
        int getAction() const override;
        int getActivatedAbilityCost() const;
        
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
        int getActivatedAbilityCost() const override;
        // Ability getAbility() const override; // ADD THIS BACK ONCE IMPLEMENTED ABILITIES
        //void setAction(int n);
};

#endif

