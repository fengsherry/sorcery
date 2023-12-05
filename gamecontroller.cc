#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include "exceptions.h"
#include "gamecontroller.h"
#include "ascii_graphics.h"
#include "sorcerydisplay.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "sorceryutil.h"
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
    cout << "You have activated the " + arg + " command argument, and " + filename + " file " << endl;
}

void GameController::notifyDisplays() {
    for (auto display : displays) {
        display->displaySorceryBoard();
    }
}

// describe minion
void GameController::notifyDisplays(MinionPtr m) {
    for (auto display : displays) {
        display->displayMinion(m);
    }
}

// hand
void GameController::notifyDisplays(int p) {
    for (auto display : displays) {
        display->displayHand(p);
    }
}

// message
void GameController::notifyDisplays(string msg, int p) {
    notifyDisplays(vector<string>{msg}, p);
    // for (auto display : displays) {
    //     cout << "HELLO" << endl;
    //     vector<string> messages = {msg};
    //     notifyDisplays(messages, p);
    //     // display->displayMsg(msg, p);
    // }
}

// multiple messages
void GameController::notifyDisplays(vector<string> msg, int p) {
    for (auto display : displays) {
        // cout << "hi2" << endl;
        display->displayMsg(msg, p);
    }
}

void GameController::notifyDisplaysErr(string err, int p) {
    for (auto display : displays) {
        display->displayErrMsg(err, p);
    }
}

