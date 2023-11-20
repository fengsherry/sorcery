// This program implements the "Sorcery" game

#include <iostream>
#include <string>
#include <fstream>
#include "gamemaster.h"
using namespace std;

bool findIndex(int argc, char* argv[], string s, int* i) {
    for (int index = 0; index < argc; ++i) {
        if (argv[index] == s) *i = index; return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    // potential command line arguments: -deck1 (filename), -deck2 (filename), -init (filename), -testing
    int* i;
    bool deck1, deck2, init, testing;
    string deck1File, deck2File, initFile;
    if (findIndex(argc, argv, "-deck1", i)) deck1 = true; deck1File = argv[*i + 1];
    if (findIndex(argc, argv, "-deck2", i)) deck2 = true; deck2File = argv[*i + 1];
    if (findIndex(argc, argv, "-init", i)) init = true; initFile = argv[*i + 1];
    if (findIndex(argc, argv, "-testing", i)) testing = true; 

    // set decks according to cmd line args, or default.deck
    ifstream* in1 = deck1 ? new ifstream(deck1File.c_str()) : new ifstream("default.deck");
    ifstream* in2 = deck2 ? new ifstream(deck2File.c_str()) : new ifstream("default.deck");

    // asks players for their names
    cout << "Please enter player names: " << endl;
    string p1name, p2name;
    getline(cin, p1name); 
    getline(cin, p2name); 

    // initialize the game
    GameMaster gm{p1name, p2name};

}
