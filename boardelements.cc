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
        // an if else to make the different cards?

        Card* card = new DefaultMinion(cardName, 1, 1, 1);
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

Card *Hand::getCard(int i) {
    return theHand[i];
}

void Hand::TEST_printHand() {
    for (int i = 0; i < 5; ++i) {
        cout << "Hand (" << i << "): " << *theHand[i] << endl;
    }
}

/* BOARD */
Minion *Board::getMinion(int i) {
    return theBoard[i];
}

void Board::addCard(Minion *m) {
    theBoard.emplace_back(m);
}