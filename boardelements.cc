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

void Deck::TEST_printDeck() {
    for (auto s : theDeck) { cout << *s << endl; }
}

