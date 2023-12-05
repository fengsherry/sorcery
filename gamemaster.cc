#include <string>
#include <iostream>
#include "gamemaster.h"
#include "exceptions.h"
using namespace std;

GameMaster::GameMaster() {}; 
GameMaster::~GameMaster() {}


// SET PLAYERS, ask Players for their names
void GameMaster::initPlayers(vector<string>names, ifstream& deck1In, ifstream& deck2In, bool testing) {
    // players:
    // string p1name, p2name;
    // // cout << "Please enter player names: " << endl;
    // getline(cin, p1name); 
    // getline(cin, p2name); 

    p1.init(names[0], 1, deck1In, &ol, testing);
    p2.init(names[1], 2, deck2In, &ol, testing);

    activePlayer = &p1;
    nonactivePlayer = &p2;

    // testing:
    cout << "Player " << p1.getId() << ": " << p1.getName() << "\n" << endl;
    cout << "Player " << p2.getId() << ": " << p2.getName() << "\n" << endl;

    p1.TEST_printPlayerDeck();
    p2.TEST_printPlayerDeck();

    p1.TEST_printPlayerHand();
    p2.TEST_printPlayerHand();

}

bool find(vector<TriggeredAbility*> v, TriggeredAbility* target) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == target) return i;
    }
    return -1;
}

bool contains(vector<TriggeredAbility*> v, TriggeredAbility* target) {
    return (find(v, target) >= 0);
}

void GameMaster::attach(TriggeredAbility* o) {
    // bool isGameObserver = false;
    // if (o->getType() == TriggerType::StartTurn || o->getType() == TriggerType::EndTurn) isGameObserver = true;
    
    // if (isGameObserver && !contains(observers, o)) observers.emplace_back(o);
    // else if (!isGameObserver && !contains(observers, o)) observers.emplace_back(o);
    
    //if (!contains(observers, o)) observers.emplace_back(o);
    ol.observers.emplace_back(o);
}

void GameMaster::detach(TriggeredAbility* o) {
    for (auto it = ol.observers.begin(); it != ol.observers.end();) {
        if (*it == o) ol.observers.erase(it);
        else ++it;
    }
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
    try {
        if (activePlayer->getHandSize() < 5) activePlayer->drawCard();
    } catch (deck_empty e) {cout << e.what() << endl;}
    activePlayer->getBoard().restoreAction();
    activePlayer->getHand().restoreAction(); // can we combine these two
    
    // update activePlayer in observers
    ol.activePlayer = activePlayer;

    notifyStartTurnObservers();
}

// ends a turn, notifies corresponding observers
void GameMaster::endTurn() {
    ++turn;
    if (turn > numPlayers) {
        turn = 1;
    }
    this->notifyEndTurnObservers();
    swap(activePlayer, nonactivePlayer);
}

void GameMaster::attackMinion(int i, int j, MinionPtr* attacker, MinionPtr*victim) { // i is attacker, j is victim
    MinionPtr attackingMinion = activePlayer->getBoard().getCard(i);
    MinionPtr victimMinion = nonactivePlayer->getBoard().getCard(j);

    // check for enough action
    if (attackingMinion->getAction() == 0) throw not_enough_action{*activePlayer, attackingMinion}; 

    // minions attack each other
    attackingMinion->setAction(0);
    int attackValAttacker = attackingMinion->getAttack();
    int attackValVictim = victimMinion->getAttack();
    *attacker = activePlayer->getBoard().enchantMinion(i, "Modify Defense", -attackValVictim);
    *victim = nonactivePlayer->getBoard().enchantMinion(j, "Modify Defense", -attackValAttacker);

    // cout << "ap defense: " << activePlayer->getBoard().getCard(i)->getDefense() << endl;
    // cout << "nap defense: " << nonactivePlayer->getBoard().getCard(j)->getDefense() << endl;

    // update the original pointers to point at the top layer (after adding modify defense/attack enchantdecs)
    // *attacker = activePlayer->getBoard().getCard(i);
    // *victim = nonactivePlayer->getBoard().getCard(j);

    // cout << attacker->get() << endl;

    // // check if minions are dead 
    // if (activePlayer->getBoard().getCard(i)->isDead()) {
    //     // send to graveyard
    //     // activePlayer->getBoard().stripEnchants(i);
    //     activePlayer->getGrave().push(activePlayer->getBoard().getCard(i));
    //     activePlayer->getBoard().removeCard(i);
    // }
    // if (nonactivePlayer->getBoard().getCard(j)->isDead()) {
    //     nonactivePlayer->getGrave().push(nonactivePlayer->getBoard().getCard(j));
    //     nonactivePlayer->getBoard().removeCard(j);
    // }
    // cout << "in game master: " << activePlayer->getGrave().getTop().get() << endl;
    // cout << "in grave, defense: " << activePlayer->getGrave().getTop()->getDefense() << endl;
}


