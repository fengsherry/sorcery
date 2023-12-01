#include "enchantmentdec.h"

EnchantmentDec::EnchantmentDec(CardName cardName, int cost, string desc, MinionPtr next) : 
    Minion{cardName, cost, desc}, next{next} {}

EnchantmentDec::~EnchantmentDec() { next.reset(); }
