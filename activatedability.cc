#include <stdexcept>
#include "activatedability.h"
#include "player.h"
#include "exceptions.h"
// #include "boardelements.h"
#include "sorceryutil.h"

ActivatedAbility::ActivatedAbility(int activationCost, bool needTarget, bool hitBoth) : 
activationCost{activationCost}, hitBoth {hitBoth}, needTarget{needTarget} {}

void ActivatedAbility::applyAbility(Player& player1, Player& player2, int i) {
    if (hitBoth) {
        doEffect(player1, i);
        doEffect(player2, i);
    } else {
        doEffect(player1, i);
    }
}

bool ActivatedAbility::getNeedTarget() { return needTarget; }

int ActivatedAbility::getActivationCost() { return activationCost; }

void ActivatedAbility::incActivationCost(int n) {activationCost += n; }

/* Abilities for Spells with targets: */

BanishAbility::BanishAbility() {}
BanishAbility::~BanishAbility() {}
void BanishAbility::doEffect(Player& player, int i) {
    if (i == -1) player.destroyRitual();
    else if (i < 0 || i > player.getBoard().size()) throw outside_range();
    else  player.getBoard().removeCard(i);
}

UnsummonAbility::UnsummonAbility() {}
UnsummonAbility::~UnsummonAbility() {}
void UnsummonAbility::doEffect(Player& player, int i) {
    player.getBoard().stripEnchants(i); // remove any enchantments from minion
    MinionPtr temp = player.getBoard().getCard(i);
    player.getBoard().removeCard(i); // remove it from the Board
    player.getHand().addCard(temp); // add it into the Hand
}

// DOES NOTHING YET - need enchantment decorators to be finalized
DisenchantAbility::DisenchantAbility() {}
DisenchantAbility::~DisenchantAbility() {}
void DisenchantAbility::doEffect(Player& player, int i){
    try {
        player.getBoard().stripTopEnchant(i);
    } catch (no_enchantments& e) {}
}

/* Abilities for Spells without targets: */
// i will be unused since these abilities do not target minions

RechargeAbility::RechargeAbility() {}
RechargeAbility::~RechargeAbility() {}
void RechargeAbility::doEffect(Player& player, int i) {
    if (!player.getRitual()) return;
    player.getRitual()->increaseCharge(3);
}

RaiseDeadAbility::RaiseDeadAbility() {}
RaiseDeadAbility::~RaiseDeadAbility() {}
void RaiseDeadAbility::doEffect(Player& player, int i) {
    if (player.getGrave().isEmpty()) throw empty_grave();

    // ressurect top minion in graveyard
    MinionPtr m = player.getGrave().getTop();
    player.getGrave().removeTop();

    int modifyDefenseVal = 1 - m->getDefense();
    player.getBoard().addCard(m);
    int index = player.getBoard().size() - 1;
    player.getBoard().enchantMinion(index, "Modify Defense", modifyDefenseVal);
}

// note: this is an ability that effects more than one player
BlizzardAbility::BlizzardAbility() : ActivatedAbility{0, false, true} {}
BlizzardAbility::~BlizzardAbility() {}
void BlizzardAbility::doEffect(Player& player, int i) {
    for (int i = 0; i < player.getBoard().size(); i++) {
        player.getBoard().enchantMinion(i, "Modify Defense", -2);
    }
}

/* Activated Abilities for Minions: */

// deal 1 damage to target minion
NovicePyromancerAbility::NovicePyromancerAbility() : ActivatedAbility{1, true} {}
NovicePyromancerAbility::~NovicePyromancerAbility() {}
void NovicePyromancerAbility::doEffect(Player& player, int i) {
    player.getBoard().enchantMinion(i, "Modify Defense", -1);
}

// summon a 1/1 air elemental
ApprenticeSummonerAbility::ApprenticeSummonerAbility() : ActivatedAbility{1, false} {}
ApprenticeSummonerAbility::~ApprenticeSummonerAbility() {}
void ApprenticeSummonerAbility::doEffect(Player& player, int i) {
    if (player.getBoard().size() == 5) throw full_board{};
    // MinionPtr minionCard = std::dynamic_pointer_cast<MinionP>(createCard("Air Elemental", nullptr));
    else player.getBoard().addCard(std::dynamic_pointer_cast<Minion>(createCard("Air Elemental", nullptr)));
}

// summon up to three 1/1 air elementals
MasterSummonerAbility::MasterSummonerAbility() : ActivatedAbility{2, false} {}
MasterSummonerAbility::~MasterSummonerAbility() {}
void MasterSummonerAbility::doEffect(Player& player, int i) {
    if (player.getBoard().size() == 5) throw full_board{};
    else {
        int toadd = 3;
        while (player.getBoard().size() != 5 && toadd > 0) {
            player.getBoard().addCard(dynamic_pointer_cast<Minion>(createCard("Air Elemental", nullptr)));
            --toadd;
        }
    }
}

SilenceAbility::SilenceAbility(): ActivatedAbility{} {}
SilenceAbility::~SilenceAbility(){}
void SilenceAbility::doEffect(Player& player, int i)  { throw ability_silenced{}; } // this is supposed to do nothing

