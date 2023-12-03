#include <string>
#include "enchantmentdec.h"

EnchantmentDec::EnchantmentDec(CardName cardName, int cost, string desc, MinionPtr next, bool hidden) : 
    Minion{cardName, cost, desc}, next{next}, hidden{hidden} {}

EnchantmentDec::~EnchantmentDec() { next.reset(); }

void EnchantmentDec::setAction(int n) { next->setAction(n); }

bool EnchantmentDec::isHidden() { return hidden; }

string EnchantmentDec::getDefaultMinionName() const { return next->getDefaultMinionName(); }

string EnchantmentDec::getDefaultMinionDesc() const { return next->getDefaultMinionDesc(); }

// const Minion* EnchantmentDec::getDefaultMinion() const { return next->getDefaultMinion(); }

variant<ActivatedAbility*, TriggeredAbility*, monostate> EnchantmentDec::getAbility() {
    return next->getAbility();
}

MinionPtr EnchantmentDec::getNext() { return next; }

void EnchantmentDec::setNext(MinionPtr newnext) { next = newnext; }

// CardName EnchantmentDec::getDefaultMinionName() { return next->getDefaultMinionName(); }
