#include "graphicsdisplay.h"
#include "gamemaster.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(GameMaster *_gm) : gm{_gm} {
    w = new Xwindow();

    // draw sorcery board
    w->fillRectangle(53,27,644,632,1); // black frame
    w->fillRectangle(60,36,630,263,2); // red - player 1
    w->fillRectangle(60,387,630,263,4); // blue - player 2
    w->fillRectangle(60,303,630,80,0); // white, background behind sorcery
    displaySorceryBoard();
}
GraphicsDisplay::~GraphicsDisplay() {

}
void GraphicsDisplay::displayMsg(string msg) {

}

void GraphicsDisplay::displayCard(int x, int y, int colour) {
    w->fillRectangle(x, y, cardwidth, cardheight, 1); // for border
    w->fillRectangle(x+2, y+2, cardwidth-4, cardheight-4, colour); // actual 
}

void GraphicsDisplay::displayCard(int x, int y, int colour, Player* p) {
    displayCard(x, y, colour);
    if (p->getName() != "DEFAULT PLAYER") {
        cout << "p->getId: " << p->getId() << endl;
        w->drawString(playerpsn[p->getId()-1][0] + 43, playerpsn[p->getId()-1][1] + 42, p->getName());
        w->drawString(playerpsn[p->getId()-1][0] + 5, playerpsn[p->getId()-1][1] + 110, to_string(p->getLife()));
        w->drawString(playerpsn[p->getId()-1][0] + 107, playerpsn[p->getId()-1][1] + 110, to_string(p->getMagic()));
    }
    
}

void GraphicsDisplay::displaySorceryBoard(){
    // cout << "hi" << endl;
    for (int p = 0; p <= 1; ++p) { // looping through player 1 and 2
        cout << "p: " << p << endl;
        // board
        for (int i = 0; i < 5; ++i) {
            if (i < gm->getPlayer(p+1).getBoard().size()) {
                // print the actual minion, this is temporary
                displayCard(cardpsn[p][i][0], cardpsn[p][i][1], 3);
            } else {
                displayCard(cardpsn[p][i][0], cardpsn[p][i][1], 0);
            }
        }
        // ritual
        displayCard(ritualpsn[p][0], ritualpsn[p][1], 0);
        // graveyard
        displayCard(gravepsn[p][0], gravepsn[p][1], 0);
        // player
        displayCard(playerpsn[p][0], playerpsn[p][1], 0, &gm->getPlayer(p+1));
    }
}
void GraphicsDisplay::displayHand(int p) {

}
void GraphicsDisplay::displayMinion() {

}


