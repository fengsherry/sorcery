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
    int life; // health points
    int magic; // way to place cards on the board, etc
    // Deck deck;
    // Hand hand;
    // Graveyard grave;
    // Ritual* ritual;

};


#endif
