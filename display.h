#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <string>
#include "minion.h"
using namespace std;

class Display {
    public:
        virtual ~Display() = default;
        //virtual void notify(Hand &hand) = 0;

        // virtual SubscriptionType subType() = 0;
        
        virtual void displayMsg(string msg) = 0;
        virtual void displaySorceryBoard() = 0;
        virtual void displayHand(int p) = 0;
        virtual void displayMinion(const MinionPtr m) = 0;
};


#endif
