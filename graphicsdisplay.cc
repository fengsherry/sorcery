#include "graphicsdisplay.h"
#include "gamemaster.h"
#include <sstream>

using namespace std;

GraphicsDisplay::GraphicsDisplay(GameMaster *_gm) : gm{_gm} {
    w = new Xwindow();

    // draw sorcery board
    w->fillRectangle(53,27,848,632,1); // black frame

    w->fillRectangle(60,36,832,263,2); // red - player 1
    w->fillRectangle(60,387,832,263,4); // blue - player 2
    w->fillRectangle(60,303,832,80,0); // white, background behind sorcery
    w->drawString(400, 350, "S  O   R   C   E   R   Y");

    w->fillRectangle(913, 27, 351, 632, 1);
    w->fillRectangle(913+2, 27+2, 351-4, 632-4, 0);
    displaySorceryBoard();
}
GraphicsDisplay::~GraphicsDisplay() {

}
void GraphicsDisplay::displayMsg(vector<string> msg, int p) {
    int colour; // background colour matches active player's id
    if (p == 1) colour = 2;  else if (p == 2) colour = 4; else colour = 1;
    
    w->fillRectangle(913+2, 27+2, 351-4, 128-4, colour);
    w->fillRectangle(913+2+10, 27+2+10, 351-4-20, 128-4-20, 0);
    wrapString(932, 62, 50, msg);
}

void GraphicsDisplay::displayCardBlank(int x, int y, int width, int height) {
    w->fillRectangle(x, y, width, height, 1); // for border
    w->fillRectangle(x+2, y+2, width-4, height-4, 0); // actual 
}

// player
void GraphicsDisplay::displayCard(int x, int y,  int width, int height, Player* p) {
    displayCardBlank(x, y, width, height);
    if (p->getName() != "") {
        // cout << "p->getId: " << p->getId() << endl;
        w->drawString(playerpsn[p->getId()-1][0] + 75, playerpsn[p->getId()-1][1] + 42, p->getName());
        w->drawString(playerpsn[p->getId()-1][0] + 8, playerpsn[p->getId()-1][1] + 110, to_string(p->getLife()));
        w->drawString(playerpsn[p->getId()-1][0] + 143, playerpsn[p->getId()-1][1] + 110, to_string(p->getMagic()));
    } 
}

void GraphicsDisplay::displayCardBase(int x, int y, int width, int height, CardPtr c) {
    w->fillRectangle(x, y+20, width, 2, 1); // first seperator
    w->fillRectangle(x, y+40, width, 2, 1); // second seperator

    string name;
    if (MinionPtr m = dynamic_pointer_cast<Minion>(c)) name = m->getDefaultMinionName();
    else name = c->getName();

    w->drawString(x+8, y+15, name); // name
    w->drawString(x+143, y+15, to_string(c->getCost())); // cost
    w->drawString(x+80, y+35, cardTypeToString(c->getType())); // type
}

// minion base
void GraphicsDisplay::displayCardMinionBase(int x, int y, int width, int height, MinionPtr m) {
    // w->fillRectangle(x, y+20, 200, 2, 1); // first seperator
    // w->fillRectangle(x, y+40, 200, 2, 1); // second seperator
    // w->drawString(x+8, y+15, m->getName());
    // w->drawString(x+185, y+15, to_string(m->getCost()));

    // w->drawString(x+120, y+35, cardTypeToString(m->getType()));

    displayCardBase(x, y, width, height, m);

    w->drawString(x+8, y+(height-10), to_string(m->getAttack())); // attack 
    w->drawString(x+143,y+(height-10), to_string(m->getDefense())); // defense
}

// wrapper function
void GraphicsDisplay::wrapString(int x, int y, size_t chars, string s) {
    wrapString(x, y, chars, vector<string>{s});
}

