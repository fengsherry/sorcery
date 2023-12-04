#include <iostream>
#include <string>
#include "textdisplay.h"
#include "minion.h"
#include "ascii_graphics.h"
#include "gamemaster.h"
using namespace std;

// print a card/board element
void print(const card_template_t &t) {
  for (auto row : t) { 
    cout << row << endl;
  }
}

// void printCardFiveRow(const vector<card_template_t> &ct) {
//   for (int j = 0; j < 11; j++) {
//     for (int i = 0; i < ct.size(); i ++) {
//       cout << ct[i][j];
//     }
//     cout << endl;
//     // TEST MORE THAN 5 ENCHANTMENTS, PRINT ON NEW LINE
//     if ((j % 5) == 0) {
//       cout << endl;
//     }
//   }
// }

// print cards from a vector of templates
void printCardRow(const vector<card_template_t> &ct) {
  for (int j = 0; j < 11; j++) {
    for (int i = 0; i < ct.size(); i ++){
      cout << ct[i][j];
    }
    cout << endl;
  }
}


// print cards with the boarder from a vector of templates
void printCardRowWithBorder(const vector<card_template_t> &ct) {
  for (int j = 0; j < 11; j++) {
    for (int i = 0; i < ct.size(); i ++) {
      if (i == 0) {
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN  << ct[i][j];
      } else if (i == ct.size() - 1) {
        cout << ct[i][j] << EXTERNAL_BORDER_CHAR_UP_DOWN;
      } else {
        cout << ct[i][j];
      }
    }
    cout << endl;
  }
}


