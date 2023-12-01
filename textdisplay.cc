#include <iostream>
#include <string>
#include "textdisplay.h"
#include "ascii_graphics.h"
#include "gamemaster.h"
using namespace std;


// print a card/board element
void print(const card_template_t &t) {
  for (auto row : t) { 
    cout << row << endl;
  }
}

// print cards from a vector of templates
void printCardRow(const vector<card_template_t> &ct) {
  for (int j = 0; j < 11; j++) {
    for (int i = 0; i < ct.size(); i ++){
      cout << ct[i][j];
    }
    cout << endl;
  }
}

// TextDisplay Constructor
TextDisplay::TextDisplay(GameMaster *_gm) : gm(_gm) {}

TextDisplay::~TextDisplay() = default;

void TextDisplay::displayMsg(string msg) {
    cout << msg << endl;
}


// Print the hand of player number [p] to stdout
// IF HAND IS EMPTY< PRINT EMPTY CARD
void TextDisplay::displayHand(int p) {
  int len = gm->getPlayer(p).getHand().getSize();

  // create a vector of all cardtemplates to print 
  vector<card_template_t> toPrint;

  // iterate through all items in the hand
  for (int i = 0; i < len; ++i) {

    string name = gm->getPlayer(p).getHand().getCard(i)->getName();
    string desc = gm->getPlayer(p).getHand().getCard(i)->getDesc();
    int cost = gm->getPlayer(p).getHand().getCard(i)->getCost();

    // if the card is an enchantment
    if (gm->getPlayer(p).getHand().getCard(i)->getType() == CardType::Enchantment) {
      toPrint.emplace_back(display_enchantment(name, cost, desc));
    
    //if the card is a spell
    } else if (gm->getPlayer(p).getHand().getCard(i)->getType() == CardType::Spell){
      toPrint.emplace_back(display_spell(name, cost, desc));

    // else, check the card one by one
    } else {
      // if minion:
      switch(gm->getPlayer(p).getHand().getCard(i)->getCardName()) {
        case(CardName::AirElemental):
          toPrint.emplace_back(display_minion_no_ability(name, cost, p, p));
          break;
        case(CardName::EarthElemental):
          toPrint.emplace_back(display_minion_no_ability(name, cost, 4, 4));
          break;
        case(CardName::BoneGolem):
          toPrint.emplace_back(display_minion_no_ability(name, cost, p, 3));
          break;
        case(CardName::FireElemental):
          toPrint.emplace_back(display_minion_no_ability(name, cost, 2, 2));
          break;
        case(CardName::PotionSeller):
          toPrint.emplace_back(display_minion_no_ability(name, cost, p, 3));
          break;
        case(CardName::NovicePyromancer):
          toPrint.emplace_back(display_minion_no_ability(name, cost, i, p));
          break;
        case(CardName::ApprenticeSummoner):
          toPrint.emplace_back(display_minion_no_ability(name, cost, p, p));
          break;
        case(CardName::MasterSummoner):
          toPrint.emplace_back(display_minion_no_ability(name, cost, 2, 3));
          break;

        // if ritual:
        case(CardName::DarkRitual):
          // display_ritual(name, cost, ritual_cost,ritual_desc, ritual_charges); 
          cout << "ritual" << endl;
          break;
      }
    }
    // go to the left of the current card, change the cursor position
    // moveup(11);
    // moveright(34);
  }
  printCardRow(toPrint);
}

void TextDisplay::displayMinion() {
}

void TextDisplay::displaySorceryBoard() {

  // create a vector of all cardtemplates to print 
  vector<card_template_t> toPrint;

  int len1 = gm->getPlayer(1).getBoard().getBoardSize();
  int len2 = gm->getPlayer(2).getBoard().getBoardSize();

  // PRINT the board for player 1
  for (int i = 0; i < len1; ++i) {
    string name = gm->getPlayer(1).getBoard().getCard(i)->getName();
    string desc = gm->getPlayer(1).getBoard().getCard(i)->getDesc();
    int cost = gm->getPlayer(1).getBoard().getCard(i)->getCost();
    int attack = gm->getPlayer(1).getBoard().getCard(i)->getAttack();
    int defense = gm->getPlayer(1).getBoard().getCard(i)->getDefense();
    toPrint.emplace_back(display_minion_no_ability(name, cost, attack, defense));
  }
  printCardRow(toPrint);
  toPrint.clear();
  // PRINT the center graphic
  print(CENTRE_GRAPHIC);

  // PRINT the board for player 2
  for (int i = 0; i < len2; ++i) {
    string name = gm->getPlayer(2).getBoard().getCard(i)->getName();
    string desc = gm->getPlayer(2).getBoard().getCard(i)->getDesc();
    int cost = gm->getPlayer(2).getBoard().getCard(i)->getCost();
    int attack = gm->getPlayer(2).getBoard().getCard(i)->getAttack();
    int defense = gm->getPlayer(2).getBoard().getCard(i)->getDefense();
    toPrint.emplace_back(display_minion_no_ability(name, cost, attack, defense));
  }
  printCardRow(toPrint);
  toPrint.clear();
}



