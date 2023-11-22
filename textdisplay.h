#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "display.h"

class TextDisplay : public Display {
    public:
        TextDisplay();
        ~TextDisplay();
        void displayMsg(string msg) override;
        void displaySorceryBoard() override;
        void displayHand() override;
        void displayMinion() override;
};


#endif
