// Public interface for Ability

#ifndef __ABILITY_H__
#define __ABILITY_H__
#include <vector>
using namespace std;

class Ability {
    vector<Player*> targetPlayers; 
    vector<Minion*> targetMinions;

    public:   
        Ability(targetPlayers = vector<Player*> emptyPlayerVector, targetMinions = vector<Minion*> emptyMinionVector); 
        bool applyAbility() = 0; 

        vector<Player*>& getTargetPlayers();
        vector<Minion*>& getTargetMinions();
}