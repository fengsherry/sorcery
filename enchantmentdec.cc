#include <string>
#include "enchantmentdec.h"

EnchantmentDec::EnchantmentDec(CardName cardName, int cost, string desc, MinionPtr next, bool hidden) : 
    Minion{cardName, cost, desc}, next{next}, hidden{hidden} {}

EnchantmentDec::~EnchantmentDec() { next.reset(); }

void EnchantmentDec::setAction(int n) { next->setAction(n); }

void EnchantmentDec::setAbility(variant<ActivatedAbility*, TriggeredAbility*, monostate> a) {
    next->setAbility(a);
}

void EnchantmentDec::modifyAction(int n) { next->modifyAction(n); }

bool EnchantmentDec::isHidden() { return hidden; }

string EnchantmentDec::getDefaultMinionName() const { return next->getDefaultMinionName(); }

Minion* EnchantmentDec::getDefaultMinion() { return next->getDefaultMinion(); }

MinionPtr EnchantmentDec::getNext() { return next; }

variant<ActivatedAbility*, TriggeredAbility*, monostate> EnchantmentDec::getAbility() {
    return next->getAbility();
}

void EnchantmentDec::setNext(MinionPtr newnext) { next = newnext; }

// CardName EnchantmentDec::getDefaultMinionName() { return next->getDefaultMinionName(); }
