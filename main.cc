// This program implements the "Sorcery" game

#include <iostream>
#include <string>
#include <fstream>
#include "gamemaster.h"
using namespace std;

// helper function to find command line variabls
bool findIndex(int argc, char* argv[], string s, int* i) {
    for (int index = 0; index < argc; ++i) {
        if (argv[index] == s) *i = index; return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    // potential command line arguments: -deck1 (filename), -deck2 (filename), -init (filename), -testing
    int* i;
    bool deck1Flag, deck2Flag, initFlag, testingFlag;
    string deck1File, deck2File, initFile;
    if (findIndex(argc, argv, "-deck1", i)) deck1Flag = true; deck1File = argv[*i + 1];
    if (findIndex(argc, argv, "-deck2", i)) deck2Flag = true; deck2File = argv[*i + 1];
    if (findIndex(argc, argv, "-init", i)) initFlag = true; initFile = argv[*i + 1];
    if (findIndex(argc, argv, "-testing", i)) testingFlag = true; 

    // set decks according to cmd line args, or default.deck
    ifstream in1 = deck1Flag ? ifstream(deck1File.c_str()) : ifstream("default.deck");
    ifstream in2 = deck2Flag ? ifstream(deck2File.c_str()) : ifstream("default.deck");

    string cardName;
    while (getline(in1, cardName)) {
        // (construct the card that corresponds to cardName)
    }
    // initialize 2 decks
    Deck deck1; // = new Deck{...}
    Deck deck2; // = new Deck{...}


    // asks players for their names
    cout << "Please enter player names: " << endl;
    string p1name, p2name;
    getline(cin, p1name); 
    getline(cin, p2name); 

    // initialize 2 players
    // Player p1{ ... }
    // Player p2{ ... }

    // initialize the game
    GameMaster gm{p1name, p2name, deck1, deck2}; 

    bool turn = 0; // 0 for player 1's turn, 1 for player 2's turn
    while (true) {

    }

}
