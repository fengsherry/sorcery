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

  int cardwidth = 200; 
  int cardheight = 123;

  vector<vector<vector<int>>> cardpsn =
  {
  {{65,171}, {65+(205*1),171}, {65+(205*2),171}, {65+(205*3),171}, {65+(205*4),171}}, // player 1's board
  {{65,392}, {65+(205*1),392}, {65+(205*2),392}, {65+(205*3),392}, {65+(205*4),392}} // player 2's board
  };

  vector<vector<int>> ritualpsn = {{65,43}, {65,521}};
  vector<vector<int>> playerpsn = {{65+(205*2),43}, {65+(205*2),521}};
  vector<vector<int>> gravepsn = {{65+(205*4),43}, {65+(205*4),521}};

  // helpers
  void displayCardBlank(int x, int y); // blank card 
  void displayCardBase(int x, int y, CardPtr c);
  void displayDesc(int x, int y, size_t chars, CardPtr c); // c is space allowance for chars

  // player
  void displayCard(int x, int y, Player* p); // player information

  // minion
  void displayCard(int x, int y, MinionPtr m); // minion information, the board
  void displayCardMinionBase(int x, int y, MinionPtr m);

  // ritual
  void displayCard(int x, int y, RitualPtr r);

  // graveyard
  void displayCard(int x, int y, Graveyard* g);


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
