// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDEC_H__
#define __ENCHANTMENTDEC_H__
#include <string>
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
        TriggeredAbility* getEnchantmentAbility();
        MinionPtr getNext();
        void setNext(MinionPtr newnext);
        void setAbility(variant<ActivatedAbility*, TriggeredAbility*, monostate> a);

        // CardName getDefaultMinionName() override;
};
typedef std::shared_ptr<EnchantmentDec> EnchantmentDecPtr;

#endif
