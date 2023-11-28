#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "display.h"
#include <vector>
using namespace std;

class GameMaster;

class TextDisplay : public Display {
 private:
    std::vector<std::vector<char>> theBoard;
    std::vector<std::vector<char>> theHand;

 public:
    TextDisplay();
    ~TextDisplay();
    void notify(GameMaster &gm) override;
    void displayMsg(string msg) override;
    void displaySorceryBoard() override;
    void displayHand() override;
    void displayMinion() override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
