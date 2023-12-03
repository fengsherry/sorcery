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
#include "graphicsdisplay.h"
using namespace std;

GameController::GameController() {}
GameController::~GameController() {}

bool GameController::findIndex(int argc, char* argv[], string s, int& i) {
    for (int index = 1; index < argc; ++index) {
        if (argv[index] == s) {i = index; return true;}
    }
    return false;
}

void GameController::testCmdArg(string arg, string filename) { 
    // cout << td << endl;
    td->displayMsg("You have activated the " + arg + " command argument, and " + filename + " file ");
    // cout << "You have activated the " << arg << " command argument, and " << filename << " file " << endl; 
}

void GameController::go(int argc, char *argv[]) {

    // create a new textdisplay
    td = new TextDisplay(&gm);

    // potential command line arguments: -deck1 (filename), -deck2 (filename), -init (filename), -testing
    int i;
    bool deck1Flag = false;
    bool deck2Flag = false;
    bool initFlag = false;
    bool testingFlag = false;
    bool graphicsFlag = false;
    string deck1File, deck2File, initFile;
    if (findIndex(argc, argv, "-deck1", i)) {
        deck1Flag = true; deck1File = argv[i + 1];
        testCmdArg("deck1", deck1File);
    }
    if (findIndex(argc, argv, "-deck2", i)) {
        deck2Flag = true; deck2File = argv[i + 1];
        testCmdArg("deck2", deck2File);
    }
    if (findIndex(argc, argv, "-init", i)) { // NOT IMPLEMENTED YET
        initFlag = true; initFile = argv[i + 1];
        testCmdArg("init", initFile);
    }
    if (findIndex(argc, argv, "-testing", i)) { // NOT IMPLEMENTED YET
        testingFlag = true; 
        testCmdArg("testing");
    }
    if (findIndex(argc, argv, "-graphics", i)) { 
        graphicsFlag = true; 
        testCmdArg("graphics");
    }


    // create input file streams for each deck file location
    ifstream in1 = deck1Flag ? ifstream(deck1File.c_str()) : ifstream("default.deck");
    ifstream in2 = deck2Flag ? ifstream(deck2File.c_str()) : ifstream("default.deck");

    // initialize the game
    GameMaster gm{};

    // create a new graphics display if required
    if (graphicsFlag) gd = new GraphicsDisplay{&gm};

    // initialize Players, their Decks, and their Hands
    gm.initPlayers(in1, in2);

    if (graphicsFlag) gd->displaySorceryBoard();

    

    //TEMP ____________________________________________________________________________________________________________________
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
                // call a method in text display to automatically print the help message
                // Commands: help -- Display this message.
                // end -- End the current player’s turn.
                // quit -- End the game.
                // attack minion other-minion -- Orders minion to attack other-minion.
                // attack minion -- Orders minion to attack the opponent.
                // play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.
                // use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player.
                // inspect minion -- View a minion’s card and all enchantments on that minion.
                // hand -- Describe all cards in your hand.
                // board -- Describe all cards on the board.

            } else if (cmd == "end") {
                gm.endTurn();
                // reset names with new pointer values
                activePlayerName = gm.getActivePlayer().getName(); 
                nonactivePlayerName = gm.getNonactivePlayer().getName();
                gm.startTurn();
                cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  It's your turn!" << endl;
            } else if (cmd == "quit") {
                break;
            } else if (cmd == "draw") {
                try {
                    CardPtr drawnCard = gm.getActivePlayer().drawCard();
                    cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  drew a " << drawnCard << endl;
                } catch (invalid_play e) {cout << e.what() << endl; }
                
            } else if (cmd == "discard") { // only available in -testing mode; how to handle this?
                int i;
                if (testingFlag && (cin >> i)) {
                    gm.getActivePlayer().getHand().removeCard(i-1);
                } else cout << "Not a valid command" << endl;
                gm.getActivePlayer().TEST_printPlayerHand();
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
                    cout << activePlayerName << "'s minion, " << attackingMinion << " is attacking " <<  nonactivePlayerName 
                    << "'s minion, " << victimMinion << endl;

                    try {
                        // perform attack
                        gm.attackMinion(arg-1, arg2-1);
                        // output new states of minions
                        attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                        victimMinion = gm.getNonactivePlayer().getBoard().getCard(arg2-1);
                        
                        if (attackingMinion->isDead()) cout << attackingMinion << " has died." << endl;
                        else cout << attackingMinion << "'s defense remaining: " << attackingMinion->getDefense() << endl;
                        if (victimMinion->isDead()) cout << victimMinion << " has died." << endl;
                        else cout << victimMinion << "'s defense remaining: " << victimMinion->getDefense() << endl;
                    } catch (not_enough_action e) {
                        cout << e.what() << endl; // error message
                    }

                } else {
                    // "attack i" - order minion i to attack the nonactive player
                    cin.clear();

                    MinionPtr attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                    cout << activePlayerName << " is attacking " <<  nonactivePlayerName 
                    << " with " << attackingMinion << endl;

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
                
                vector<int> args;
                string line;
                int arg;
                getline(cin, line);
                istringstream iss(line);
                while (iss >> arg) { args.emplace_back(arg); }

                if (args.size() == 1) { // "play i" - minions, rituals, spells with no targets
                    // check if i within range

                    cout << activePlayerName << " is playing " << gm.getActivePlayer().getHand().getCard(args[0]-1) << endl;
                    try { 
                        gm.play(args[0]-1); 
                        cout << activePlayerName << "'s magic remaining: " << gm.getActivePlayer().getMagic() << endl;
                        cout << endl;
                    }
                    catch (not_enough_magic e) { cout << e.what() << endl;}
                    catch (no_target_provided e) { cout << e.what() << endl;}

                } else if (args.size() == 3) { // "play i p j" - enchantments, spells with targets
                    // check if i and j within range

                    // identify target player
                    Player* targetPlayer;
                    if (args[1] != 1 && args[1] != 2) { cout << "Invalid player id." << endl; }
                    else if (args[1] == gm.getActivePlayer().getId()) { targetPlayer = &gm.getActivePlayer(); } 
                    else { targetPlayer = &gm.getNonactivePlayer(); }

                    // identify target card
                    Card* targetCard;
                    if (args[2] == 'r') {
                        cout << "targeting a ritual!" << endl;
                        targetCard = targetPlayer->getRitual().get();
                    }  
                    else targetCard = targetPlayer->getBoard().getCard(args[2] - 1).get();
                    cout << activePlayerName << " is playing " << gm.getActivePlayer().getHand().getCard(args[0]-1) << 
                    " on " << targetPlayer->getName() << "'s " << targetCard <<endl;

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
                vector<int> args;
                string line;
                int arg;
                getline(cin, line);
                istringstream iss(line);
                while (iss >> arg) { args.emplace_back(arg); }

                // use i        (activated ability without target)
                if (args.size() == 1) {
                    // check if i within range
                    cout << activePlayerName << " is using " << gm.getActivePlayer().getBoard().getCard(args[0]-1) << "'s activated ability" << endl;

                    // use the ability
                    try {
                        gm.useAbility(args[0]-1);
                    } 
                    catch (no_target_provided e) { cout << e.what() << endl; }
                    catch (not_enough_magic e) { cout << e.what() << endl; } 
                    catch (not_enough_magic e) { cout << e.what() << endl; }
                    catch (invalid_play e) { cout << e.what() << endl; }
                }
                
                // use i p j    (activated ability with target)
                else if (args.size() == 3) {
                    // check if i and j within range

                    // identify target player
                    Player* targetPlayer;
                    if (args[1] != 1 && args[1] != 2) { cout << "Invalid player id." << endl; }
                    else if (args[1] == gm.getActivePlayer().getId()) { targetPlayer = &gm.getActivePlayer(); } 
                    else { targetPlayer = &gm.getNonactivePlayer(); }

                    // // identify target card
                    // Card* targetCard = targetPlayer->getBoard().getCard(args[2] - 1);

                    cout << activePlayerName << " is using " << gm.getActivePlayer().getBoard().getCard(args[0]) << 
                    "'s activated ability on " << targetPlayer->getName() << "'s " << targetPlayer->getBoard().getCard(args[2]-1) << endl;

                    // use the ability
                    try {
                        gm.useAbility(args[0]-1, args[2]-1, *targetPlayer);
                    } 
                    catch (no_target_needed e) { cout << e.what() << endl; }
                    catch (not_enough_magic e) { cout << e.what() << endl; } 
                    catch (not_enough_magic e) { cout << e.what() << endl; }
                    catch (invalid_play e) { cout << e.what() << endl; }

                }

                else {
                    cout << "Incorrect input." << endl;
                }

                

            } else if (cmd == "describe") {
                int i;
                cin >> i;
                gm.getActivePlayer().getBoard().getCard(i-1)->TEST_printInspectMinion();

            } else if (cmd == "hand") {
                gm.getActivePlayer().TEST_printPlayerHand();
                td->displayHand(1);

            } else if (cmd == "board") {
                gm.getActivePlayer().TEST_printPlayerBoard();
                // td->displaySorceryBoard();
                if (graphicsFlag) gd->displaySorceryBoard();

            } else if (cmd == "grave") {
                gm.getActivePlayer().TEST_printPlayerGrave();
            } else if (cmd != "") {
                td->displayMsg("Not a valid command");
                // cout << "Not a valid command" << endl;
            } 

        } catch(out_of_range e) { cout << e.what() << endl; }
        
    }
}
