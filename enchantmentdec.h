// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDEC_H__
#define __ENCHANTMENTDEC_H__
#include <string>
#include "minion.h"

class EnchantmentDec : public Minion {
    bool hidden;

    protected:
        Minion* next;
    public:
        EnchantmentDec(CardName cardName, int cost, string desc, Minion* next, bool hidden);
        virtual ~EnchantmentDec();

        void setAction(int n);
        bool isHidden();
        
        string getDefaultMinionName() const override;
        Minion* getDefaultMinion() override;
        Minion* getNext();
        void setNext(Minion* newnext);
        // CardName getDefaultMinionName() override;
};

#endif
