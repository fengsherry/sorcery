// This is the public interface for Deck, Hand, Board, Graveyard, which are elements of the sorcery game board.

#ifndef __BOARDELEMENTS_H__
#define __BOARDELEMENTS_H__
#include <stack>
#include <string>
#include <vector>
#include <variant>
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
    vector<CardPtr> theDeck;
    //vector<string*> theDeck;

 public:
    Deck();
    ~Deck();

    void init(ifstream& file, Player* p);
    void shuffle();
    CardPtr drawCard();
    size_t getSize();

    void TEST_printDeck();
};

// cards a player is holding, but has not placed
class Hand {
    vector<CardPtr> theHand;

    public:
        void init(Deck& deck);
        void addCard(CardPtr c);
        CardPtr getCard(int i) const;
        size_t getSize(); // fix maybe later

        void TEST_printHand();
        void restoreAction(); // sets action of Minions to 1
        void removeCard(int i);
};

// Minions the player has played, not yet dead
class Board {
    vector<MinionPtr> theBoard;
    vector<TriggeredAbility*>* boardObservers; // reference to the boardObservers vector in gamemaster

    public:
        MinionPtr getCard(int i) const;
        void init(vector<TriggeredAbility*>* bo);
        void addCard(MinionPtr m);
        void removeCard(int i);
        void enchantMinion(int i, string minionName, int modifyval = 0); // enchant ith Minion with specified enchantment name.
        void stripEnchants(int i);
        void stripTopEnchant(int i); 
        void restoreAction(); // sets action of Minions to 1
        void destroyMinion(int i);
        int size();
        int getBoardSize();
        int find(MinionPtr m); // returns index of m in theBoard, -1 if not found
        bool contains(MinionPtr m);
        void TEST_printBoard();
    

        // observer pattern methods
        void attach(TriggeredAbility* o);
        void detach(TriggeredAbility* o);
        void notifyMinionEnterObservers(MinionPtr targetMinion);
        void notifyMinionLeaveObservers(MinionPtr targetMinion);
        

};

// collection of dead Minions
class Graveyard {
    stack<MinionPtr> theGrave;

    public:
        Graveyard();
        ~Graveyard();
        bool isEmpty();
        MinionPtr getTop();
        void removeTop();
        void push(MinionPtr m);
        void TEST_printGrave();

 public:
    stack<MinionPtr>& getGrave();

};

#endif
