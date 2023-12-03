#include "graphicsdisplay.h"
#include "gamemaster.h"
#include <sstream>

using namespace std;

GraphicsDisplay::GraphicsDisplay(GameMaster *_gm) : gm{_gm} {
    w = new Xwindow();

    // draw sorcery board
    w->fillRectangle(53,27,1045,632,1); // black frame
    w->fillRectangle(60,36,1031,263,2); // red - player 1
    w->fillRectangle(60,387,1031,263,4); // blue - player 2
    w->fillRectangle(60,303,1031,80,0); // white, background behind sorcery
    displaySorceryBoard();
}
GraphicsDisplay::~GraphicsDisplay() {

}
void GraphicsDisplay::displayMsg(string msg) {

}

void GraphicsDisplay::displayCardBlank(int x, int y) {
    w->fillRectangle(x, y, cardwidth, cardheight, 1); // for border
    w->fillRectangle(x+2, y+2, cardwidth-4, cardheight-4, 0); // actual 
}

// player
void GraphicsDisplay::displayCard(int x, int y, Player* p) {
    displayCardBlank(x, y);
    if (p->getName() != "DEFAULT PLAYER") {
        // cout << "p->getId: " << p->getId() << endl;
        w->drawString(playerpsn[p->getId()-1][0] + 75, playerpsn[p->getId()-1][1] + 42, p->getName());
        w->drawString(playerpsn[p->getId()-1][0] + 8, playerpsn[p->getId()-1][1] + 110, to_string(p->getLife()));
        w->drawString(playerpsn[p->getId()-1][0] + 185, playerpsn[p->getId()-1][1] + 110, to_string(p->getMagic()));
    } 
}

void GraphicsDisplay::displayCardBase(int x, int y, CardPtr c) {
    w->fillRectangle(x, y+20, 200, 2, 1); // first seperator
    w->fillRectangle(x, y+40, 200, 2, 1); // second seperator

    string name;
    if (MinionPtr m = dynamic_pointer_cast<Minion>(c)) name = m->getDefaultMinionName();
    else name = c->getName();
    w->drawString(x+8, y+15, name);
    w->drawString(x+185, y+15, to_string(c->getCost()));

    w->drawString(x+120, y+35, cardTypeToString(c->getType()));
}

// minion base
void GraphicsDisplay::displayCardMinionBase(int x, int y, MinionPtr m) {
    // w->fillRectangle(x, y+20, 200, 2, 1); // first seperator
    // w->fillRectangle(x, y+40, 200, 2, 1); // second seperator
    // w->drawString(x+8, y+15, m->getName());
    // w->drawString(x+185, y+15, to_string(m->getCost()));

    // w->drawString(x+120, y+35, cardTypeToString(m->getType()));

    displayCardBase(x, y, m);

    w->drawString(x+8, y+113, to_string(m->getAttack())); // attack 
    w->drawString(x+185,y+113, to_string(m->getDefense())); // defense
}

// minion ability description
void GraphicsDisplay::displayDesc(int x, int y, size_t chars, CardPtr c) {
    
    istringstream iss;
    if (MinionPtr m = dynamic_pointer_cast<Minion>(c)) iss.str(m->getDefaultMinionDesc());
    else iss.str(c->getDesc());
    cout << iss.str() << endl;
    
    string word;
    int line = 0;
    ostringstream oss;
    while (iss >> word) {
        // go to a new line
        if ((oss.str() + word).length() >= chars) {
            cout << "oss.str(): " << oss.str() << endl;
            w->drawString(x, y + line*12, oss.str());
            ++line;
            oss.str("");
            oss << word << " "; 
        }
        // stay on this line
        else {
            cout << "else" << endl;
            oss << word << " ";
        }
    }
    w->drawString(x, y + line*12, oss.str());
}

// minion
void GraphicsDisplay::displayCard(int x, int y, MinionPtr m) {
    displayCardBlank(x, y); 
    displayCardMinionBase(x, y, m); 

    // if activated ability: cost, then left align
    if (holds_alternative<ActivatedAbility*>(m->getAbility())) {
        // cout << "hi" << endl;
        ActivatedAbility* aa = get<ActivatedAbility*>(m->getAbility());
        w->drawString(x+8,y+55,to_string(aa->getActivationCost()));
        // w->drawString(x+31, y+55, m->getDesc());
        displayDesc(x+31, y+55, 25, m);
    }
    
    else displayDesc(x+8, y+55, 30, m);

}

// ritual
void GraphicsDisplay::displayCard(int x, int y, RitualPtr r) {
    displayCardBlank(x, y);
    displayCardBase(x, y, r);

    w->drawString(x+8,y+55,to_string(r->getCost())); // cost
    w->drawString(x+185,y+113, to_string(r->getCharge())); // charge
    displayDesc(x, y, 30, r);
}

// graveyard
void GraphicsDisplay::displayCard(int x, int y, Graveyard* g) {
    if (g->isEmpty()) displayCardBlank(x, y);
    else displayCard(x, y, g->getTop());
}

void GraphicsDisplay::displaySorceryBoard(){
    // cout << "hi" << endl;
    for (int p = 0; p <= 1; ++p) { // looping through player 1 and 2
        // cout << "p: " << p << endl;
        // board
        for (int i = 0; i < 5; ++i) {
            if (i < gm->getPlayer(p+1).getBoard().size()) {
                // print the actual minion, this is temporary
                displayCard(cardpsn[p][i][0], cardpsn[p][i][1], gm->getPlayer(p+1).getBoard().getCard(i));
            } else {
                displayCardBlank(cardpsn[p][i][0], cardpsn[p][i][1]);
            }
        }
        // ritual
        displayCardBlank(ritualpsn[p][0], ritualpsn[p][1]);
        // graveyard
        displayCardBlank(gravepsn[p][0], gravepsn[p][1]);
        // player
        displayCard(playerpsn[p][0], playerpsn[p][1], &gm->getPlayer(p+1));
    }
}
void GraphicsDisplay::displayHand(int p) {

}
void GraphicsDisplay::displayMinion() {

}


