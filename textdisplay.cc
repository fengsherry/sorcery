#include <iostream>
#include <string>
#include "textdisplay.h"
#include "ascii_graphics.h"
#include "gamemaster.h"
using namespace std;

// TextDisplay Constructor
TextDisplay::TextDisplay(GameMaster *_gm) : gm(_gm) {}

TextDisplay::~TextDisplay() = default;

void TextDisplay::displayMsg(string msg) {
    cout << msg << endl;
}

void TextDisplay::displayHand(int p) {
  int len = gm->getPlayer(p).getHand().getSize();

  // iterate through all items in the hand
  for (int i = 0; i < len; ++i) {

    string name = gm->getPlayer(p).getHand().getCard(i)->getName();
    string desc = gm->getPlayer(p).getHand().getCard(i)->getDesc();
    int cost = gm->getPlayer(p).getHand().getCard(i)->getCost();

    // if the card is an enchantment
    if (gm->getPlayer(p).getHand().getCard(i)->getType() == CardType::Enchantment) {
      display_enchantment(name, cost, desc);
    
    //if the card is a spell
    } else if (gm->getPlayer(p).getHand().getCard(i)->getType() == CardType::Spell){
      display_spell(name, cost, desc);

    // else, check the card one by one
    } else {
      // if minion:
      switch(gm->getPlayer(p).getHand().getCard(i)->getCardName()) {
        case(CardName::AirElemental):
          display_minion_no_ability(name, cost, p, p);
          break;
        case(CardName::EarthElemental):
          display_minion_no_ability(name, cost, 4, 4);
          break;
        case(CardName::BoneGolem):
          display_minion_no_ability(name, cost, p, 3);
          break;
        case(CardName::FireElemental):
          display_minion_no_ability(name, cost, 2, 2);
          break;
        case(CardName::PotionSeller):
          display_minion_no_ability(name, cost, p, 3);
          break;
        case(CardName::NovicePyromancer):
          display_minion_no_ability(name, cost, i, p);
          break;
        case(CardName::ApprenticeSummoner):
          display_minion_no_ability(name, cost, p, p);
          break;
        case(CardName::MasterSummoner):
          display_minion_no_ability(name, cost, 2, 3);
          break;

        // if ritual:
        case(CardName::DarkRitual):
          // display_ritual(name, cost, ritual_cost,ritual_desc, ritual_charges); 
          cout << "ritual" << endl;
          break;
      }
    }
  }

  // if minion
  
}

void TextDisplay::displayMinion() {
}

void TextDisplay::displaySorceryBoard() {
  string name = gm->getPlayer(p).getBoard().getCard(i)->getName();
  int cost = gm->getPlayer(p).getBoard().getCard(i)->getCost();
  int attack = gm->getPlayer(p).getBoard().getCard(i)->getAttack();
  int defense = gm->getPlayer(p).getBoard().getCard(i)->getDefense();
  display_minion_no_ability(name, cost, attack, defense);

}

