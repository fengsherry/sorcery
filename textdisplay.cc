#include <iostream>
#include <string>
#include "textdisplay.h"
#include "minion.h"
#include "ascii_graphics.h"
#include "gamemaster.h"
#include "exceptions.h"
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
    for (size_t i = 0; i < ct.size(); i ++){
      cout << ct[i][j];
    }
    cout << endl;
  }
}

// adds the ability to print 5 cards in a row if the vector contains >5 elements
void printCardFiveRow(const vector<card_template_t> &ct) {
  if (ct.size() <= 5) {
    printCardRow(ct);
  } else {
    vector<card_template_t> ct2(ct);

    while (!ct2.empty()) {

      // print the first 5 cards
      for (int j = 0; j < 11; ++j) {
        for (int i = 0; i < 5; ++i) {
          cout << ct[i][j];
        }
        cout << endl;
      }
      // Erase the first 5 elements
      ct2.erase(ct2.begin(), ct2.begin() + 5);

      // if the rest of the elements <= 5, print normally
      if (ct2.size() <= 5) {
        printCardRow(ct2);
        break;
      }
    }
  }
}

// print cards with the boarder from a vector of templates
void printCardRowWithBorder(const vector<card_template_t> &ct) {
  for (int j = 0; j < 11; j++) {
    for (size_t i = 0; i < ct.size(); i ++) {
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

// print the top row for player each player, consists of:
//  ritual card, blank, name card, blank, graveyard
void TextDisplay::printPlayerBoardRow(int p) {
  vector<card_template_t> toPrint;
  
  // Print the ritual card
  if(gm->getPlayer(p).getRitual()) {
    string player_r_name = gm->getPlayer(p).getRitual()->getName();
    int player_r_cost = gm->getPlayer(p).getRitual()->getCost();
    int player_ritual_cost = gm->getPlayer(p).getRitual()->getActivationCost();
    string player_ritual_desc = gm->getPlayer(p).getRitual()->getDesc();
    int player_ritual_charges = gm->getPlayer(p).getRitual()->getCharge();
    toPrint.emplace_back(display_ritual(player_r_name, player_r_cost, player_ritual_cost, player_ritual_desc, player_ritual_charges));
  } else {
    toPrint.emplace_back(CARD_TEMPLATE_BORDER);
  }

  toPrint.emplace_back(CARD_TEMPLATE_EMPTY);

  // Print the name card
  string player_name = gm->getPlayer(p).getName();
  int player_life = gm->getPlayer(p).getLife();
  int player_mana = gm->getPlayer(p).getMagic();

  toPrint.emplace_back(display_player_card(p, player_name, player_life, player_mana));
  toPrint.emplace_back(CARD_TEMPLATE_EMPTY);

  // Print the graveyard card
  if(!gm->getPlayer(p).getGrave().isEmpty()) {
    string grave_name = gm->getPlayer(p).getGrave().getGrave().top()->getName();
    int grave_cost = gm->getPlayer(p).getGrave().getGrave().top()->getCost();
    int grave_attack = gm->getPlayer(p).getGrave().getGrave().top()->getAttack();
    int grave_defense = gm->getPlayer(p).getGrave().getGrave().top()->getDefense();
    toPrint.emplace_back(display_minion_no_ability(grave_name, grave_cost, grave_attack, grave_defense));
  } else {
    toPrint.emplace_back(CARD_TEMPLATE_BORDER);
  }
  printCardRowWithBorder(toPrint);
  toPrint.clear();
}

// TextDisplay Constructor
TextDisplay::TextDisplay(GameMaster *_gm) : gm(_gm) {}

TextDisplay::~TextDisplay() = default;

void TextDisplay::displayMsg(vector<string> msg, int p) {
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
    string name;
    string desc;
    int cost;

    CardPtr c = gm->getPlayer(p).getHand().getCard(i);
    if (MinionPtr mptr = dynamic_pointer_cast<Minion>(c)) {
      name = mptr->getDefaultMinionName();
      desc = mptr->getDefaultMinionDesc();
      cost = mptr->getCost();
    } else {
      name = gm->getPlayer(p).getHand().getCard(i)->getName();
      desc = gm->getPlayer(p).getHand().getCard(i)->getDesc();
      cost = gm->getPlayer(p).getHand().getCard(i)->getCost();
    }

    //if the card is a spell
    if (gm->getPlayer(p).getHand().getCard(i)->getType() == CardType::Spell) {
      toPrint.emplace_back(display_spell(name, cost, desc));

    // else, check the card one by one
    } else {
      // if minion:
      switch(gm->getPlayer(p).getHand().getCard(i)->getCardName()) {
        case(CardName::AirElemental):
          toPrint.emplace_back(display_minion_no_ability(name, cost, 1, 1));
          break;
        case(CardName::EarthElemental):
          toPrint.emplace_back(display_minion_no_ability(name, cost, 4, 4));
          break;
        case(CardName::BoneGolem):
          toPrint.emplace_back(display_minion_triggered_ability(name, cost, 1, 3, desc));
          break;
        case(CardName::FireElemental):
          toPrint.emplace_back(display_minion_triggered_ability(name, cost, 2, 2, desc));
          break;
        case(CardName::PotionSeller):
          toPrint.emplace_back(display_minion_triggered_ability(name, cost, 1, 3, desc));
          break;
        case(CardName::NovicePyromancer):
          toPrint.emplace_back(display_minion_activated_ability(name, cost, 0, 1, 1, desc));
          break;
        case(CardName::ApprenticeSummoner):
          toPrint.emplace_back(display_minion_activated_ability(name, cost, 1, 1, 1, desc));
          break;
        case(CardName::MasterSummoner):
          toPrint.emplace_back(display_minion_activated_ability(name, cost, 2, 3, 2, desc));
          break;

        // if ritual:
        case(CardName::DarkRitual):
          toPrint.emplace_back(display_ritual(name, cost, 1, desc, 5)); 
          break;
        case(CardName::AuraOfPower):
          toPrint.emplace_back(display_ritual(name, cost, 1, desc, 4)); 
          break;
        case(CardName::Standstill):
          toPrint.emplace_back(display_ritual(name, cost, 2, desc, 4)); 
          break;

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
        default: break;
      }
    }
    // go to the left of the current card, change the cursor position
    // moveup(11);
    // moveright(34);
  }
  printCardRow(toPrint);
}

// returns a vector of card_templates that has the default minion in the first position and the rest of the enchantments after in the vector
vector<card_template_t> &addEnchantmentPrint(const MinionPtr m, vector<card_template_t> &toPrint, int count) {
  //card_template_t NULL_TEMPLATE;

  if (DefaultMinionPtr dm = dynamic_pointer_cast<DefaultMinion>(m)) {
    toPrint.insert(toPrint.begin(), display_minion_no_ability(m->getDefaultMinionName(), m->getCost(), m->getAttack(), m->getDefense()));
    return toPrint;

  // if there are enchantments on the minion
  } else {
    EnchantmentDecPtr ed = dynamic_pointer_cast<EnchantmentDec>(m);

    // // add a placeholder so the print method can print a newline
    // if (count != 0 && count % 5 == 0) {
    //   toPrint.emplace_back(NULL_TEMPLATE);
    // }

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
      default: break;
    }
    addEnchantmentPrint(ed->getNext(), toPrint, count++);
  }
}

void TextDisplay::displayMinion(const MinionPtr m) {
  vector<card_template_t> toPrint;
  
  if (!(m->getType() == CardType::Minion)) {
    throw invalid_inspect_type(m);
  }

  addEnchantmentPrint(m, toPrint, 0);

  // print the minion first
  print(toPrint.at(0));

  // delete the minion card from the toPrint vector
  if (!toPrint.empty()) {
    toPrint.erase(toPrint.begin());
  }
  // print the rest of the enchantment cards in rows of 5's
  printCardFiveRow(toPrint);
  toPrint.clear();
}

// displays the entore sorcery board: 
// player1 row, play1 board, center graphic, player 2 board, player 2 row, (+border)
void TextDisplay::displaySorceryBoard(int p) {
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
      // auto a = gm->getPlayer(1).getBoard().getCard(i)->getAbility();
      // int ability_cost = get<ActivatedAbility*>(a)->getActivationCost();
      int ability_cost = gm->getPlayer(1).getBoard().getCard(i)->getActivatedAbilityCost();
      toPrint.emplace_back(display_minion_activated_ability(name, cost, attack, defense, ability_cost, desc));

    // if triggered ability, use the template
    } else if (holds_alternative<TriggeredAbility*>(gm->getPlayer(1).getBoard().getCard(i)->getAbility())) {
      toPrint.emplace_back(display_minion_triggered_ability(name, cost, attack, defense, desc));
    
    } else { // else, print the no ability minion
      toPrint.emplace_back(display_minion_no_ability(name, cost, attack, defense));
    }
  }

  //print empty cards placements on the board
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
      // auto a = gm->getPlayer(1).getBoard().getCard(i)->getAbility();
      // int ability_cost = get<ActivatedAbility*>(a)->getActivationCost();
      int ability_cost = gm->getPlayer(2).getBoard().getCard(i)->getActivatedAbilityCost();
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



