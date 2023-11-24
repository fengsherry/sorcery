#include "ability.h"
using namespace std;

Ability::Ability(targetPlayers = vector<Player*> emptyPlayerVector, targetMinions = vector<Minion*> emptyMinionVector):
targetPlayers{targetPlayers}, targetMinions{targetMinions} {}

vector<Player*>& Ability::getTargetPlayers() {
    return targetPlayers;
}

vector<Minion*>& Ability::getTargetMinions() {
    return targetMinions;
}
