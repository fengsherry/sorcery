#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "sorcerydisplay.h"
#include "window.h"
#include "player.h"
#include <vector>
using namespace std;

class GameMaster;

class GraphicsDisplay : public SorceryDisplay {
 private:
   GameMaster *gm;
   Xwindow* w;

   vector<vector<vector<int>>> cardpsn =
   {
    {{65,171}, {190,171}, {315,171}, {440,171}, {565,171}}, // player 1's board
    {{65,392}, {190,392}, {315,392}, {440,392}, {565,392}} // player 2's board
   };

   vector<vector<int>> ritualpsn = {{65,43}, {65,521}};
   vector<vector<int>> playerpsn = {{315,43}, {315,521}};
   vector<vector<int>> gravepsn = {{565,43}, {565,521}};

   int cardwidth = 120; 
   int cardheight = 123;

    void displayCard(int x, int y, int colour);

    void displayCard(int x, int y, int colour, Player* p);

 public:
    GraphicsDisplay(GameMaster *_gm);
    ~GraphicsDisplay();
    void displayMsg(string msg) override;
    void displaySorceryBoard() override;
    void displayHand(int p) override;
    void displayMinion() override;

    // friend ostream &operator<<(ostream &out, const card_template_t &t);

};

#endif
