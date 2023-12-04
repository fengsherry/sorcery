// This is the public interface for a Player, representing one of two players of sorcery

#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
#include "boardelements.h"
#include "ritual.h"
#include "enchantment.h"
#include "enchantmentdec.h"
#include "enchantmentdecsconcrete.h"
using namespace std;

class Player {
    string name = "";
    int id = 0; // player 1 or 2
    int life = 20; // health points
    int magic = 3; // way to place cards on the board, etc
    Deck deck;
    Hand hand; // players start with 5 cards in their hand
    Board board;
    Graveyard grave;
    RitualPtr ritual; // set to nullptr if something breaks maybe
 
 public:
        Player(); // default ctor to be called when GameMaster is initialized
        // Player(string name, int id);
        ~Player();

        // void init(string name, int id);
        void init(string name, int id, ifstream& deckIn, vector<TriggeredAbility*>* boardObservers);

        string getName() const;
        int getId() const;
        int getLife() const;
        int getMagic() const;
        Hand& getHand();
        size_t getHandSize();
        Board& getBoard();
        bool onBoard(MinionPtr m);
        RitualPtr getRitual();
        Graveyard& getGrave();

        void setLife(int n);
        void setMagic(int n);
        void increaseMagic(int n);
        void increaseLife(int n);
        void decreaseLife(int n);
        CardPtr drawCard();
        
        void destroyRitual();

        // plays the ith card int he player's hand with no target (i.e. minions, rituals, spells)
        // throws exception if unsucessful 
        TriggeredAbility* play(int i, Player& nonActivePlayer); 
        void play(int i, int j, Player& p); 

        void useAbility(int i, Player& nonActivePlayer);
        void useAbility(int i, int j, Player &p);
        
        
        void TEST_printPlayerDeck();
        void TEST_printPlayerHand();
        void TEST_printPlayerBoard();
        void TEST_printPlayerRitual();
        void TEST_printPlayerGrave();
};

// class not_enough_action : public std::exception {
//     Player p;
//     public:
//         not_enough_action(Player& p) : p{p} {}
//         string what () {
//             return p.getName() + " has 0 action. Unable to attack.";
//         }
// };
// class not_enough_magic : public std::exception {
//     Player p;
//     public:
//         not_enough_magic(Player& p) : p{p} {}
//         string what () {
//             return p.getName() + " does not have enough magic. Play failed.";
//         }
// };
// class no_target_provided : public std::exception {
//     Card c;
//     public:
//         no_target_provided(Card& c) : c{c} {}
//         string what () {
//             return c.getName() + " cannot be played without a target. Play failed.";
//         }
// };
// class no_target_needed : public std::exception {
//     Card c;
//     public:
//         no_target_needed(Card& c) : c{c} {}
//         string what () {
//             return c.getName() + " cannot be played with a target. Play failed.";
//         }
// };
// class invalid_play : public std::exception {
//     string msg;
//     public:
//         invalid_play(string msg) : msg{msg} {}
//         string what () {
//             return msg;
//         }
// };


#endif
