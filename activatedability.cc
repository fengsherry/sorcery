#include <stdexcept>
#include "activatedability.h"
#include "player.h"
#include "exceptions.h"

ActivatedAbility::ActivatedAbility(int activationCost): activationCost{activationCost} {}

/* Abilities for Spells with targets: */

BanishAbility::BanishAbility() : ActivatedAbility{2} {}
BanishAbility::~BanishAbility() {}
void applyAbility(Player& player, int i) {
    if (i = 'r') player.destroyRitual();
    else if (i < 1 || i > player.getBoard().size()) throw outside_range();
    else  player.getBoard().destroyMinion(i - 1);
}

UnsummonAbility::UnsummonAbility() : ActivatedAbility{1} {}
UnsummonAbility::~UnsummonAbility() {}
void UnsummonAbility::applyAbility(Player& player, int i) {
    Minion* temp = player.getBoard().getCard(i - 1);
    player.getBoard().destroyMinion(i - 1);
    // need to strip the minion of enchantments
    player.getHand().addCard(temp);
}

// DOES NOTHING YET - need enchantment decorators to be finalized
DisenchantAbility::DisenchantAbility() : ActivatedAbility{1} {}
DisenchantAbility::~DisenchantAbility() {}
void DisenchantAbility::applyAbility(Player& player, int i = 0){
    // do something
}

/* Abilities for Spells without targets: */
// i will be unused since these abilities do not target minions

RechargeAbility::RechargeAbility() : ActivatedAbility{1} {}
RechargeAbility::~RechargeAbility() {}
void RechargeAbility::applyAbility(Player& player, int i) {
    if (!player.getRitual()) return;
    player.getRitual()->increaseCharge(3);
}

RaiseDeadAbility::RaiseDeadAbility() : ActivatedAbility{1} {}
RaiseDeadAbility::~RaiseDeadAbility() {}
void RaiseDeadAbility::applyAbility(Player& player, int i = 0) {

}

// DOES NOTHING YET - still confused lol
// note: this is an ability that effects more than one player
BlizzardAbility::BlizzardAbility() : ActivatedAbility{3} {}
BlizzardAbility::~BlizzardAbility() {}
void BlizzardAbility::applyAbility(Player& player, int i = 0) {

}
