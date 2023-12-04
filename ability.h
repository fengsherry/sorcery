// Public interface for Ability

#ifndef __ABILITY_H__
#define __ABILITY_H__
#include <vector>
#include "player.h"
using namespace std;

class Ability {
    vector<Player*> targetPlayers; 
    vector<MinionPtr> targetMinions;

    public:   
        Ability(vector<Player*> targetPlayers = {}, vector<MinionPtr> targetMinions = {}); 
        virtual bool applyAbility() = 0; 

        vector<Player*>& getTargetPlayers();
        vector<MinionPtr>& getTargetMinions();
};

#endif
