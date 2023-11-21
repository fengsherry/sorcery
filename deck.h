#ifndef __DECK_H__
#define __DECK_H__
#include <string>
#include <vector>
#include "card.h"
using namespace std;

class Deck {
    vector<Card*> theDeck;

 public:
    Card* drawCard();
};

#endif