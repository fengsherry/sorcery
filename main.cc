// This program implements the "Sorcery" game

#include <iostream>
#include <string>
#include <fstream>
#include "gamemaster.h"
using namespace std;

// helper function to find command line variabls
bool findIndex(int argc, char* argv[], string s, int& i) {
    for (int index = 1; index < argc; ++i) {
        if (argv[index] == s) {i = index; return true;}
    }
    return false;
}

void testCmdArg(string arg) { cout << "You have activated the " << arg << " command argument" << endl; }

int main(int argc, char *argv[]) {
    // potential command line arguments: -deck1 (filename), -deck2 (filename), -init (filename), -testing
    int i;
    bool deck1Flag, deck2Flag, initFlag, testingFlag;
    string deck1File, deck2File, initFile;
    if (findIndex(argc, argv, "-deck1", i)) {
        deck1Flag = true; deck1File = argv[i + 1];
        testCmdArg("deck1");
    }
    if (findIndex(argc, argv, "-deck2", i)) {
        deck2Flag = true; deck2File = argv[i + 1];
        testCmdArg("deck2");
    }
    if (findIndex(argc, argv, "-init", i)) {
        initFlag = true; initFile = argv[i + 1];
        testCmdArg("init");
    }
    if (findIndex(argc, argv, "-testing", i)) {
        testingFlag = true; 
        testCmdArg("testing");
    }

    // SET DECKS according to cmd line args, or default.deck
    ifstream in1 = deck1Flag ? ifstream(deck1File.c_str()) : ifstream("default.deck");
    ifstream in2 = deck2Flag ? ifstream(deck2File.c_str()) : ifstream("default.deck");
    string cardName;
    while (getline(in1, cardName)) {
        // (construct each card that corresponds to cardName)
    }
    while (getline(in2, cardName)) {
        // (construct each card that corresponds to cardName)
    }

    // initialize 2 decks - should this be done in GameMaster?
    Deck deck1; // {...}
    Deck deck2; // {...}



    // SET PLAYERS, ask players for their names
    cout << "Please enter player names: " << endl;
    string p1name, p2name;
    getline(cin, p1name); 
    getline(cin, p2name); 
    cout << "Player 1: " << p1name << "\nPlayer 2: " << p2name << endl;

    // initialize 2 players - should this be done in GameMaster?
    Player p1{p1name, 1};
    Player p2{p2name, 2};

    // initialize the game
    // GameMaster gm{p1name, p2name, deck1, deck2}; 

    bool turn = 0; // 0 for player 1's turn, 1 for player 2's turn
    string cmd;
    while (true) {
        cin >> cmd;
        if (cin.eof()) return 0;
        if (cmd == "help") { 

        } else if (cmd == "quit") {

        } else if (cmd == "draw") {

        } else if (cmd == "discard") { // only available in -testing mode; how to handle this?

        } else if (cmd == "attack") {

        } else if (cmd == "play") {

        } else if (cmd == "use") {

        } else if (cmd == "describe") {

        } else if (cmd == "hand") {

        } else if (cmd == "board") {

        } else if (cmd != "") {
            cout << "Not a valid command" << endl;
        } 
     }

}
