#ifndef __DECK_H__
#define __DECK_H__
#include <string>
#include <vector>
#include "card.h"
using namespace std;

class Deck {
    // vector<Card*> theDeck;
    vector<string*> theDeck;

 public:
    void shuffle();
    Card* drawCard();
};

#endif