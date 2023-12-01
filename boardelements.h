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
        void removeCard(int i);
        void enchantMinion(int i, string minionName, int modifyval = 0); // enchant ith Minion with specified enchantment name.
        void stripEnchants(int i, Player *p);
        void stripTopEnchant(int i); 
        void restoreAction(); // sets action of Minions to 1
        void destroyMinion(int i);
        int size();
        void TEST_printBoard();
};

// collection of dead Minions
class Graveyard {
    stack<Minion*> theGrave;

    public:
        Graveyard();
        ~Graveyard();
        bool isEmpty();
        Minion* getTop();
        void removeTop();
        void push(Minion* m);
        void TEST_printGrave();
};

#endif