// minion ability description
void GraphicsDisplay::wrapString(int x, int y, size_t chars, vector<string> msg) {
    // istringstream iss(s);
    // istringstream iss;
    // if (MinionPtr m = dynamic_pointer_cast<Minion>(c)) iss.str(m->getDefaultMinionDesc());
    // else iss.str(c->getDesc());
    // cout << iss.str() << endl;
    
    string word;
    int line = 0;
    
    for (string s : msg) {
        // cout << "hi"  << s << endl;
        istringstream iss(s);
        ostringstream oss;
        while (iss >> word) {
            // go to a new line
            if ((oss.str() + word).length() >= chars) {
                // cout << "oss.str(): " << oss.str() << endl;
                w->drawString(x, y + line*12, oss.str());
                ++line;
                oss.str("");
                oss << word << " "; 
            }
            // stay on this line
            else {
                // cout << "else" << endl;
                oss << word << " ";
            }
        }
        w->drawString(x, y + line*12, oss.str());
        ++line;
    }
    
}

// minion
void GraphicsDisplay::displayCard(int x, int y, int width, int height, MinionPtr m) {
    displayCardBlank(x, y, width, height); 
    displayCardMinionBase(x, y, width, height, m); 

    // if activated ability: cost, then left align
    if (holds_alternative<ActivatedAbility*>(m->getAbility())) {
        // cout << "hi" << endl;
        ActivatedAbility* aa = get<ActivatedAbility*>(m->getAbility());
        w->drawString(x+8,y+55,to_string(aa->getActivationCost()));
        wrapString(x+31, y+55, 17, m->getDefaultMinionDesc());
    }
    
    else wrapString(x+8, y+55, 22, m->getDefaultMinionDesc());

}

void GraphicsDisplay::displayCard(int x, int y, int width, int height, EnchantmentDecPtr e) {
    // cout << e->getName() << endl;
    switch (e->getCardName()) {
        case(CardName::GiantStrength):
            // cout << "giant strength" << endl;
            displayCard(x, y, hand_cardwidth, hand_cardheight, make_shared<Enchantment>(e->getCardName(), e->getCost(), e->getDesc(), "+2", "+2"));
            break;
        case(CardName::Enrage):
            // cout << "enrage" << endl;
            displayCard(x, y, hand_cardwidth, hand_cardheight, make_shared<Enchantment>(e->getCardName(), e->getCost(), e->getDesc(), "*2", "*2"));
            break;
        case(CardName::Haste):
            displayCard(x, y, hand_cardwidth, hand_cardheight, make_shared<Enchantment>(e->getCardName(), e->getCost(), e->getDesc()));
            break;
        case(CardName::MagicFatigue):
            displayCard(x, y, hand_cardwidth, hand_cardheight, make_shared<Enchantment>(e->getCardName(), e->getCost(), e->getDesc()));
            break;
        case(CardName::Silence):
            displayCard(x, y, hand_cardwidth, hand_cardheight, make_shared<Enchantment>(e->getCardName(), e->getCost(), e->getDesc()));
            break;
    }
}

// ritual
void GraphicsDisplay::displayCard(int x, int y, int width, int height, RitualPtr r) {
    // displayCardBlank(x, y, width, height);
    if (!r) return;
    displayCardBase(x, y, width, height, r);

    w->drawString(x+8,y+55,to_string(r->getCost())); // cost
    w->drawString(x+143,y+(height-10), to_string(r->getCharge())); // charge
    wrapString(x+31, y+55, 22, r->getDesc());
}

// graveyard
void GraphicsDisplay::displayCard(int x, int y, int width, int height, Graveyard& g) {
    if (g.isEmpty()) displayCardBlank(x, y, width, height);
    else displayCard(x, y, width, height, g.getTop());
}

// enchantment
void GraphicsDisplay::displayCard(int x, int y, int width, int height, EnchantmentPtr e) {
    string attack = "";
    string defense = "";
    if (e->getCardName() == CardName::GiantStrength) {attack = "+2"; defense = "+2";}
    else if (e->getCardName() == CardName::Enrage) {attack = "*2"; defense = "*2";}

    cout << "hi2" << endl;
    cout << "x: " << x << " y: " << y << endl;
    displayCardBlank(x, y, width, height);
    displayCardBase(x, y, width, height, e);
    w->drawString(x+8, y+85, attack); // attack modifer 
    w->drawString(x+143,y+85, defense); // defense modifier
    wrapString(x+8, y+55, 17, e->getDesc());
}

// spell
void GraphicsDisplay::displayCard(int x, int y, int width, int height, SpellPtr s) {
    displayCardBlank(x, y, width, height);
    displayCardBase(x, y, width, height, s); // name, type, cost
    wrapString(x+8, y+55, 17, s->getDesc());
}

