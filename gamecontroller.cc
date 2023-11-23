#include <iostream>
#include <string>
#include <fstream>
#include "gamecontroller.h"

GameController::GameController() {}
GameController::~GameController() {}

bool GameController::findIndex(int argc, char* argv[], string s, int& i) {
    for (int index = 1; index < argc; ++index) {
        if (argv[index] == s) {i = index; return true;}
    }
    return false;
}

void GameController::testCmdArg(string arg, string filename) { 
    td.displayMsg("You have activated the " + arg + " command argument, and " + filename + " file ");
    // cout << "You have activated the " << arg << " command argument, and " << filename << " file " << endl; 
}

void GameController::go(int argc, char *argv[]) {
    // copy code from main.cc here

    // potential command line arguments: -deck1 (filename), -deck2 (filename), -init (filename), -testing
    int i;
    bool deck1Flag = false;
    bool deck2Flag = false;
    bool initFlag = false;
    bool testingFlag = false;
    string deck1File, deck2File, initFile;
    if (findIndex(argc, argv, "-deck1", i)) {
        deck1Flag = true; deck1File = argv[i + 1];
        testCmdArg("deck1", deck1File);
    }
    if (findIndex(argc, argv, "-deck2", i)) {
        deck2Flag = true; deck2File = argv[i + 1];
        testCmdArg("deck2", deck2File);
    }
    if (findIndex(argc, argv, "-init", i)) {
        initFlag = true; initFile = argv[i + 1];
        testCmdArg("init", initFile);
    }
    if (findIndex(argc, argv, "-testing", i)) {
        testingFlag = true; 
        testCmdArg("testing");
    }

    // create input file streams for each deck file location
    ifstream in1 = deck1Flag ? ifstream(deck1File.c_str()) : ifstream("default.deck");
    ifstream in2 = deck2Flag ? ifstream(deck2File.c_str()) : ifstream("default.deck");

    // initialize the game
    GameMaster gm{}; 

    // initialize Players, their Decks, and their Hands
    gm.initPlayers(in1, in2);

    int turn = 1; // 1 for player 1's turn, 2 for player 2's turn
    int numPlayers = 2;
    string cmd;
    int arg;
    while (true) {
        
        cin >> cmd;

        if (cin.eof()) return;
        if (cmd == "help") { 

        } else if (cmd == "end") {
            ++turn;
            if (turn > numPlayers) {
                turn = 1;
            }
        } else if (cmd == "quit") {

        } else if (cmd == "draw") {
            
        } else if (cmd == "discard") { // only available in -testing mode; how to handle this?

        } else if (cmd == "attack") {
            // basic version that only attacks player
            cin >> arg;
            gm.attackPlayer(arg);
        } else if (cmd == "play") {
            // currently the basic version that only plays a basic minion with no abilities
            cin >> arg;
            gm.play(arg);
        } else if (cmd == "use") {

        } else if (cmd == "describe") {

        } else if (cmd == "hand") {

        } else if (cmd == "board") {

        } else if (cmd != "") {
            td.displayMsg("Not a valid command");
            // cout << "Not a valid command" << endl;
        } 
     }
}



