// This is the public interface for a Player, representing one of two players of sorcery

#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
#include "boardelements.h"
#include "ritual.h"
using namespace std;

class Player {
    string name;
    int id; // player 1 or 2
    int life = 20; // health points
    int magic = 3; // way to place cards on the board, etc
    Deck deck;
    Hand hand; // players start with 5 cards in their hand
    Board board;
    Graveyard grave;
    Ritual* ritual;
 
 public:
    Player(); // default ctor to be called when GameMaster is initialized
    // Player(string name, int id);
    ~Player();

        void init(string name, int id);

        string getName() const;
        int getId() const;
        int getLife() const;
        int getMagic() const;
        Hand& getHand();
        Board& getBoard();

        void setLife(int n);
        void setMagic(int n);
        void increaseMagic(int n);
        void decreaseLife(int n);

        // plays the ith card int he player's hand with no target (i.e. minions, rituals, spells)
        // returns true if successful, false otherwise
        bool play(int i); 
        void init(string name, int id, ifstream& deckIn);
        
        void TEST_printPlayerDeck();
        void TEST_printPlayerHand();
        void TEST_printPlayerBoard();
};


#endif
