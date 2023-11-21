#include <fstream>
#include <string>
#include <iostream>
#include "gamemaster.h"
using namespace std;

GameMaster::GameMaster() {} 

// SET PLAYERS, ask Players for their names
void GameMaster::initPlayers() {
    string p1name, p2name;
    cout << "Please enter player names: " << endl;
    getline(cin, p1name); 
    getline(cin, p2name); 

    // initialize 2 players
    p1 = Player{p1name, 1};
    p2 = Player{p2name, 2};

    cout << "Player " << p1.getId() << ": " << p1.getName() << endl;
    cout << "Player " << p2.getId() << ": " << p2.getName() << endl;

}

// SET DECKS, initialize Decks
void GameMaster::initDecks(ifstream& deck1In, ifstream& deck2In) {
    string cardName;
    while (getline(deck1In, cardName)) {
        // (construct each card that corresponds to cardName)
    }
    while (getline(deck2In, cardName)) {
        // (construct each card that corresponds to cardName)
    }

    // initialize 2 decks - should this be done in GameMaster?
    Deck deck1; // {...}
    Deck deck2; // {...}
}

GameMaster::~GameMaster() {} 
