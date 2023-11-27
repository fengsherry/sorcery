#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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

    string cmd;
    int arg;
    gm.startTurn();
    string activePlayerName = gm.getActivePlayer().getName();
    string nonactivePlayerName = gm.getNonactivePlayer().getName();
    cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  It's your turn!" << endl;
    while (true) {
        
        cin >> cmd;

        if (cin.eof()) return;
        if (cmd == "help") { 

        } else if (cmd == "end") {
            gm.endTurn();
            // reset names with new pointer values
            activePlayerName = gm.getActivePlayer().getName(); 
            nonactivePlayerName = gm.getNonactivePlayer().getName();
            gm.startTurn();
            cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  It's your turn!" << endl;
        } else if (cmd == "quit") {

        } else if (cmd == "draw") {
            
        } else if (cmd == "discard") { // only available in -testing mode; how to handle this?

        } else if (cmd == "attack") {
            // basic version that only attacks player

            string args;
            int arg, arg2;
            getline(cin, args);
            istringstream iss(args);
            iss >> arg;
            
            if (iss >> arg2) { 
                // "attack i j" - order minion i to attack nonactive player's minion j
                Minion* attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                Minion* victimMinion = gm.getNonactivePlayer().getBoard().getCard(arg2-1);
                cout << activePlayerName << "'s minion, " << *attackingMinion << " is attacking " <<  nonactivePlayerName 
                << "'s minion, " << *victimMinion << endl;

                // perform attack
                bool success = gm.attackMinion(arg-1, arg2-1);  // DOESN'T WORK UNTIL WE IMPLEMENT DECORATOR

                // output new states of players
                if (!success) cout << attackingMinion->getName() << " has 0 action. Unable to attack." << endl; 
                else {
                    cout <<  attackingMinion->getName() << "'s defense remaining: " << attackingMinion->getDefense() << endl;
                    cout << victimMinion->getName() << "'s defense remaining: " << victimMinion->getDefense() << endl;
                }

            } else {
                // "attack i" - order minion i to attack the nonactive player
                cin.clear();

                Minion* attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                cout << activePlayerName << " is attacking " <<  nonactivePlayerName 
                << " with " << *attackingMinion << endl;

                // perform attack
                bool success = gm.attackPlayer(arg-1);

                // output new states of players
                if (!success) cout << attackingMinion->getName() << " has 0 action. Unable to attack." << endl; 
                if (success) cout << nonactivePlayerName << "'s life remaining: " << gm.getNonactivePlayer().getLife() << endl;
                
                cout << endl;

            }

        } else if (cmd == "play") {
            // currently the basic version that only plays a basic minion with no abilities
            
            cin >> arg;

            cout << activePlayerName << " is playing " << *(gm.getActivePlayer().getHand().getCard(arg-1)) << endl;
            bool playSuccess = gm.play(arg-1);
            if (!playSuccess) cout << "Not enough magic. Play failed." << endl;
            else cout << activePlayerName << "'s magic remaining: " << gm.getActivePlayer().getMagic() << endl;
            cout << endl;
        } else if (cmd == "use") {

        } else if (cmd == "describe") {

        } else if (cmd == "hand") {
            gm.getNonactivePlayer().TEST_printPlayerHand();

        } else if (cmd == "board") {
            gm.getActivePlayer().TEST_printPlayerBoard();

        } else if (cmd != "") {
            td.displayMsg("Not a valid command");
            // cout << "Not a valid command" << endl;
        } 
     }
}



