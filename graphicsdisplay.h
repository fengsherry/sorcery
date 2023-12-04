#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <vector>
#include "sorcerydisplay.h"
#include "window.h"
#include "player.h"
#include "sorceryutil.h"
using namespace std;

class GameMaster;

class GraphicsDisplay : public SorceryDisplay {
    private:
        GameMaster *gm;
        Xwindow* w;

        /* Useful Dimensions: */

        int cardwidth = 160; 
        int cardheight = 123;

        int hand_cardwidth = 160;
        int hand_cardheight = 90;

        vector<vector<vector<int>>> cardpsn =
        {
        {{65,171}, {65+(165*1),171}, {65+(165*2),171}, {65+(165*3),171}, {65+(165*4),171}}, // player 1's board
        {{65,392}, {65+(165*1),392}, {65+(165*2),392}, {65+(165*3),392}, {65+(165*4),392}} // player 2's board
        };
        vector<vector<int>> ritualpsn = {{65,43}, {65,521}};
        vector<vector<int>> playerpsn = {{65+(165*2),43}, {65+(165*2),521}};
        vector<vector<int>> gravepsn = {{65+(165*4),43}, {65+(165*4),521}};
        vector<vector<int>> handpsn = {{1009,162}, {1009,162+98*1}, {1009,162+98*2}, {1009,162+98*3}, {1009,162+98*4}};
        // vector<vector<int>> minionpsn = 
        // {
        //     {}, {},
        // }

        /* Helpers: */ 
        void displayCardBlank(int x, int y, int width, int height); // blank card 
        void displayCardBase(int x, int y, int width, int height, CardPtr c);
        void wrapString(int x, int y, size_t chars, string s); // c is space allowance for chars
        void wrapString(int x, int y, size_t chars, vector<string> msg);

        // player
        void displayCard(int x, int y, int width, int height, Player* p); // player information

        // minion
        void displayCard(int x, int y, int width, int height, MinionPtr m); // minion information, the board
        void displayCardMinionBase(int x, int width, int height, int y, MinionPtr m);

        // ritual
        void displayCard(int x, int y, int width, int height, RitualPtr r);

        // graveyard
        void displayCard(int x, int y, int width, int height, Graveyard& g);

        // enchantment
        void displayCard(int x, int y, int width, int height, EnchantmentPtr e);

        // spell
        void displayCard(int x, int y, int width, int height, SpellPtr s);


    public:
        GraphicsDisplay(GameMaster *_gm);
        ~GraphicsDisplay();
        // void displayMsg(string msg, int p = 0);
        void displayMsg(vector<string> msg, int p = 0) override;
        void displaySorceryBoard() override;
        void displayHand(int p) override;
        void displayMinion(const MinionPtr m) override;

        // friend ostream &operator<<(ostream &out, const card_template_t &t);

};

#endif
