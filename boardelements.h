// This is the public interface for Deck, Hand, Board, Graveyard, which are elements of the sorcery game board.

#ifndef __BOARDELEMENTS_H__
#define __BOARDELEMENTS_H__
#include <stack>
#include <string>
#include <vector>
#include "card.h"
#include "minion.h"
#include "defaultminion.h"
#include "spell.h"
#include "triggeredability.h"
#include "enchantment.h"
#include "enchantmentdec.h"
#include "enchantmentdecsconcrete.h"
using namespace std;

// collection of cards from which players draw cards into their Hand
class Deck {
    vector<Card*> theDeck;
    //vector<string*> theDeck;

 public:
    Deck();
    ~Deck();

    void init(ifstream& file, Player* p);
    void shuffle();
    Card* drawCard();
    size_t getSize();

    void TEST_printDeck();
};

// cards a player is holding, but has not placed
class Hand {
    vector<Card*> theHand;

    public:
        void init(Deck& deck);
        void addCard(Card* c);
        Card* getCard(int i) const;
        size_t getSize();
        void TEST_printHand();
        void restoreAction(); // sets action of Minions to 1
        void removeCard(int i);
};

// Minions the player has played, not yet dead
class Board {
    vector<Minion*> theBoard;

    public:
        Minion* getCard(int i) const;
        void addCard(Minion *m);
        void enchantMinion(int i, string minionName); // enchant ith Minion with specified enchantment name.
        void restoreAction(); // sets action of Minions to 1
        void TEST_printBoard();
};

// collection of dead Minions
class Graveyard {
    stack<Minion*> theGrave;
};

#endif
