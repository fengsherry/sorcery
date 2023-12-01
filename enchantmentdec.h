// Public interface for Enchantment Decorators

#ifndef __ENCHANTMENTDEC_H__
#define __ENCHANTMENTDEC_H__
#include "minion.h"

class EnchantmentDec : public Minion {
    public:
        MinionPtr next;
    public:
        EnchantmentDec(CardName cardName, int cost, string desc, MinionPtr next);
        virtual ~EnchantmentDec();

        
};

#endif
