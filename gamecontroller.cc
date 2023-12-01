#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "exceptions.h"
#include "gamecontroller.h"

#include "ascii_graphics.h"
#include "textdisplay.h"

GameController::GameController() {}
GameController::~GameController() {}

bool GameController::findIndex(int argc, char* argv[], string s, int& i) {
    for (int index = 1; index < argc; ++index) {
        if (argv[index] == s) {i = index; return true;}
    }
    return false;
}

void GameController::testCmdArg(string arg, string filename) { 
    td->displayMsg("You have activated the " + arg + " command argument, and " + filename + " file ");
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

    // create a new textdisplay
    td = new TextDisplay(&gm);

    //TEMP ____________________________________________________________________________________________________________________
    td->displayHand(1);
    //TEMP____________________________________________________________________________________________________________________

    string cmd;
    int arg1, arg2, arg3;
    gm.startTurn();
    string activePlayerName = gm.getActivePlayer().getName();
    string nonactivePlayerName = gm.getNonactivePlayer().getName();
    cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  It's your turn!" << endl;
    while (true) {
        try { // catches exception
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
                try {
                    CardPtr drawnCard = gm.getActivePlayer().drawCard();
                    cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  drew a " << drawnCard->getName() << endl;
                } catch (invalid_play e) {cout << e.what() << endl; }
                
            } else if (cmd == "discard") { // only available in -testing mode; how to handle this?

            } else if (cmd == "attack") {
                // attacks player or minion

                string args;
                int arg, arg2;
                getline(cin, args);
                istringstream iss(args);
                iss >> arg;
                
                if (iss >> arg2) { 
                    // "attack i j" - order minion i to attack nonactive player's minion j
                    MinionPtr attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                    MinionPtr victimMinion = gm.getNonactivePlayer().getBoard().getCard(arg2-1);
                    cout << activePlayerName << "'s minion, " << *attackingMinion << " is attacking " <<  nonactivePlayerName 
                    << "'s minion, " << *victimMinion << endl;

                    try {
                        // perform attack
                        gm.attackMinion(arg-1, arg2-1);
                        // output new states of minions
                        cout <<  attackingMinion->getName() << "'s defense remaining: " << attackingMinion->getDefense() << endl;
                        cout << victimMinion->getName() << "'s defense remaining: " << victimMinion->getDefense() << endl;
                    } catch (not_enough_action e) {
                        cout << e.what() << endl; // error message
                    }

                } else {
                    // "attack i" - order minion i to attack the nonactive player
                    cin.clear();

                    MinionPtr attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                    cout << activePlayerName << " is attacking " <<  nonactivePlayerName 
                    << " with " << *attackingMinion << endl;

                    try {
                        // perform attack
                        gm.attackPlayer(arg-1);
                        // output new states of players
                        cout << nonactivePlayerName << "'s life remaining: " << gm.getNonactivePlayer().getLife() << endl;
                        cout << endl;
                    } catch (not_enough_action e) {
                        cout << e.what() << endl; // error message
                    }
                }

            } else if (cmd == "play") {
                // version that plays minions and enchantments with no abilities
                
                vector<int> args;
                string line;
                int arg;
                getline(cin, line);
                istringstream iss(line);
                while (iss >> arg) { args.emplace_back(arg); }

                if (args.size() == 1) { // "play i" - minions, rituals, spells with no targets
                    cout << activePlayerName << " is playing " << *(gm.getActivePlayer().getHand().getCard(arg-1)) << endl;
                    try { 
                        gm.play(args[0]-1); 
                        cout << activePlayerName << "'s magic remaining: " << gm.getActivePlayer().getMagic() << endl;
                        cout << endl;
                    }
                    catch (not_enough_magic e) { cout << e.what() << endl;}
                    catch (no_target_provided e) { cout << e.what() << endl;}

                } else if (args.size() == 3) { // "play i p j" - enchantments, spells with targets
                    // identify target player
                    Player* targetPlayer;
                    if (args[1] != 1 && args[1] != 2) { cout << "Invalid player id." << endl; }
                    else if (args[1] == gm.getActivePlayer().getId()) { targetPlayer = &gm.getActivePlayer(); } 
                    else { targetPlayer = &gm.getNonactivePlayer(); }

                    Card* targetCard;
                    if (args[2] == 'r') {
                        cout << "targeting a ritual!" << endl;
                        targetCard = targetPlayer->getRitual().get();
                    }
                    else targetCard = targetPlayer->getBoard().getCard(args[2] - 1).get();
                    cout << activePlayerName << " is playing " << *(gm.getActivePlayer().getHand().getCard(args[0]-1)) << 
                    " on " << targetPlayer->getName() << "'s " << targetCard->getName() <<endl;

                    // play the card
                    try { 
                        gm.play(args[0]-1, args[2]-1, *targetPlayer);
                        cout << activePlayerName << "'s magic remaining: " << gm.getActivePlayer().getMagic() << endl;
                        cout << endl; 
                    } 
                    catch(not_enough_magic e) { cout << e.what() << endl; } 
                    catch(no_target_needed e) { cout << e.what() << endl; } 
                    catch(invalid_play e) { cout << e.what() << endl; }

                } else {
                    cout << "Incorrect input." << endl;
                }

                
            } else if (cmd == "use") {

            } else if (cmd == "describe") {

            } else if (cmd == "hand") {
                gm.getActivePlayer().TEST_printPlayerHand();

            } else if (cmd == "board") {
                gm.getActivePlayer().TEST_printPlayerBoard();

            } else if (cmd != "") {
                td->displayMsg("Not a valid command");
                // cout << "Not a valid command" << endl;
            } 


        } catch(out_of_range e) { cout << e.what() << endl; }
        
    }
}



