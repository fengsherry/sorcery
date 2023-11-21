#include <fstream>
#include <string>
#include <iostream>
#include "gamemaster.h"
using namespace std;

GameMaster::GameMaster() {} 

// SET PLAYERS, ask players for their names
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

GameMaster::~GameMaster() {} 
