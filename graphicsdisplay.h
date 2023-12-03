#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "sorcerydisplay.h"
#include "window.h"
#include <vector>
using namespace std;

class GameMaster;

class GraphicsDisplay : public SorceryDisplay {
 private:
   GameMaster *gm;
   Xwindow* w;

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
