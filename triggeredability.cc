#include "triggeredability.h"
#include "player.h"
#include "minion.h"
//#include "exceptions.h"
#include <iostream> //remove later

TriggeredAbility:: TriggeredAbility(TriggerType type, TriggerCardType cardType, Player* owner, MinionPtr ownerMinion):
    type {type}, cardType {cardType}, owner {owner}, ownerMinion {ownerMinion} {}


Player* TriggeredAbility::getOwner() {return owner;}

TriggerType TriggeredAbility::getType() {return type;}

Player* TriggeredAbility::getActivePlayer() {return activePlayer;}

TriggerCardType TriggeredAbility::getCardType() {return cardType;}

void TriggeredAbility::setEnoughCharge(bool b) { enoughCharge = b; } 

bool TriggeredAbility::getEnoughCharge() { return enoughCharge; } 

void TriggeredAbility::setOwnerMinion(MinionPtr m) {ownerMinion = m;}

void TriggeredAbility::setActivePlayer(Player* ap) {activePlayer = ap;}

void TriggeredAbility::setTargetPlayer(Player* targetPlayer) {
    targetPlayers.clear();
    targetPlayers.emplace_back(targetPlayer);
}
void TriggeredAbility::setTargetMinion(MinionPtr targetMinion) {
    targetMinions.clear();
    targetMinions.emplace_back(targetMinion);
}

void TriggeredAbility::setTargetPlayers(vector<Player*> targetPlayers) {targetPlayers = targetPlayers;}

void TriggeredAbility::setTargetMinions(vector<MinionPtr> targetMinions) {targetMinions = targetMinions;}

void TriggeredAbility::applyAbility() {
    if (cardType == TriggerCardType::Ritual) {
        owner->getRitual()->trigger(); // decreases the charge
    }
}

/* Dark Ritual */
DarkRitualAbility::DarkRitualAbility(Player* owner): 
TriggeredAbility{TriggerType::StartTurn, TriggerCardType::Ritual, owner} {}


void DarkRitualAbility::applyAbility() {
    cout << "!! triggering DarkRitualAbility for " << targetPlayers[0]->getName() << "!!!!" << endl;

    // at this point, the current activePlayer should already be set as targetPlayer
    
    if (owner == targetPlayers[0]) {
        targetPlayers[0]->increaseMagic(1);
        TriggeredAbility::applyAbility();
    }
}

/* Aura of Power */
AuraOfPowerAbility::AuraOfPowerAbility(Player* owner):
TriggeredAbility{TriggerType::MinionEnter, TriggerCardType::Ritual, owner} {}

void AuraOfPowerAbility::applyAbility() {
    cout << "!! triggering AuraOfPowerAbility for " << targetMinions[0]->getName() << "!!!!" << endl;

    // targetMinion (the minion that just entered) should be added to targetMinions
    if (owner->onBoard(targetMinions[0])) {
        targetMinions[0]->modifyAttack(1);
        targetMinions[0]->modifyDefence(1);
        TriggeredAbility::applyAbility();
    }
}


/* Standstill */
StandstillAbility::StandstillAbility(Player* owner):
TriggeredAbility{TriggerType::MinionEnter, TriggerCardType::Ritual, owner} {}

void StandstillAbility::applyAbility() {
    cout << "!! triggering StandstillAbility for " << targetMinions[0]->getName() << "!!!!" << endl;

    TriggeredAbility::applyAbility();
    targetMinions[0]->destroy();
}


/* Bone Golem */
BoneGolemAbility::BoneGolemAbility(Player* owner):
TriggeredAbility{TriggerType::MinionLeave, TriggerCardType::Minion, owner} {}

void BoneGolemAbility::applyAbility() {
    cout << "!! triggering BoneGolemAbility for " << targetMinions[0]->getName() << "!!!!" << endl;

    ownerMinion->modifyAttack(1);
    ownerMinion->modifyDefence(1);

}


/* Fire Elemental */
FireElementalAbility::FireElementalAbility(Player* owner):
TriggeredAbility{TriggerType::MinionEnter, TriggerCardType::Minion, owner} {}

void FireElementalAbility::applyAbility() {
    // targetMinons[0] was set to minion that just entered

    // deal damage if minion isn't owned by owner
    cout << "!! triggering FireElementalAbility for " << targetMinions[0]->getName() << "!!!!" << endl;
    bool opponentsMinion = !owner->onBoard(targetMinions[0]);
    if (opponentsMinion) targetMinions[0]->modifyDefence(-1); // error here
}

/* Potion Seller */
PotionSellerAbility::PotionSellerAbility(Player* owner):
TriggeredAbility{TriggerType::EndTurn, TriggerCardType::Minion, owner} {}

void PotionSellerAbility::applyAbility() {
    // targetPlayers[0] has been set to the activePlayer
    cout << "!! triggering PotionSellerAbility for " << targetPlayers[0]->getName() << "!!!!" << endl;

    if (owner == targetPlayers[0]) {
        Board* b = &(owner->getBoard());
        for (int i = 0; i < b->size(); i++) {
            b->getCard(i)->modifyDefence(1);
        }
    }

}



/* Haste */
HasteAbility::HasteAbility(MinionPtr ownerMinion):
TriggeredAbility{TriggerType::StartTurn, TriggerCardType::Minion, nullptr, ownerMinion} {}

void HasteAbility::applyAbility() {
    cout << "!! triggering HasteAbility for " << ownerMinion->getName() << "!!!!" << endl;
    ownerMinion->modifyAction(1);
}