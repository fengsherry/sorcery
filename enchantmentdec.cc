#include "enchantmentdec.h"

EnchantmentDec::EnchantmentDec(CardName cardName, int cost, string desc, Minion* next) : 
    Minion{cardName, cost, desc}, next{next} {}

EnchantmentDec::~EnchantmentDec() { delete next; }
