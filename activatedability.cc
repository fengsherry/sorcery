#include <stdexcept>
#include "activatedability.h"
#include "player.h"
#include "exceptions.h"
// #include "boardelements.h"
#include "sorceryutil.h"

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
    else if (i < 0 || i > player.getBoard().size()) throw outside_range();
    else  player.getBoard().destroyMinion(i - 1);
}

UnsummonAbility::UnsummonAbility() : ActivatedAbility{1} {}
UnsummonAbility::~UnsummonAbility() {}
void UnsummonAbility::doEffect(Player& player, int i) {
    player.getBoard().stripEnchants(i, player); // remove any enchantments from minion
    Minion* temp = player.getBoard().getCard(i);
    player.getBoard().destroyMinion(i); // remove it from the Board
    player.getHand().addCard(temp); // add it into the Hand
}

// DOES NOTHING YET - need enchantment decorators to be finalized
DisenchantAbility::DisenchantAbility() : ActivatedAbility{1} {}
DisenchantAbility::~DisenchantAbility() {}
void DisenchantAbility::doEffect(Player& player, int i){
    player.getBoard().stripTopEnchant(i);
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
    if (player.getGrave().isEmpty()) throw empty_grave();

    // ressurect top minion in graveyard
    Minion* m = player.getGrave().getTop();
    player.getGrave().removeTop();

    int modifyDefenseVal = 1 - m->getDefense();
    player.getBoard().addCard(m);
    int index = player.getBoard().size() - 1;
    player.getBoard().enchantMinion(index, "Modify Defense", modifyDefenseVal);
}

// note: this is an ability that effects more than one player
BlizzardAbility::BlizzardAbility() : ActivatedAbility{3, true} {}
BlizzardAbility::~BlizzardAbility() {}
void BlizzardAbility::doEffect(Player& player, int i) {
    for (int i = 0; i < player.getBoard().size(); i++) {
        player.getBoard().enchantMinion(i, "Modify Defense", -2);
    }
}

/* Activated Abilities for Minions: */

// deal 1 damage to target minion
NovicePyromancerAbility::NovicePyromancerAbility() {}
NovicePyromancerAbility::~NovicePyromancerAbility() {}
void NovicePyromancerAbility::doEffect(Player& player, int i) {
    player.getBoard().enchantMinion(i, "Modify Defense", -1);
}

// summon a 1/1 air elemental
ApprenticeSummonerAbility::ApprenticeSummonerAbility() {}
ApprenticeSummonerAbility::~ApprenticeSummonerAbility() {}
void ApprenticeSummonerAbility::doEffect(Player& player, int i) {
    if (player.getBoard().size() == 5) throw full_board{};
    else player.getBoard().addCard(dynamic_cast<Minion*>(createCard("Air Elemental", nullptr)));
}

// summon up to three 1/1 air elementals
MasterSummonerAbility::MasterSummonerAbility() {}
MasterSummonerAbility::~MasterSummonerAbility() {}
void MasterSummonerAbility::doEffect(Player& player, int i) {
    if (player.getBoard().size() == 5) throw full_board{};
    else {
        while (player.getBoard().size() != 5) {
            player.getBoard().addCard(dynamic_cast<Minion*>(createCard("Air Elemental", nullptr)));
        }
    }

}