void GameController::go(int argc, char *argv[]) {
    // create a new textdisplay
    // td = new TextDisplay(&gm);
    displays.emplace_back(new TextDisplay(&gm));

    // potential command line arguments: -deck1 (filename), -deck2 (filename), -init (filename), -testing
    int i;
    bool deck1Flag = false;
    bool deck2Flag = false;
    bool initFlag = false;
    bool testingFlag = false;
    bool graphicsFlag = false;
    string deck1File, deck2File, initFile;
    ifstream file(initFile);
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
    if (findIndex(argc, argv, "-testing", i)) { // NOT IMPLEMENTED YET // NOT IMPLEMENTED YET
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
    // GameMaster gm{};

    // create a new textdisplay
    // td = new TextDisplay(&gm);

    // create a new graphics display if required
    // if (graphicsFlag) gd = new GraphicsDisplay{&gm};
    if (graphicsFlag) displays.emplace_back(new GraphicsDisplay{&gm});

    // initialize Players, their Decks, and their Hands
    notifyDisplays("Please enter player names.", 0);
    gm.initPlayers(in1, in2, testingFlag); 

    if (graphicsFlag) displays[1]->displaySorceryBoard();
    
    string cmds, cmd; // cmds is a line, cmd is the first "word" in that line
    int arg1, arg2, arg3;
    srand(static_cast<unsigned>(time(0)));
    gm.startTurn();
    string activePlayerName = gm.getActivePlayer().getName();
    string nonactivePlayerName = gm.getNonactivePlayer().getName();
    notifyDisplays("Player " + to_string(gm.getTurn()) + ": " + activePlayerName + "  It's your turn!", gm.getActivePlayer().getId());
    // cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  It's your turn!" << endl;
    while (true) {
        try { // catches exception
            if (cin.eof()) return;
            if (initFlag && getline(file, cmds)) {
                // we've already read into cmd
            }  else getline(cin, cmds);
            istringstream iss(cmds);

            iss >> cmd;

            if (cmd == "help") {  // only shows in textdisplay
                string helpmsg = 
                "Commands: \n\thelp -- Display this message.\n"
                "\tend -- End the current player\'s turn.\n"
                "\tquit -- End the game.\n"
                "\tattack minion other-minion -- Orders minion to attack other-minion.\n"
                "\tattack minion -- Orders minion to attack the opponent.\n"
                "\tplay card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n"
                "\tuse minion [target-player target-card] -- Use minion\'s special ability, optionally targeting target-card owned by target-player.\n"
                "\tinspect minion -- View a minion\'s card and all enchantments on that minion.\n"
                "\thand -- Describe all cards in your hand.\n"
                "\tboard -- Describe all cards on the board.";

                displays[0]->displayMsg(vector<string>{helpmsg});

            } else if (cmd == "end") {
                gm.endTurn();
                notifyDisplays();
                // reset names with new pointer values
                activePlayerName = gm.getActivePlayer().getName(); 
                nonactivePlayerName = gm.getNonactivePlayer().getName();
                gm.startTurn();
                notifyDisplays("Player " + to_string(gm.getTurn()) + ": " + activePlayerName + "  It's your turn!", gm.getActivePlayer().getId());
                // cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  It's your turn!" << endl;
            } else if (cmd == "quit") {
                break;
            } else if (testingFlag && cmd == "draw") {
                try {
                    CardPtr drawnCard = gm.getActivePlayer().drawCard();
                    notifyDisplays("Player " + to_string(gm.getTurn()) + ": " + activePlayerName + "  drew a " + drawnCard->getName(), gm.getActivePlayer().getId());
                    // cout << "Player " << gm.getTurn() << ": " << activePlayerName << "  drew a " << drawnCard << endl;
                } 
                catch (invalid_play &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                catch (full_hand &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                catch (deck_empty &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                
            } else if (testingFlag && cmd == "discard") { // only available in -testing mode; how to handle this?
                int i;
                iss >> i;
                checkRange(i, gm.getActivePlayer().getHand().getSize()); // may throw control to next iteration of while loop, skipping below code
                gm.getActivePlayer().getHand().removeCard(i-1);
                // if (testingFlag && (iss >> i)) {
                //     gm.getActivePlayer().getHand().removeCard(i-1);
                // } else notifyDisplaysErr("Not a valid command", gm.getActivePlayer().getId());
                // gm.getActivePlayer().TEST_printPlayerHand();
            } else if (cmd == "attack") {
                // attacks player or minion

                string args;
                int arg, arg2;
                // getline(cin, args);
                // istringstream iss(args);
                iss >> arg;
                checkRange(arg, gm.getActivePlayer().getBoard().getBoardSize());
                
                if (iss >> arg2) { 
                    checkRange(arg2, gm.getNonactivePlayer().getBoard().getBoardSize());
                    // "attack i j" - order minion i to attack nonactive player's minion j
                    MinionPtr attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                    MinionPtr victimMinion = gm.getNonactivePlayer().getBoard().getCard(arg2-1);
                    
                    // cout << activePlayerName << "'s minion, " << attackingMinion << " is attacking " <<  nonactivePlayerName 
                    // << "'s minion, " << victimMinion << endl;

                    try {
                        // minions
                        attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                        victimMinion = gm.getNonactivePlayer().getBoard().getCard(arg2-1);
                        // perform attack
                        gm.attackMinion(arg-1, arg2-1, &attackingMinion, &victimMinion);

                        string s = activePlayerName + "'s minion, " + attackingMinion->getDefaultMinionName() + " has attacked " +  nonactivePlayerName 
                                    + "'s minion, " + victimMinion->getDefaultMinionName();  
                        string s1, s2;
                        // cout << "in game controller: " << attackingMinion.get() << endl;
                        // cout << "attack: " << attackingMinion->getAttack() << endl;
                        // cout << "defense: " << attackingMinion->getDefense() << endl;
                        // cout << "action: " << attackingMinion->getAction() << endl;
                        if (attackingMinion->isDead()) {
                            s1 = attackingMinion->getDefaultMinionName() + " has died.";
                        } else {
                            s1 = attackingMinion->getDefaultMinionName() + "'s defense remaining: " + to_string(attackingMinion->getDefense());
                        }
                        if (victimMinion->isDead()) {
                            s2 = victimMinion->getDefaultMinionName() + " has died.";
                        } else {
                            s2 = victimMinion->getDefaultMinionName() + "'s defense remaining: " + 
                            to_string(victimMinion->getDefense());
                        }
                        vector<string> msg = {s, s1, s2};
                        
                        notifyDisplays(msg, gm.getActivePlayer().getId());
                    } catch (not_enough_action &e) {
                        notifyDisplaysErr(e.what(), gm.getActivePlayer().getId());
                        // cout << e.what() << endl; // error message
                    }
                    

                } else {
                    // "attack i" - order minion i to attack the nonactive player
                    // cin.clear();

                    MinionPtr attackingMinion = gm.getActivePlayer().getBoard().getCard(arg-1);
                    
                    // cout << activePlayerName << " is attacking " <<  nonactivePlayerName 
                    // << " with " << attackingMinion << endl;

                    try {
                        // perform attack
                        gm.attackPlayer(arg-1);
                        // output new states of players
                        vector<string> msg;
                        msg.emplace_back(activePlayerName + " has attacked " +  nonactivePlayerName + " with " + attackingMinion->getDefaultMinionName(), gm.getActivePlayer().getId());
                        msg.emplace_back(nonactivePlayerName + "'s life remaining: " + to_string(gm.getNonactivePlayer().getLife()), gm.getActivePlayer().getId());
                        // notifyDisplays(activePlayerName + " has attacked " +  nonactivePlayerName + " with " + attackingMinion->getDefaultMinionName(), gm.getActivePlayer().getId());
                        // notifyDisplays(nonactivePlayerName + "'s life remaining: " + to_string(gm.getNonactivePlayer().getLife()), gm.getActivePlayer().getId());
                        // cout << nonactivePlayerName << "'s life remaining: " << gm.getNonactivePlayer().getLife() << endl;
                        // cout << endl;
                        notifyDisplays(msg, gm.getActivePlayer().getId());
                    } catch (not_enough_action e) {
                        notifyDisplaysErr(e.what(), gm.getActivePlayer().getId());
                        // cout << e.what() << endl; // error message
                    }
                    
                }

            } else if (cmd == "play") {
                
                vector<int> args;
                string line;
                int arg;
                // getline(cin, line);
                // istringstream iss(line);
                while (iss >> arg) { args.emplace_back(arg); }

                if (args.size() == 1) { // "play i" - minions, rituals, spells with no targets
                    // check if i within range
                    checkRange(args[0], gm.getActivePlayer().getHand().getSize());
                    string s = activePlayerName + " has played " + gm.getActivePlayer().getHand().getCard(args[0]-1)->getName();
                    
                    // cout << activePlayerName << " is playing " << gm.getActivePlayer().getHand().getCard(args[0]-1) << endl;
                    try { 
                        gm.play(args[0]-1);
                        vector<string> msg;
                        msg.emplace_back(s);
                        msg.emplace_back(activePlayerName + "'s magic remaining: " + to_string(gm.getActivePlayer().getMagic()));
                        notifyDisplays(msg, gm.getActivePlayer().getId()); 
                        // notifyDisplays(activePlayerName + " has played " + gm.getActivePlayer().getHand().getCard(args[0]-1)->getName(), gm.getActivePlayer().getId());
                        // notifyDisplays(activePlayerName + "'s magic remaining: " + to_string(gm.getActivePlayer().getMagic()), gm.getActivePlayer().getId());
                        // cout << activePlayerName << "'s magic remaining: " << gm.getActivePlayer().getMagic() << endl;
                        // cout << endl;
                    }
                    catch (not_enough_magic &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId());}
                    catch (no_target_provided &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId());}

                } else if (args.size() == 3) { // "play i p j" - enchantments, spells with targets
                    // check if i and j within range
                    checkRange(args[0], gm.getActivePlayer().getHand().getSize());
                    if (args[1] != 'r' && args[1] != 1 && args[2] != 2) throw out_of_range{"Out of range."};

                    // identify target player
                    Player* targetPlayer;
                    if (args[1] != 1 && args[1] != 2) { notifyDisplaysErr("Invalid player id.", gm.getActivePlayer().getId()); }
                    else if (args[1] == gm.getActivePlayer().getId()) { targetPlayer = &gm.getActivePlayer(); } 
                    else { targetPlayer = &gm.getNonactivePlayer(); }

                    checkRange(args[2], targetPlayer->getBoard().getBoardSize());

                    // identify target card
                    Card* targetCard;
                    if (args[2] == 'r') {
                        targetCard = targetPlayer->getRitual().get();
                    }  
                    else targetCard = targetPlayer->getBoard().getCard(args[2] - 1).get();
                    string s = activePlayerName + " has played " + gm.getActivePlayer().getHand().getCard(args[0]-1)->getName() + 
                                    " on " + targetPlayer->getName() + "'s " + targetCard->getName();
                    // notifyDisplays(activePlayerName + " is playing " + gm.getActivePlayer().getHand().getCard(args[0]-1)->getName() + 
                    //                 " on " + targetPlayer->getName() + "'s " + targetCard->getName(), gm.getActivePlayer().getId());
                    // cout << activePlayerName << " is playing " << gm.getActivePlayer().getHand().getCard(args[0]-1) << 
                    // " on " << targetPlayer->getName() << "'s " << targetCard <<endl;

                    // play the card
                    try { 
                        gm.play(args[0]-1, args[2]-1, *targetPlayer);
                        vector<string> msg;
                        msg.emplace_back(s);
                        msg.emplace_back(activePlayerName + "'s magic remaining: " + to_string(gm.getActivePlayer().getMagic()));
                        // notifyDisplays(activePlayerName + "'s magic remaining: " + to_string(gm.getActivePlayer().getMagic()), gm.getActivePlayer().getId());
                        // cout << activePlayerName << "'s magic remaining: " << gm.getActivePlayer().getMagic() << endl;
                        // cout << endl; 
                    } 
                    catch(not_enough_magic &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); } 
                    catch(no_target_needed &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); } 
                    catch(invalid_play &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }

                } else {
                    notifyDisplaysErr("Incorrect input.", gm.getActivePlayer().getId());
                    // cout << "Incorrect input." << endl;
                }

                
            } else if (cmd == "use") {
                vector<int> args;
                string line;
                int arg;
                // getline(cin, line);
                // istringstream iss(line);
                while (iss >> arg) { args.emplace_back(arg); }

                // use i        (activated ability without target)
                if (args.size() == 1) {
                    // check if i within range
                    checkRange(args[0], gm.getActivePlayer().getBoard().getBoardSize());
                    notifyDisplays(activePlayerName + " is using " + gm.getActivePlayer().getBoard().getCard(args[0]-1)->getName() + "'s activated ability", gm.getActivePlayer().getId());
                    // cout << activePlayerName << " is using " << gm.getActivePlayer().getBoard().getCard(args[0]-1) << "'s activated ability" << endl;

                    // use the ability
                    try {
                        gm.useAbility(args[0]-1);
                    } 
                    catch (no_target_provided &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                    catch (not_enough_magic &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); } 
                    catch (not_enough_magic &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                    catch (invalid_play &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                    catch (ability_silenced &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                }
                
                // use i p j    (activated ability with target)
                else if (args.size() == 3) {
                    // check if i and j within range
                    checkRange(args[0], gm.getActivePlayer().getBoard().getBoardSize());
                    checkRange(args[1], 2);

                    // identify target player
                    Player* targetPlayer;
                    if (args[1] != 1 && args[1] != 2) { notifyDisplaysErr("Invalid player id.", gm.getActivePlayer().getId()); }
                    else if (args[1] == gm.getActivePlayer().getId()) { targetPlayer = &gm.getActivePlayer(); } 
                    else { targetPlayer = &gm.getNonactivePlayer(); }

                    checkRange(args[2], targetPlayer->getBoard().getBoardSize());

                    // // identify target card
                    // Card* targetCard = targetPlayer->getBoard().getCard(args[2] - 1);

                    notifyDisplays(activePlayerName + " is using " + gm.getActivePlayer().getBoard().getCard(args[0])->getName() + 
                                    "'s activated ability on " + targetPlayer->getName() + "'s " + targetPlayer->getBoard().getCard(args[2]-1)->getName(),
                                    gm.getActivePlayer().getId());
                    // cout << activePlayerName << " is using " << gm.getActivePlayer().getBoard().getCard(args[0]) << 
                    // "'s activated ability on " << targetPlayer->getName() << "'s " << targetPlayer->getBoard().getCard(args[2]-1) << endl;

                    // use the ability
                    try {
                        gm.useAbility(args[0]-1, args[2]-1, *targetPlayer);
                    } 
                    catch (no_target_needed &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                    catch (not_enough_magic &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); } 
                    catch (not_enough_magic &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                    catch (invalid_play &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
                    catch (ability_silenced &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }

                }

                else {
                    notifyDisplaysErr("Incorrect input.", gm.getActivePlayer().getId());
                    // cout << "Incorrect input." << endl;
                }

            } else if (cmd == "inspect") {
                int i;
                // cin >> i;
                iss >> i;
                checkRange(i, gm.getActivePlayer().getBoard().getBoardSize());

                try {
                    if (i > gm.getPlayer(gm.getActivePlayer().getId()).getBoard().size()) {
                        throw invalid_card_inspect();
                    }
                    notifyDisplays(gm.getActivePlayer().getBoard().getCard(i-1));
                } catch ( invalid_inspect_type &e ) {
                    notifyDisplaysErr(e.what(), gm.getActivePlayer().getId());
                } catch ( invalid_card_inspect &e ) {
                    notifyDisplaysErr(e.what(), gm.getActivePlayer().getId());
                } catch ( dne_card_inspect &e ) {
                    notifyDisplaysErr(e.what(), gm.getActivePlayer().getId());
                }
                // if (!(gm.getActivePlayer().getBoard().getCard(i-1)->getType() == CardType::Minion)){
                //     notifyDisplaysErr("Try again, this card is not a Minion.", gm.getActivePlayer().getId());
                // } else if (i > gm.getPlayer(gm.getActivePlayer().getId()).getBoard().size()) {
                //     notifyDisplaysErr("Try again, this card is not on the board.", gm.getActivePlayer().getId());
                // } else {
                //     notifyDisplays(gm.getActivePlayer().getBoard().getCard(i-1));
                // }

                // gm.getActivePlayer().getBoard().getCard(i-1)->TEST_printInspectMinion();
                // td->displayMinion(gm.getActivePlayer().getBoard().getCard(i-1));

            } else if (cmd == "hand") {
                // gm.getActivePlayer().TEST_printPlayerHand();
                notifyDisplays(gm.getActivePlayer().getId());

            } else if (cmd == "board") {
                gm.getActivePlayer().TEST_printPlayerBoard();
                notifyDisplays();

            } else if (cmd == "grave") {
                // gm.getActivePlayer().TEST_printPlayerGrave();

            } else if (cmd != "") {
                notifyDisplays("Not a valid command", gm.getActivePlayer().getId());
            } 
            // notifyDisplays();
            // if (graphicsFlag) displays[1]->displaySorceryBoard();
        } catch(out_of_range &e) { notifyDisplaysErr(e.what(), gm.getActivePlayer().getId()); }
        
    }
}
