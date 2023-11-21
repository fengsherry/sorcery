// This is the public interface for Deck, Hand, Board, Graveyard, which are elements of the sorcery game board.

#ifndef __BOARDELEMENTS_H__
#define __BOARDELEMENTS_H__
#include <stack>
#include "card.h"
#include "minion.h"
using namespace std;

// collection of cards from which players draw cards into their Hand
class Deck {
    // vector<Card*> theDeck;
    vector<string*> theDeck;

 public:
    void shuffle();
    Card* drawCard();
};
// cards a player is holding, but has not placed
class Hand {
    vector<Card*> theHand;
};

// Minions the player has played, not yet dead
class Board {
    vector<Minion*> theBoard;
};

// collection of dead Minions
class Graveyard {
    stack<Minion*> theGrave;
};

#endif
