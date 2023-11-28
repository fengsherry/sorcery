#include "triggeredability.h"
#include "player.h"
// #include <iostream> //remove later

TriggeredAbility:: TriggeredAbility(TriggerType type, vector<Player*> targetPlayers, vector<Minion*> targetMinions):
    type {type}, targetPlayers {targetPlayers}, targetMinions {targetMinions} {}

TriggerType TriggeredAbility::getType() {return type;}


/* Dark Ritual */
DarkRitualAbility::DarkRitualAbility(Player* targetPlayer): 
TriggeredAbility{TriggerType::StartTurn, vector<Player*>(), vector<Minion*>()} {
    targetPlayers.emplace_back(targetPlayer);
}

// DarkRitualAbility::addTarget(Player* targetPlayer) {
//     targetPlayer.emplace_back(targetPlayer);
// }

void DarkRitualAbility::applyAbility(Player* activePlayer) {
    if (activePlayer == targetPlayers[0]) targetPlayers[0]->increaseMagic(1);
    // cout << "triggering" << endl;
}