void GameMaster::attackPlayer(int i) {
    MinionPtr attackingMinion = activePlayer->getBoard().getCard(i);

    // check for enough action
    if (attackingMinion->getAction() == 0) throw not_enough_action{*activePlayer, attackingMinion}; 

    attackingMinion->setAction(0);
    int attackVal = attackingMinion->getAttack();
    nonactivePlayer->decreaseLife(attackVal);
}

void activateAbility();

void discard();

// play without target
void GameMaster::play(int i) {
    // try {
    TriggeredAbility* ta = activePlayer->play(i, *nonactivePlayer); // may throw exception
    if (ta) this->attach(ta);
        // if (ta) { 
        //     if (ta->getType() == TriggerType::StartTurn || ta->getType() == TriggerType::EndTurn) this->attach(ta);
        //     else activePlayer->getBoard().attach(ta);
        // } 
    // } catch (detach_game_observer& e) {
    //     play(i);
    // }

    activePlayer->getHand().removeCard(i);

    activePlayer->TEST_printPlayerBoard();

}

// play with target
void GameMaster::play(int i, int j, Player& targetPlayer) {
    TriggeredAbility* ta = activePlayer->play(i, j, targetPlayer); // may throw exception
    if (ta) this->attach(ta);
        
    activePlayer->getHand().removeCard(i);

    activePlayer->TEST_printPlayerBoard();
}

void GameMaster::useAbility(int i) {
    activePlayer->useAbility(i, *nonactivePlayer);

    activePlayer->TEST_printPlayerHand();
    activePlayer->TEST_printPlayerBoard();
}

void GameMaster::useAbility(int i, int j, Player& targetPlayer) {
    activePlayer->useAbility(i, j, targetPlayer);

    activePlayer->TEST_printPlayerHand();
    activePlayer->TEST_printPlayerBoard();
}


void GameMaster::notifyStartTurnObservers() {
    // for (auto o = observers.begin(); o != observers.end();) {
    //     try {
    //         if ((*o)->getType() == TriggerType::StartTurn) {
    //             (*o)->setTargetPlayer(activePlayer);
    //             (*o)->applyAbility();   
    //         }
    //         o++;
    //     } catch (not_enough_charge& e) {
    //         observers.erase(o);
    //     }
    // }

    auto o = ol.observers.begin();
    try {
        while (o != ol.observers.end()) {
            if ((*o)->getType() == TriggerType::StartTurn && (*o)->getOwner() == ol.activePlayer) { // TODO
                (*o)->setTargetPlayer(activePlayer);
                (*o)->applyAbility();   
            }
            ++o;
        }
        o = ol.observers.begin();
        while (o != ol.observers.end()) {
            if ((*o)->getType() == TriggerType::StartTurn && (*o)->getOwner() != ol.activePlayer) { // TODO
                (*o)->setTargetPlayer(activePlayer);
                (*o)->applyAbility();   
            }
            ++o;
        }
    } catch (not_enough_charge& e) {
        ol.observers.erase(o);
    }

}

void GameMaster::notifyEndTurnObservers() {
    // for (auto o = observers.begin(); o != observers.end();) {
    //     try {
    //         if ((*o)->getType() == TriggerType::EndTurn) {
    //             (*o)->setTargetPlayer(activePlayer);
    //             (*o)->applyAbility();   
    //         }
    //         o++;
    //     } catch (not_enough_charge& e) {
    //         observers.erase(o);
    //     }
    // }

    auto o = ol.observers.begin();
    try {
        while (o != ol.observers.end()) {
            if ((*o)->getType() == TriggerType::EndTurn && (*o)->getOwner() == ol.activePlayer) { // TODO
                (*o)->setTargetPlayer(activePlayer);
                (*o)->applyAbility();   
            }
            ++o;
        }
        o = ol.observers.begin();
        while (o != ol.observers.end()) {
            if ((*o)->getType() == TriggerType::EndTurn && (*o)->getOwner() != ol.activePlayer) { 
                (*o)->setTargetPlayer(activePlayer);
                (*o)->applyAbility();   
            }
            ++o;
        }
    } catch (not_enough_charge& e) {
        ol.observers.erase(o);
    }
}

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


