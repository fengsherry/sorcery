#include <string>
#include "enchantmentdec.h"

EnchantmentDec::EnchantmentDec(CardName cardName, int cost, string desc, Minion* next, bool hidden) : 
    Minion{cardName, cost, desc}, next{next}, hidden{hidden} {}

EnchantmentDec::~EnchantmentDec() { delete next; }

void EnchantmentDec::setAction(int n) { next->setAction(n); }

bool EnchantmentDec::isHidden() { return hidden; }

string EnchantmentDec::getDefaultMinionName() const { return next->getDefaultMinionName(); }

variant<ActivatedAbility*, TriggeredAbility*, monostate> EnchantmentDec::getAbility() {
    return next->getAbility();
}

Minion* EnchantmentDec::getNext() { return next; }

void EnchantmentDec::setNext(Minion* newnext) { next = newnext; }

// CardName EnchantmentDec::getDefaultMinionName() { return next->getDefaultMinionName(); }
