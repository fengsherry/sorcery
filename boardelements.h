// This is the public interface for Deck, Hand, Board, Graveyard, which are elements of the sorcery game board.

#ifndef __BOARDELEMENTS_H__
#define __BOARDELEMENTS_H__
#include <stack>
#include <string>
#include <vector>
#include "card.h"
#include "minion.h"
#include "defaultminion.h"
using namespace std;

// collection of cards from which players draw cards into their Hand
class Deck {
    vector<Card*> theDeck;
    //vector<string*> theDeck;

 public:
    Deck();
    ~Deck();

    void init(ifstream& file);
    void shuffle();
    Card* drawCard();

    void TEST_printDeck();
};

// cards a player is holding, but has not placed
class Hand {
    vector<Card*> theHand;

    public:
        void init(Deck& deck);
        Card* getCard(int i);

        void TEST_printHand();
};

// Minions the player has played, not yet dead
class Board {
    vector<Minion*> theBoard;

    public:
        Minion* getMinion(int i);
        void addCard(Minion *m);

};

// collection of dead Minions
class Graveyard {
    stack<Minion*> theGrave;
};

#endif
