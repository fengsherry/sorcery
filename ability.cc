#include "ability.h"
using namespace std;

Ability::Ability(vector<Player*> targetPlayers, vector<MinionPtr> targetMinions):
targetPlayers{targetPlayers}, targetMinions{targetMinions} {}

vector<Player*>& Ability::getTargetPlayers() {
    return targetPlayers;
}

vector<MinionPtr>& Ability::getTargetMinions() {
    return targetMinions;
}
