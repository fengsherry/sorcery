// This is the public interface for a Player, representing one of two players of sorcery

#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Player {
    string name;
    int id; // player 1 or 2
    int life = 20; // health points
    int magic = 3; // way to place cards on the board, etc
    // Deck deck;
    // Hand hand; // players start with 5 cards in their hand
    // Graveyard grave;
    // Ritual* ritual;
    public:
        Player(string name, int id);
        ~Player();

};


#endif
