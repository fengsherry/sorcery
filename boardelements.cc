#include <iostream>
#include <fstream>
#include "boardelements.h"
using namespace std;

Deck::Deck() {

}

Deck::~Deck() {}

void Deck::init(ifstream& file) {
    string cardName;
    while (getline(file, cardName)) {
        // an function to make the different cards?

        // this is just making a basic 1/1 minion 
        Card* card = new DefaultMinion(cardName, 1, 1);
        theDeck.emplace_back(card);
    }
}

void Deck::TEST_printDeck() {
    for (auto s : theDeck) { cout << *s << endl; }
}

Card* Deck::drawCard() {
    Card* card = theDeck.back();
    theDeck.pop_back();
    return card;
}


/* HAND */
void Hand::init(Deck& deck) {
    for (int i = 0; i < 5; ++i) {
        theHand.emplace_back(deck.drawCard());
    }
}

Card* Hand::getCard(int i) const {
    return theHand[i];
}

void Hand::TEST_printHand() {
    for (size_t i = 0; i < theHand.size(); ++i) {
        cout << "Hand (" << (i+1) << "): " << *theHand[i] << endl;
    }
}

void Hand::restoreAction() {
    for (auto card : theHand) {
        // type check for Minions
        Minion* minionCard = dynamic_cast<Minion*>(card);
        minionCard->setAction(1);
    }
}

void Hand::removeCard(int i) {
    theHand.erase(theHand.begin() + i);
}

/* BOARD */
Minion* Board::getCard(int i) const {
    return theBoard[i];
}

void Board::addCard(Minion *m) {
    theBoard.emplace_back(m);
}

void Board::restoreAction() {
    for (auto minion : theBoard) {
        minion->setAction(1);
    }
}

void Board::TEST_printBoard() {
    for (size_t i = 0; i < theBoard.size(); ++i) {
        cout << "Board (" << (i+1) << "): " << *theBoard[i] << endl;
    }
}