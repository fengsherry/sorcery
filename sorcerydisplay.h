#ifndef __SORCERYDISPLAY_H__
#define __SORCERYDISPLAY_H__

#include <string>
using namespace std;

class SorceryDisplay {
    public:
        // SorceryDisplay();
        virtual ~SorceryDisplay() = default;
        //virtual void notify(Hand &hand) = 0;

        // virtual SubscriptionType subType() = 0;
        
        virtual void displayMsg(string msg) = 0;
        virtual void displaySorceryBoard() = 0;
        virtual void displayHand(int p) = 0;
        virtual void displayMinion() = 0;
};


#endif
