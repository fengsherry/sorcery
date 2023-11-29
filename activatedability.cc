#include <stdexcept>
#include "activatedability.h"
#include "player.h"
#include "exceptions.h"

ActivatedAbility::ActivatedAbility(int activationCost, bool hitBoth): 
activationCost{activationCost}, hitBoth {hitBoth} {}

void ActivatedAbility::applyAbility(Player& player1, Player& player2, int i) {
    if (hitBoth) {
        doEffect(player1, i);
        doEffect(player2, i);
    } else {
        doEffect(player1, i);
    }
}


/* Abilities for Spells with targets: */

BanishAbility::BanishAbility() : ActivatedAbility{2} {}
BanishAbility::~BanishAbility() {}
void BanishAbility::doEffect(Player& player, int i) {
    if (i == 'r') player.destroyRitual();
    else if (i < 1 || i > player.getBoard().size()) throw outside_range();
    else  player.getBoard().destroyMinion(i - 1);
}

UnsummonAbility::UnsummonAbility() : ActivatedAbility{1} {}
UnsummonAbility::~UnsummonAbility() {}
void UnsummonAbility::doEffect(Player& player, int i) {
    Minion* temp = player.getBoard().getCard(i - 1);
    player.getBoard().destroyMinion(i - 1);
    // need to strip the minion of enchantments
    player.getHand().addCard(temp);
}

// DOES NOTHING YET - need enchantment decorators to be finalized
DisenchantAbility::DisenchantAbility() : ActivatedAbility{1} {}
DisenchantAbility::~DisenchantAbility() {}
void DisenchantAbility::doEffect(Player& player, int i){
    // do something
}

/* Abilities for Spells without targets: */
// i will be unused since these abilities do not target minions

RechargeAbility::RechargeAbility() : ActivatedAbility{1} {}
RechargeAbility::~RechargeAbility() {}
void RechargeAbility::doEffect(Player& player, int i) {
    if (!player.getRitual()) return;
    player.getRitual()->increaseCharge(3);
}

RaiseDeadAbility::RaiseDeadAbility() : ActivatedAbility{1} {}
RaiseDeadAbility::~RaiseDeadAbility() {}
void RaiseDeadAbility::doEffect(Player& player, int i) {

}

// note: this is an ability that effects more than one player
BlizzardAbility::BlizzardAbility() : ActivatedAbility{3, true} {}
BlizzardAbility::~BlizzardAbility() {}
void BlizzardAbility::doEffect(Player& player, int i) {
    for (int i = 0; i < player.getBoard().size(); i++) {
        // decrease defense isn't implemented yet so doesn't work. 
        player.getBoard().getCard(i)->decreaseDefense(2);
    }
}
