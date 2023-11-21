// This is the public interface for GameMaster, representing the controls over a game of sorcery

#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__
#include <iostream>
#include <vector>
#include "player.h"
#include "boardelements.h"
using namespace std;

class GameMaster {
    Player p1, p2;
    Deck d1, d2;
    // vector<TriggeredAbility*> observers;
    
    public:
        GameMaster(); 
        ~GameMaster();

        // methods to initialize the game
        void initPlayers();
        void initDecks(ifstream& deck1In, ifstream& deck2In);

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
