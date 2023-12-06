#ifndef __SORCERYDISPLAY_H__
#define __SORCERYDISPLAY_H__

#include <string>
#include <vector>
#include "minion.h"
using namespace std;

class SorceryDisplay {
    public:
        // SorceryDisplay();
        virtual ~SorceryDisplay() = default;
        //virtual void notify(Hand &hand) = 0;

        // virtual SubscriptionType subType() = 0;
        
        virtual void displayMsg(vector<string> msg, int p = 0) = 0;
        // virtual void displayMsg(string msg, int p = 0) = 0;
        virtual void displaySorceryBoard(int p) = 0;
        virtual void displayHand(int p) = 0;
        virtual void displayMinion(const MinionPtr m) = 0;
        void displayErrMsg(string msg, int p = 0);
};


#endif
