#include "triggeredability.h"
#include "player.h"
#include <iostream> //remove later

TriggeredAbility:: TriggeredAbility(TriggerType type, Player* owner):
    type {type}, owner {owner} {}

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
        // targetMinions[0]->increaseLife(1);
        // targetMinions[0]->increaseDefence(1);
        // increaseLife and increaseDefence not implemented
    }
    cout << "!!! increasing life and defence for " << targetMinions[0]->getName() << "!!!!" << endl;
}


/* Standstill */
StandstillAbility::StandstillAbility(Player* owner):
TriggeredAbility{TriggerType::MinionEnter, owner} {}

void StandstillAbility::applyAbility() {
    //targetMinion[0].destroy();
}


/* Bone Golem */
BoneGolemAbility::BoneGolemAbility(Player* owner):
TriggeredAbility{TriggerType::MinionLeave, owner} {}

void BoneGolemAbility::applyAbility() {
    // targetMinions[0] has been set to 
}


/* Fire Elemental */
FireElementalAbility::FireElementalAbility(Player* owner):
TriggeredAbility{TriggerType::MinionEnter, owner} {}

void FireElementalAbility::applyAbility() {}

/* Potion Seller */
PotionSellerAbility::PotionSellerAbility(Player* owner):
TriggeredAbility{TriggerType::EndTurn, owner} {}

void PotionSellerAbility::applyAbility() {}