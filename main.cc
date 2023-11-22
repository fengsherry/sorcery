// This program implements the "Sorcery" game

// #include <iostream>
// #include <string>
// #include <fstream>
#include "gamemaster.h"
#include "gamecontroller.h"
using namespace std;

/* moved to .go() method in GameController */
// // helper function to find command line variables
// bool findIndex(int argc, char* argv[], string s, int& i) {
//     for (int index = 1; index < argc; ++index) {
//         if (argv[index] == s) {i = index; return true;}
//     }
//     return false;
// }

// void testCmdArg(string arg, string filename = "n/a") { 
//     cout << "You have activated the " << arg << " command argument, and " << filename << " file " << endl; 
// }

int main(int argc, char *argv[]) {
    GameController controller;
    controller.go(argc, argv);
    
    /* moved to .go() method in GameController */
    // // potential command line arguments: -deck1 (filename), -deck2 (filename), -init (filename), -testing
    // int i;
    // bool deck1Flag = false;
    // bool deck2Flag = false;
    // bool initFlag = false;
    // bool testingFlag = false;
    // string deck1File, deck2File, initFile;
    // if (findIndex(argc, argv, "-deck1", i)) {
    //     deck1Flag = true; deck1File = argv[i + 1];
    //     testCmdArg("deck1", deck1File);
    // }
    // if (findIndex(argc, argv, "-deck2", i)) {
    //     deck2Flag = true; deck2File = argv[i + 1];
    //     testCmdArg("deck2", deck2File);
    // }
    // if (findIndex(argc, argv, "-init", i)) {
    //     initFlag = true; initFile = argv[i + 1];
    //     testCmdArg("init", initFile);
    // }
    // if (findIndex(argc, argv, "-testing", i)) {
    //     testingFlag = true; 
    //     testCmdArg("testing");
    // }

    // // create input file streams for each deck file location
    // ifstream in1 = deck1Flag ? ifstream(deck1File.c_str()) : ifstream("default.deck");
    // ifstream in2 = deck2Flag ? ifstream(deck2File.c_str()) : ifstream("default.deck");

    // // initialize the game
    // GameMaster gm{}; 

    // // initialize Players
    // gm.initPlayers(in1, in2);

    // int turn = 1; // 1 for player 1's turn, 2 for player 2's turn
    // int numPlayers = 2;
    // string cmd;
    // int arg;
    // while (true) {
        
    //     cin >> cmd;

    //     if (cin.eof()) return 0;
    //     if (cmd == "help") { 

    //     } else if (cmd == "end") {
    //         ++turn;
    //         if (turn > numPlayers) {
    //             turn = 1;
    //         }
    //     } else if (cmd == "quit") {

    //     } else if (cmd == "draw") {
            
    //     } else if (cmd == "discard") { // only available in -testing mode; how to handle this?

    //     } else if (cmd == "attack") {
    //         // basic version that only attacks player
    //         cin >> arg;
    //         gm.attackPlayer();
    //     } else if (cmd == "play") {

    //     } else if (cmd == "use") {

    //     } else if (cmd == "describe") {

    //     } else if (cmd == "hand") {

    //     } else if (cmd == "board") {

    //     } else if (cmd != "") {
    //         cout << "Not a valid command" << endl;
    //     } 
    //  }

}
