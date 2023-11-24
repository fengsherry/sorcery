#include "activatedability.h"

ActivatedAbility::ActivatedAbility(int activationCost): activationCost{activationCost} {}

bool BanishAbility::applyAbility(Card* c) {
    if (c->getType != CardType::Ritual && c->getType != CardType::Minion) return false;
    delete c;
    return true;
}