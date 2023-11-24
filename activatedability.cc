#include "activatedability.h"

ActivatedAbility::ActivatedAbility(Player& target, int activationCost): activationCost{activationCost} {}

// void BanishAbility::applyAbility(Card* c) {
//     if (c->getType != CardType::Ritual && c->getType != CardType::Minion) return false;
//     delete c;
//     return true;
// }


void RechargeAbility::applyAbility(Player& player) {
    if (!player.getRitual()) return;
    player.getRitual()->increaseCharge(3);
}