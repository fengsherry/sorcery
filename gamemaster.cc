#include <fstream>
#include <string>
#include <iostream>
#include "gamemaster.h"
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

void attackMinion();


bool GameMaster::attackPlayer(int i) {
    Minion* attackingMinion = activePlayer->getBoard().getCard(i);

    if (attackingMinion->getAction() == 0) { // check for enough action
        cout << attackingMinion->getName() << " has 0 action. Unable to attack." << endl; // this shouldn't be here
        return false;
    }

    attackingMinion->setAction(0);
    int attackVal = attackingMinion->getAttack();
    nonactivePlayer->decreaseLife(attackVal);
    return true;
}

void activateAbility();

void discard();

void GameMaster::play(int i) {
    activePlayer->play(i);
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
