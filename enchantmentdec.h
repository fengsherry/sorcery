// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDEC_H__
#define __ENCHANTMENTDEC_H__
#include "minion.h"

class EnchantmentDec : public Minion {
    public:
        bool hidden;
    protected:
        Minion* next;
    public:
        EnchantmentDec(CardName cardName, int cost, string desc, Minion* next, bool hidden);
        virtual ~EnchantmentDec();
        
        // CardName getDefaultMinionName() override;
};

#endif
