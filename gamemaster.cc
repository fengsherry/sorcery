#include <fstream>
#include <string>
#include <iostream>
#include "gamemaster.h"
#include "exceptions.h"
using namespace std;

GameMaster::GameMaster() {} 
GameMaster::~GameMaster() {} 


// SET PLAYERS, ask Players for their names
void GameMaster::initPlayers(ifstream& deck1In, ifstream& deck2In) {
    // players:
    string p1name, p2name;
    cout << "Please enter player names: " << endl;
    getline(cin, p1name); 
    getline(cin, p2name); 

    p1.init(p1name, 1, deck1In);
    p2.init(p2name, 2, deck2In);

    activePlayer = &p1;
    nonactivePlayer = &p2;

    cout << "Player " << p1.getId() << ": " << p1.getName() << "\n" << endl;
    cout << "Player " << p2.getId() << ": " << p2.getName() << "\n" << endl;

    p1.TEST_printPlayerDeck();
    p2.TEST_printPlayerDeck();

    p1.TEST_printPlayerHand();
    p2.TEST_printPlayerHand();

}

// // SET DECKS, initialize Decks
// void GameMaster::initDecks(ifstream& deck1In, ifstream& deck2In) {
//     Deck deck1, deck2;
//     deck1.init(deck1In);
//     deck2.init(deck2In);

//     cout << "Player 1's Deck: " << endl;
//     deck1.TEMP_printDeck();
//     cout << "Player 2's Deck: " << endl;
//     deck2.TEMP_printDeck();
// }

// starts a turn, switches active and nonactive players, notifies corresponding observers
void GameMaster::startTurn() {
    activePlayer->increaseMagic(1);
    activePlayer->getBoard().restoreAction();
    activePlayer->getHand().restoreAction(); // can we combine these two
    // notify
}

// ends a turn, notifies corresponding observers
void GameMaster::endTurn() {
    ++turn;
    if (turn > numPlayers) {
        turn = 1;
    }
    // notify end of turn observers
    swap(activePlayer, nonactivePlayer);
}

