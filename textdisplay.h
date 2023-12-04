#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "sorcerydisplay.h"
#include <vector>
using namespace std;

class GameMaster;

class TextDisplay : public SorceryDisplay {
 private:
   //  std::vector<std::vector<char>> theBoard;
   //  std::vector<std::vector<char>> theHand;
   GameMaster *gm;
   void printPlayerBoardRow(int p);

 public:
    TextDisplay(GameMaster *_gm);
    ~TextDisplay();
    void displayMsg(string msg, int p = 0) override;
    void displaySorceryBoard() override;
    void displayHand(int p) override;
    void displayMinion(const MinionPtr m) override;

    // friend ostream &operator<<(ostream &out, const card_template_t &t);

};

#endif
