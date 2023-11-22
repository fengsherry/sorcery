// This is the public interface for GameMaster, representing a game of sorcery

#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__
#include <iostream>
#include <vector>
#include "player.h"
#include "boardelements.h"
using namespace std;

class GameMaster {
    Player p1, p2;
    // vector<TriggeredAbility*> observers;
    
    public:
        GameMaster(); 
        ~GameMaster();

        // methods to initialize the players
        void initPlayers(ifstream& deck1In, ifstream& deck2In);
        // void initDecks(ifstream& deck1In, ifstream& deck2In);

        // methods correlating to commands recieved in main:
        void startTurn();
        void endTurn();

        void attackMinion();
        void attackPlayer();
        void activateAbility();

        void discard();
        void play();
        void notifyObservers();

        // displays some visual
        void describe();
        void hand();
        void board();
};


#endif