void GraphicsDisplay::displaySorceryBoard(){
    // cout << "hi" << endl;
    for (int p = 0; p <= 1; ++p) { // looping through player 1 and 2
        // cout << "p: " << p << endl;
        // board
        for (int i = 0; i < 5; ++i) {
            if (i < gm->getPlayer(p+1).getBoard().size()) { 
                // print the actual minion
                displayCard(cardpsn[p][i][0], cardpsn[p][i][1], cardwidth, cardheight, gm->getPlayer(p+1).getBoard().getCard(i));
            } else { 
                // print a blank card
                displayCardBlank(cardpsn[p][i][0], cardpsn[p][i][1], cardwidth, cardheight);
            }
        }
        // ritual
        if (gm->getPlayer(p+1).getRitual()) displayCard(ritualpsn[p][0], ritualpsn[p][1], cardwidth, cardheight, gm->getPlayer(p+1).getRitual());
        else displayCardBlank(ritualpsn[p][0], ritualpsn[p][1], cardwidth, cardheight);
        
        // graveyard
        displayCard(gravepsn[p][0], gravepsn[p][1], cardwidth, cardheight, gm->getPlayer(p+1).getGrave());
        // player
        displayCard(playerpsn[p][0], playerpsn[p][1], cardwidth, cardheight, &gm->getPlayer(p+1));
    }
}

void GraphicsDisplay::displayHand(int p) {
    w->fillRectangle(913+2,155, 351-4, 504-2, 0);

    for (size_t i = 0; i < 5; ++i) {
        w->drawString(handpsn[i][0] - 20, handpsn[i][1] + hand_cardheight/2, to_string(i+1) + ": ");
        int x = handpsn[i][0]; int y = handpsn[i][1];

        if (i < gm->getPlayer(p).getHand().getSize()) {
            // print an actual card
            CardPtr c = gm->getPlayer(p).getHand().getCard(i); 

            if (EnchantmentPtr eptr = dynamic_pointer_cast<Enchantment>(c)) {
                displayCard(x, y, hand_cardwidth, hand_cardheight, eptr);
            } else if (SpellPtr sptr = dynamic_pointer_cast<Spell>(c)) {
                displayCard(x, y, hand_cardwidth, hand_cardheight, sptr);
            } else if (MinionPtr mptr = dynamic_pointer_cast<Minion>(c)) {
                displayCard(x, y, hand_cardwidth, hand_cardheight, mptr);
            } else if (RitualPtr rptr = dynamic_pointer_cast<Ritual>(c)) {
                displayCard(x, y, hand_cardwidth, hand_cardheight, rptr);
            }
            else displayCardBlank(x, y, hand_cardwidth, hand_cardheight);
        } else {
            // print a blank card
            displayCardBlank(x, y, hand_cardwidth, hand_cardheight);
        }
    }
}

void GraphicsDisplay::displayMinion(const MinionPtr m) {
    w->fillRectangle(913+2,155, 351-4, 504-2, 0);
    MinionPtr curr = m;
    if (DefaultMinionPtr dmptr = dynamic_pointer_cast<DefaultMinion>(curr)) {
        displayCard(minionpsn[0][0], minionpsn[0][1], hand_cardwidth, hand_cardheight, curr);
    } else {
        // EnchantmentDecPtr ed_curr = dynamic_pointer_cast<EnchantmentDec>(curr);
        int i = 1;
        // cout << "i: " << i << endl;
        while (EnchantmentDecPtr ed_curr = dynamic_pointer_cast<EnchantmentDec>(curr)) {
            // cout << "hi" << endl;
            // cout << "i: " << i << endl;

            if (ed_curr->isHidden()) { curr = ed_curr->getNext(); continue; }
            // display ed_curr
            displayCard(minionpsn[i][0], minionpsn[i][1], hand_cardwidth, hand_cardheight, ed_curr);

            // reset curr to next
            curr = ed_curr->getNext();
            ++i;
        }
        displayCard(minionpsn[0][0], minionpsn[0][1], hand_cardwidth, hand_cardheight, curr);
     }
    
}


