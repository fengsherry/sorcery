#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <string>
using namespace std;

class Display {
    public:
        virtual ~Display() = default;
        virtual void displayMsg(string msg) = 0;
        virtual void displaySorceryBoard() = 0;
        virtual void displayHand() = 0;
        virtual void displayMinion() = 0;
};


#endif
