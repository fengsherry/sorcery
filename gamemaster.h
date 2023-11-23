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
    Deck d1, d2;
    int turn = 1; // 1 for player 1's turn, 2 for player 2's turn
    int numPlayers = 2;
    Player* activePlayer;
    Player* nonactivePlayer;
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

        bool attackMinion(int i, int j); // returns true if successfully attacked, returns false otherwise
        bool attackPlayer(int i); // returns true if successfully attacked, returns false otherwise
        void activateAbility();

        void discard();
        bool play(int i);
        void notifyObservers();

        // displays some visual
        void describe();
        void hand();
        void board();

        // getters and setters
        int getTurn();
        Player& getActivePlayer();
        Player& getNonactivePlayer();
};


#endif
