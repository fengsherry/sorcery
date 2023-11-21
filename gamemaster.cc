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

    Player p1, p2;
    p1.init(p1name, 1);
    p2.init(p2name, 2);

    cout << "Player " << p1.getId() << ": " << p1.getName() << endl;
    cout << "Player " << p2.getId() << ": " << p2.getName() << endl;

}

// SET DECKS, initialize Decks
void GameMaster::initDecks(ifstream& deck1In, ifstream& deck2In) {
    Deck deck1, deck2;
    deck1.init(deck1In);
    deck2.init(deck2In);

    cout << "Player 1's Deck: " << endl;
    deck1.TEMP_printDeck();
    cout << "Player 2's Deck: " << endl;
    deck2.TEMP_printDeck();
}

void GameMaster::endTurn() {
    ++turn;
    if (turn > numPlayers) {
        turn = 1;
    }

    // notify end of turn observers
}

void GameMaster::attackPlayer(int i) {
    Minion* attackingMinion = activePlayer->getMinion(i);
    int attackVal = attackingMinion->getAttack();
    nonactivePlayer->decreaseLife(attackVal);
}

GameMaster::~GameMaster() {} 
