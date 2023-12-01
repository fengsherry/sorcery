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
    else if (i < 0 || i > player.getBoard().size()) throw outside_range();
    else  player.getBoard().destroyMinion(i - 1);
}

UnsummonAbility::UnsummonAbility() : ActivatedAbility{1} {}
UnsummonAbility::~UnsummonAbility() {}
void UnsummonAbility::doEffect(Player& player, int i) {
    player.getBoard().stripEnchants(i, *player); // remove any enchantments from minion
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
    // if (player.getBoard().size() == 5) throw full_hand(); // already checked in addCard() method
    // ressurect top minion in graveyard
    Minion* m = player.getGrave().getTop();
    player.getGrave().removeTop();

    int modifyDefenseVal = 1 - m->getDefense();
    player.getBoard().addCard(m);
    int index = player.getBoard().size() - 1;
    player.getBoard().enchantMinion(index, "Modify Defense", modifyDefenseVal);

    // if (DefaultMinion* dm = dynamic_cast<DefaultMinion*>(m)) {
    //     dm->setDefense(1);
    //     player.getHand().addCard(m);
    // } else {
    //     cout << "what??? how is this possible?? it shouldn't be possible." << endl;
    // }
    // player.getHand().addCard(m);

    // set defense to 1
}

// note: this is an ability that effects more than one player
BlizzardAbility::BlizzardAbility() : ActivatedAbility{3, true} {}
BlizzardAbility::~BlizzardAbility() {}
void BlizzardAbility::doEffect(Player& player, int i) {
    for (int i = 0; i < player.getBoard().size(); i++) {
        // decrease defense isn't implemented yet so doesn't work. 
        player.getBoard().enchantMinion(i, "Modify Defense", -2);
        // player.getBoard().getCard(i)->decreaseDefense(2);
    }
}
