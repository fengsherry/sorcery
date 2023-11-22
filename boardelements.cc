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
        string* card = new string(cardName);
        theDeck.emplace_back(card);
    }
}

void Deck::TEMP_printDeck() {
    cout << "printing deck"<< endl;
    for (auto s : theDeck) { cout << *s << endl; }
}

Card *Hand::getCard(int i) {
    return theHand[i];
}

Minion *Board::getMinion(int i) {
    return theBoard[i];
}

void Board::addCard(Minion *m) {
    theBoard.emplace_back(m);
}