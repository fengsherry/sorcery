#include "enchantmentdec.h"

EnchantmentDec::EnchantmentDec(CardName cardName, int cost, string desc, Minion* next, bool hidden) : 
    Minion{cardName, cost, desc}, next{next}, hidden{hidden} {}

EnchantmentDec::~EnchantmentDec() { delete next; }

// CardName EnchantmentDec::getDefaultMinionName() { return next->getDefaultMinionName(); }