// NOT DONE YET
void GameMaster::attackMinion(int i, int j) { // i is attacker, j is victim
    Minion* attackingMinion = activePlayer->getBoard().getCard(i);
    Minion* victimMinion = nonactivePlayer->getBoard().getCard(j);

    // check for enough action#include <fstream>
#include <string>
#include <iostream>
#include "gamemaster.h"
#include "exceptions.h"
using namespace std;

GameMaster::GameMaster() {} 
GameMaster::~GameMaster() {} 


// SET PLAYERS, ask Players for their names
void GameMaster::initPlayers(ifstream& deck1In, ifstream& deck2In) {
    // players:
    string p1name, p2name;
    cout << "Please enter player names: " << endl;
    getline(cin, p1name); 
    getline(cin, p2name); 

    p1.init(p1name, 1, deck1In);
    p2.init(p2name, 2, deck2In);

    activePlayer = &p1;
    nonactivePlayer = &p2;

    cout << "Player " << p1.getId() << ": " << p1.getName() << "\n" << endl;
    cout << "Player " << p2.getId() << ": " << p2.getName() << "\n" << endl;

    p1.TEST_printPlayerDeck();
    p2.TEST_printPlayerDeck();

    p1.TEST_printPlayerHand();
    p2.TEST_printPlayerHand();

}

// // SET DECKS, initialize Decks
// void GameMaster::initDecks(ifstream& deck1In, ifstream& deck2In) {
//     Deck deck1, deck2;
//     deck1.init(deck1In);
//     deck2.init(deck2In);

//     cout << "Player 1's Deck: " << endl;
//     deck1.TEMP_printDeck();
//     cout << "Player 2's Deck: " << endl;
//     deck2.TEMP_printDeck();
// }

// starts a turn, switches active and nonactive players, notifies corresponding observers
void GameMaster::startTurn() {
    activePlayer->increaseMagic(1);
    activePlayer->getBoard().restoreAction();
    activePlayer->getHand().restoreAction(); // can we combine these two
    // notify
}

// ends a turn, notifies corresponding observers
void GameMaster::endTurn() {
    ++turn;
    if (turn > numPlayers) {
        turn = 1;
    }
    // notify end of turn observers
    swap(activePlayer, nonactivePlayer);
}

// NOT DONE YET
void GameMaster::attackMinion(int i, int j) { // i is attacker, j is victim
    MinionPtr attackingMinion = activePlayer->getBoard().getCard(i);
    MinionPtr victimMinion = nonactivePlayer->getBoard().getCard(j);

    // check for enough action
    if (attackingMinion->getAction() == 0) throw not_enough_action{*activePlayer}; 

    attackingMinion->setAction(0);
    int attackValAttacker = attackingMinion->getAttack();
    int attackValVictim = victimMinion->getAttack();
    // victimMinion->
    // activePlayer

}


void GameMaster::attackPlayer(int i) {
    MinionPtr attackingMinion = activePlayer->getBoard().getCard(i);

    // check for enough action
    if (attackingMinion->getAction() == 0) throw not_enough_action{*activePlayer}; 

    attackingMinion->setAction(0);
    int attackVal = attackingMinion->getAttack();
    nonactivePlayer->decreaseLife(attackVal);
}

void activateAbility();

void discard();

void GameMaster::play(int i) {
    activePlayer->play(i); // may throw exception
    activePlayer->getHand().removeCard(i);

    activePlayer->TEST_printPlayerHand();
    activePlayer->TEST_printPlayerBoard();
    activePlayer->TEST_printPlayerRitual();
}

void GameMaster::play(int i, int j, Player& targetPlayer) {
    activePlayer->play(i, j, targetPlayer);
    activePlayer->getHand().removeCard(i);

    activePlayer->TEST_printPlayerHand();
    activePlayer->TEST_printPlayerBoard();
}

void notifyObservers();

// displays some visual
void describe();
void hand();
void board();

int GameMaster::getTurn() {return turn;}
Player& GameMaster::getActivePlayer() {return *activePlayer;}
Player& GameMaster::getNonactivePlayer() {return *nonactivePlayer;}
Player& GameMaster::getPlayer(int i) {
    return (i == 1) ? p1 : p2;
}

    if (attackingMinion->getAction() == 0) throw not_enough_action{*activePlayer}; 

    attackingMinion->setAction(0);
    int attackValAttacker = attackingMinion->getAttack();
    int attackValVictim = victimMinion->getAttack();
    // victimMinion->
    // activePlayer

}


void GameMaster::attackPlayer(int i) {
    Minion* attackingMinion = activePlayer->getBoard().getCard(i);

    // check for enough action
    if (attackingMinion->getAction() == 0) throw not_enough_action{*activePlayer}; 

    attackingMinion->setAction(0);
    int attackVal = attackingMinion->getAttack();
    nonactivePlayer->decreaseLife(attackVal);
}

void activateAbility();

void discard();

void GameMaster::play(int i) {
    activePlayer->play(i); // may throw exception
    activePlayer->getHand().removeCard(i);

    activePlayer->TEST_printPlayerHand();
    activePlayer->TEST_printPlayerBoard();
    activePlayer->TEST_printPlayerRitual();
}

void GameMaster::play(int i, int j, Player& targetPlayer) {
    activePlayer->play(i, j, targetPlayer);
    activePlayer->getHand().removeCard(i);

    activePlayer->TEST_printPlayerHand();
    activePlayer->TEST_printPlayerBoard();
}

void notifyObservers();

// displays some visual
void describe();
void hand();
void board();

int GameMaster::getTurn() {return turn;}
Player& GameMaster::getActivePlayer() {return *activePlayer;}
Player& GameMaster::getNonactivePlayer() {return *nonactivePlayer;}
Player& GameMaster::getPlayer(int i) {
    return (i == 1) ? p1 : p2;
}
