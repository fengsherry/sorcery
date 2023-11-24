#include "ability.h"
using namespace std;

Ability::Ability(vector<Player*> targetPlayers, vector<Minion*> targetMinions):
targetPlayers{targetPlayers}, targetMinions{targetMinions} {}

vector<Player*>& Ability::getTargetPlayers() {
    return targetPlayers;
}

vector<Minion*>& Ability::getTargetMinions() {
    return targetMinions;
}
