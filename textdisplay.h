#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "display.h"
#include <vector>
using namespace std;

class GameMaster;

class TextDisplay : public Display {
 private:
   //  std::vector<std::vector<char>> theBoard;
   //  std::vector<std::vector<char>> theHand;
   GameMaster *gm;

 public:
    TextDisplay(GameMaster *_gm);
    ~TextDisplay();
    void displayMsg(string msg) override;
    void displaySorceryBoard() override;
    void displayHand(int p) override;
    void displayMinion() override;
};

#endif
