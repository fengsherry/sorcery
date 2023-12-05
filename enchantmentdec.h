// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDEC_H__
#define __ENCHANTMENTDEC_H__
#include <string>
#include "minion.h"

class EnchantmentDec : public Minion {
    bool hidden;

    protected:
        MinionPtr next;
    public:
        EnchantmentDec(CardName cardName, int cost, string desc, MinionPtr next, bool hidden);
        virtual ~EnchantmentDec();

        void setAction(int n) override;
        void modifyAction(int n) override;
        bool isHidden();
        
        variant<ActivatedAbility*, TriggeredAbility*, monostate> getAbility();
        string getDefaultMinionName() const ;
        Minion* getDefaultMinion() override;
        MinionPtr getNext();
        void setNext(MinionPtr newnext);
        void setAbility(variant<ActivatedAbility*, TriggeredAbility*, monostate> a);

        // CardName getDefaultMinionName() override;
};
typedef std::shared_ptr<EnchantmentDec> EnchantmentDecPtr;

#endif
