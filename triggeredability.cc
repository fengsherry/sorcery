#include "triggeredability.h"
#include "player.h"
#include "minion.h"
#include <iostream> //remove later

TriggeredAbility:: TriggeredAbility(TriggerType type, Player* owner, Minion* ownerMinion):
    type {type}, owner {owner}, ownerMinion {ownerMinion} {}

TriggerType TriggeredAbility::getType() {return type;}

void TriggeredAbility::setTargetPlayer(Player* targetPlayer) {
    targetPlayers.clear();
    targetPlayers.emplace_back(targetPlayer);
}
void TriggeredAbility::setTargetMinion(Minion* targetMinion) {
    targetMinions.clear();
    targetMinions.emplace_back(targetMinion);
}

void TriggeredAbility::setTargetPlayers(vector<Player*> targetPlayers) {targetPlayers = targetPlayers;}

void TriggeredAbility::setTargetMinions(vector<Minion*> targetMinions) {targetMinions = targetMinions;}

/* Dark Ritual */
DarkRitualAbility::DarkRitualAbility(Player* owner): 
TriggeredAbility{TriggerType::StartTurn, owner} {}


void DarkRitualAbility::applyAbility() {
    // at this point, the current activePlayer should already be set as targetPlayer
    if (owner == targetPlayers[0]) targetPlayers[0]->increaseMagic(1);
}

/* Aura of Power */
AuraOfPowerAbility::AuraOfPowerAbility(Player* owner):
TriggeredAbility{TriggerType::MinionEnter, owner} {}

void AuraOfPowerAbility::applyAbility() {
    // targetMinion (the minion that just entered) should be added to targetMinions
    if (owner->onBoard(targetMinions[0])) {
        targetMinions[0]->increaseAttack(1);
        targetMinions[0]->increaseDefence(1);
    }
    cout << "TEST: !!! increasing life and defence for " << targetMinions[0]->getName() << "!!!!" << endl;
}


/* Standstill */
StandstillAbility::StandstillAbility(Player* owner):
TriggeredAbility{TriggerType::MinionEnter, owner} {}

void StandstillAbility::applyAbility() {
    targetMinions[0]->destroy();
    cout << "!! triggering StandstillAbility for " << targetMinions[0]->getName() << "!!!!" << endl;
}


/* Bone Golem */
BoneGolemAbility::BoneGolemAbility(Player* owner, Minion* ownerMinion):
TriggeredAbility{TriggerType::MinionLeave, owner, ownerMinion} {}

void BoneGolemAbility::applyAbility() {
    ownerMinion->increaseAttack(1);
    ownerMinion->increaseDefence(1);
}


/* Fire Elemental */
FireElementalAbility::FireElementalAbility(Player* owner,  Minion* ownerMinion):
TriggeredAbility{TriggerType::MinionEnter, owner, ownerMinion} {}

void FireElementalAbility::applyAbility() {
    // targetMinons[0] was set to minion that just entered

    // deal damage if minion isn't owned by owner
    if (!owner->onBoard(targetMinions[0])) targetMinions[0]->increaseDefence(-1);

}

/* Potion Seller */
PotionSellerAbility::PotionSellerAbility(Player* owner, Minion* ownerMinion):
TriggeredAbility{TriggerType::EndTurn, owner, ownerMinion} {}

void PotionSellerAbility::applyAbility() {
    // targetPlayers[0] has been set to the activePlayer
    if (owner == targetPlayers[0]) {
        Board* b = &(owner->getBoard());
        for (int i = 0; i < b->size(); i++) {
            b->getCard(i)->increaseDefence(1);
        }
    }
}