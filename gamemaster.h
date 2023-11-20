// This is the public interface for GameMaster, representing the controls over a game of sorcery

#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__
#include <iostream>
#include <vector>
#include "player.h"
using namespace std;

class GameMaster {
    Player p1, p2;
    // vector<TriggeredAbility*> observers;
    
    public:
        GameMaster(string name1, string name2); // Deck should be a parameter later
        ~GameMaster();

        // methods correlating to commands recieved in main:
        void startTurn();
        void endTurn();

        void attackMinion();
        void attackPlayer();
        void activateAbility();

        void discard();
        void play();
        void notifyObservers();

        // displays
        void describe();
        void hand();
        void board();
};


#endif
