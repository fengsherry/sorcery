// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDEC_H__
#define __ENCHANTMENTDEC_H__
#include "minion.h"

class EnchantmentDec : public Minion {
    public:
        Minion* next;
    public:
        EnchantmentDec(CardName cardName, int cost, string desc, Minion* next);
        virtual ~EnchantmentDec();

        
};

#endif
