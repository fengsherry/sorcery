#include <string>
#include "enchantmentdec.h"

EnchantmentDec::EnchantmentDec(CardName cardName, int cost, string desc, Minion* next, bool hidden) : 
    Minion{cardName, cost, desc}, next{next}, hidden{hidden} {}

EnchantmentDec::~EnchantmentDec() { delete next; }

void EnchantmentDec::setAction(int n) { next->setAction(n); }

bool EnchantmentDec::isHidden() { return hidden; }

string EnchantmentDec::getDefaultMinionName() const { return next->getDefaultMinionName(); }

Minion* EnchantmentDec::getNext() { return next; }

// CardName EnchantmentDec::getDefaultMinionName() { return next->getDefaultMinionName(); }