// print the top/bottom board edge
void printTopBorder() {
  cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  for (int i = 0; i < 165; ++i) { 
    cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
}

void printBottomBorder() {
  cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (int i = 0; i < 165; ++i) { 
    cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}

void TextDisplay::printPlayerBoardRow(int p) {
  // print the top row for player 1
  vector<card_template_t> toPrint;
  //cout << p << endl;

  // Print the ritual card
  // string player1_name = gm->getPlayer(1).getRitual()->getName();
  // int player1_cost = gm->getPlayer(1).getRitual()->getCost();
  // int player1_ritual_cost = gm->getPlayer(1).getRitual()->getActivationCost();
  // string player1_ritual_desc = gm->getPlayer(1).getRitual()->getDesc();
  // int player1_ritual_charges = gm->getPlayer(1).getRitual()->getCharge();

  // toPrint.emplace_back(display_ritual(player1_name, player1_cost, player1_ritual_cost, player1_ritual_desc, player1_ritual_charges));
  // toPrint.emplace_back(CARD_TEMPLATE_EMPTY);

  // Print the name card
  string player_name = gm->getPlayer(p).getName();
  int player_life = gm->getPlayer(p).getLife();
  int player_mana = gm->getPlayer(p).getMagic();
  toPrint.emplace_back(CARD_TEMPLATE_BORDER);
  toPrint.emplace_back(CARD_TEMPLATE_EMPTY);
  toPrint.emplace_back(display_player_card(p, player_name, player_life, player_mana));
  toPrint.emplace_back(CARD_TEMPLATE_EMPTY);
  toPrint.emplace_back(CARD_TEMPLATE_BORDER);

  // Print the graveyard card
  // string grave_name = gm->getPlayer(p).getGrave().getGrave().top()->getName();
  // int grave_cost = gm->getPlayer(p).getGrave().getGrave().top()->getCost();
  // int grave_attack = gm->getPlayer(p).getGrave().getGrave().top()->getAttack();
  // int grave_defense = gm->getPlayer(p).getGrave().getGrave().top()->getDefense();
  // toPrint.emplace_back(display_minion_no_ability(grave_name, grave_cost, grave_attack, grave_defense));

  string grave_name = gm->getPlayer(p).getGrave().getGrave().top()->getName();
  int grave_cost = gm->getPlayer(p).getGrave().getGrave().top()->getCost();
  int grave_attack = gm->getPlayer(p).getGrave().getGrave().top()->getAttack();
  int grave_defense = gm->getPlayer(p).getGrave().getGrave().top()->getDefense();
  toPrint.emplace_back(display_minion_no_ability(grave_name, grave_cost, grave_attack, grave_defense));
  
  printCardRow(toPrint);
  toPrint.clear();
}

// TextDisplay Constructor
TextDisplay::TextDisplay(GameMaster *_gm) : gm(_gm) {}

TextDisplay::~TextDisplay() = default;

void TextDisplay::displayMsg(vector<string> msg, int p) {
  // cout << "hi" << endl;
  for (string s : msg) {
    cout << s << endl;
  }
  
}

// Print the hand of player number [p] to stdout
// IF HAND IS EMPTY, PRINT EMPTY CARD
void TextDisplay::displayHand(int p) {

  // create a vector of all cardtemplates to print 
  vector<card_template_t> toPrint;

  int len = gm->getPlayer(p).getHand().getSize();

  // iterate through all items in the hand
  for (int i = 0; i < len; ++i) {

    string name = gm->getPlayer(p).getHand().getCard(i)->getName();
    string desc = gm->getPlayer(p).getHand().getCard(i)->getDesc();
    int cost = gm->getPlayer(p).getHand().getCard(i)->getCost();

    // if the card is an enchantment
    if (gm->getPlayer(p).getHand().getCard(i)->getType() == CardType::Enchantment) {
      toPrint.emplace_back(display_enchantment(name, cost, desc));
    
    //if the card is a spell
    } else if (gm->getPlayer(p).getHand().getCard(i)->getType() == CardType::Spell) {
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
          toPrint.emplace_back(display_ritual(name, cost, 1, desc, 5)); 
          break;
        // case(CardName::AuraOfPower):
        //   display_ritual(name, cost, 1, desc, 4); 
        //   cout << "ritual" << endl;
        //   break;
        // case(CardName::Standstill):
        //   display_ritual(name, cost, 2, desc, 4); 
        //   cout << "ritual" << endl;
        //   break;

        // if enchantment
        case(CardName::GiantStrength):
          toPrint.emplace_back(display_enchantment_attack_defence(name, cost, desc, "+2", "+2"));
          break;
        case(CardName::Enrage):
          toPrint.emplace_back(display_enchantment_attack_defence(name, cost, desc, "*2", "*2"));
          break;
        case(CardName::Haste):
          toPrint.emplace_back(display_enchantment(name, cost, desc));
          break;
        case(CardName::MagicFatigue):
          toPrint.emplace_back(display_enchantment(name, cost, desc));
          break;
        case(CardName::Silence):
          toPrint.emplace_back(display_enchantment(name, cost, desc));
          break;

        // if spell
        case(CardName::Banish):
          toPrint.emplace_back(display_spell(name, cost, desc));
          break;
        case(CardName::Unsummon):
          toPrint.emplace_back(display_spell(name, cost, desc));
          break;
        case(CardName::Recharge):
          toPrint.emplace_back(display_spell(name, cost, desc));
          break;
        case(CardName::Disenchant):
          toPrint.emplace_back(display_spell(name, cost, desc));
          break;
        case(CardName::RaiseDead):
          toPrint.emplace_back(display_spell(name, cost, desc));
          break;
        case(CardName::Blizzard):
          toPrint.emplace_back(display_spell(name, cost, desc));
          break;
      }
    }
    // go to the left of the current card, change the cursor position
    // moveup(11);
    // moveright(34);
  }
  printCardRow(toPrint);
}

// returns a vector of card_templates that has the default minion in the first position and the rest of the enchantments after in the vector
vector<card_template_t> &addEnchantmentPrint(const MinionPtr m, vector<card_template_t> &toPrint) {
  if (DefaultMinionPtr dm = dynamic_pointer_cast<DefaultMinion>(m)) {
    toPrint.insert(toPrint.begin(), display_minion_no_ability(m->getDefaultMinionName(), m->getCost(), m->getAttack(), m->getDefense()));
    return toPrint;

  // if there are enchantments on the minion
  } else {
    EnchantmentDecPtr ed = dynamic_pointer_cast<EnchantmentDec>(m);

    switch(m->getCardName()) {
      case(CardName::GiantStrength):
        toPrint.emplace_back(display_enchantment_attack_defence(m->getName(), m->getCost(), m->getDesc(), "+2", "+2"));
        break;
      case(CardName::Enrage):
        toPrint.emplace_back(display_enchantment_attack_defence(m->getName(), m->getCost(), m->getDesc(), "*2", "*2"));
        break;
      case(CardName::Haste):
        toPrint.emplace_back(display_enchantment(m->getName(), m->getCost(), m->getDesc()));
        break;
      case(CardName::MagicFatigue):
        toPrint.emplace_back(display_enchantment(m->getName(), m->getCost(), m->getDesc()));
        break;
      case(CardName::Silence):
        toPrint.emplace_back(display_enchantment(m->getName(), m->getCost(), m->getDesc()));
        break;
    }
    addEnchantmentPrint(ed->getNext(), toPrint);
  }
}

void TextDisplay::displayMinion(const MinionPtr m) {
  vector<card_template_t> toPrint;
  addEnchantmentPrint(m, toPrint);

  //print the minion first
  print(toPrint.at(0));

  if (!toPrint.empty()) {
    toPrint.erase(toPrint.begin());
  }
  // print the rest of the enchantment cards in rows of 5's
  printCardRow(toPrint);
  toPrint.clear();
}


void TextDisplay::displaySorceryBoard() {
  printTopBorder();
  printPlayerBoardRow(1);

  // create a vector of all cardtemplates to print 
  vector<card_template_t> toPrint;

  int len1 = gm->getPlayer(1).getBoard().size();
  int len2 = gm->getPlayer(2).getBoard().size();

  // PRINT the board for player 1
  // if the card is a minion:
  for (int i = 0; i < len1; ++i) {
    string name = gm->getPlayer(1).getBoard().getCard(i)->getDefaultMinionName();
    string desc = gm->getPlayer(1).getBoard().getCard(i)->getDefaultMinionDesc();
    int cost = gm->getPlayer(1).getBoard().getCard(i)->getCost();
    int attack = gm->getPlayer(1).getBoard().getCard(i)->getAttack();
    int defense = gm->getPlayer(1).getBoard().getCard(i)->getDefense();

    // if activated ability, use the template
    if (holds_alternative<ActivatedAbility*>(gm->getPlayer(1).getBoard().getCard(i)->getAbility())) {

      auto a = gm->getPlayer(1).getBoard().getCard(i)->getAbility();
      int ability_cost = get<ActivatedAbility*>(a)->getActivationCost();

      toPrint.emplace_back(display_minion_activated_ability(name, cost, attack, defense, ability_cost, desc));

    // if triggered ability, use the template
    } else if (holds_alternative<TriggeredAbility*>(gm->getPlayer(1).getBoard().getCard(i)->getAbility())) {
      toPrint.emplace_back(display_minion_triggered_ability(name, cost, attack, defense, desc));
    
    } else { // print the no ability minion
      toPrint.emplace_back(display_minion_no_ability(name, cost, attack, defense));
    }
  }

  //print empty cards on the board
  for (int i = len1; i < 5; ++i) {
    toPrint.emplace_back(CARD_TEMPLATE_BORDER);
  }

  printCardRowWithBorder(toPrint);
  toPrint.clear();

  // PRINT the center graphic
  print(CENTRE_GRAPHIC);

  // PRINT the board for player 2
  for (int i = 0; i < len2; ++i) {
    string name = gm->getPlayer(2).getBoard().getCard(i)->getDefaultMinionName();
    string desc = gm->getPlayer(2).getBoard().getCard(i)->getDefaultMinionDesc();
    int cost = gm->getPlayer(2).getBoard().getCard(i)->getCost();
    int attack = gm->getPlayer(2).getBoard().getCard(i)->getAttack();
    int defense = gm->getPlayer(2).getBoard().getCard(i)->getDefense();

        // if activated ability, use the template
    if (holds_alternative<ActivatedAbility*>(gm->getPlayer(2).getBoard().getCard(i)->getAbility())) {
      auto a = gm->getPlayer(1).getBoard().getCard(i)->getAbility();
      int ability_cost = get<ActivatedAbility*>(a)->getActivationCost();
      toPrint.emplace_back(display_minion_activated_ability(name, cost, attack, defense, ability_cost, desc));

    // if triggered ability, use the template
    } else if (holds_alternative<TriggeredAbility*>(gm->getPlayer(2).getBoard().getCard(i)->getAbility())) {
      toPrint.emplace_back(display_minion_triggered_ability(name, cost, attack, defense, desc));
    
    } else { // print the no ability minion
      toPrint.emplace_back(display_minion_no_ability(name, cost, attack, defense));
    }
  }

  //print empty cards on the board
  for (int i = len2; i < 5; ++i) {
    toPrint.emplace_back(CARD_TEMPLATE_BORDER);
  }

  printCardRowWithBorder(toPrint);
  toPrint.clear();

  // print the top row for player 2
  printPlayerBoardRow(2);
  printBottomBorder();
}



