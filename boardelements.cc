#include <iostream>
#include <fstream>
#include "boardelements.h"
#include "exceptions.h"
using namespace std;

Deck::Deck() {

}

Deck::~Deck() {}

Card* createCard(string cardName, Player* p) {
    Card* card;
    /* Minions: */
    if (cardName == "Air Elemental") card = new DefaultMinion(CardName::AirElemental, 0, 1, 1);
    else if (cardName == "Earth Elemental") card = new DefaultMinion(CardName::EarthElemental, 3, 4, 4);
    else if (cardName == "Bone Golem") card = new DefaultMinion(CardName::BoneGolem, 2, 1, 3, "Gain +1/+1 whenever a minion leaves play.");
    else if (cardName == "Fire Elemental") card = new DefaultMinion(CardName::FireElemental, 2, 2, 2, "Whenever an opponent's minion enters play, deal 1 damage to it.");
    else if (cardName == "Potion Seller") card = new DefaultMinion(CardName::PotionSeller, 2, 1, 3, "At the end of your turn, all your minions gain +0/+1.");
    else if (cardName == "Novice Pyromancer") card = new DefaultMinion(CardName::NovicePyromancer, 1, 0, 1, "Deal 1 damage to target minion.");
    else if (cardName == "Apprentice Summoner") card = new DefaultMinion(CardName::ApprenticeSummoner, 1, 1, 1, "Summon a 1/1 air elemental.");
    else if (cardName == "Master Summoner") card = new DefaultMinion(CardName::MasterSummoner, 3, 2, 3, "Summon up to three 1/1 air elementals.");

    /* Enchantments: */
    else if (cardName == "Giant Strength") card = new Enchantment(CardName::GiantStrength, 1, "", "+2", "+2");
    else if (cardName == "Enrage") card = new Enchantment(CardName::Enrage, 2, "", "*2", "*2");
    else if (cardName == "Haste") card = new Enchantment(CardName::Haste, 1, "Enchanted minion gains +1 action each turn");
    else if (cardName == "Magic Fatigue") card = new Enchantment(CardName::MagicFatigue, 0, "Enchanted minion's activated ability costs 2 more");
    else if (cardName == "Silence") card = new Enchantment(CardName::Silence, 1, "Enchanted minion cannot use abilities");
    
    /* Spells: */ 
    else if (cardName == "Recharge") card = new Spell(CardName::Recharge, 1, false, "Your ritual gains 3 charges", new RechargeAbility{});

    /* Rituals: */ 
    else if (cardName == "Dark Ritual") card = new Ritual(CardName::DarkRitual, "At the start of your turn, gain 1 magic", 0, 1, 5, new DarkRitualAbility{p});
    else if (cardName == "Aura of Power") card = new Ritual(CardName::AuraOfPower, "Whenever a minion enters play under your control, it gains +1/+1", 1, 1, 4, new AuraOfPowerAbility{p});
    else if (cardName == "Standstill") card = new Ritual(CardName::Standstill, "Whenever a minion enters play under your control, destroy it", 3, 2, 4, new StandstillAbility{p});
    
    else return nullptr;
    return card;
}

void Deck::init(ifstream& file, Player* p) {
    string cardName;
    while (getline(file, cardName) && cardName != "") {
        // an function to make the different cards?

        Card* newCard = createCard(cardName, p);

        // add to theDeck if it is a valid card (not nullptr)
        if (newCard) theDeck.emplace_back(newCard);
    }
}

void Deck::TEST_printDeck() {
    for (auto s : theDeck) { cout << *s << endl; }
}

Card* Deck::drawCard() {
    Card* card = theDeck.back();
    theDeck.pop_back();
    return card;
}

size_t Deck::getSize() {return theDeck.size();}


/* HAND */
void Hand::init(Deck& deck) {
    size_t deckSize = deck.getSize();
    for (size_t i = 0; i < deckSize && i < 5; ++i) {
        theHand.emplace_back(deck.drawCard());
    }
}

void Hand::addCard(Card* c) {
    if (theHand.size() == 5) throw invalid_play{"Hand is already full. Draw failed."};
    theHand.emplace_back(c);
}

Card* Hand::getCard(int i) const {
    return theHand[i];
}

size_t Hand::getSize() {return theHand.size();}

void Hand::TEST_printHand() {
    for (size_t i = 0; i < theHand.size(); ++i) {
        cout << "Hand (" << (i+1) << "): " << *theHand[i] << endl;
    }
}

void Hand::restoreAction() {
    for (auto card : theHand) {
        // type check for Minions
        if (Minion* minionCard = dynamic_cast<Minion*>(card)) {
            minionCard->setAction(1);
        }
        // Minion* minionCard = dynamic_cast<Minion*>(card);
        // minionCard->setAction(1);
    }
}

void Hand::removeCard(int i) {
    theHand.erase(theHand.begin() + i);
}


/* BOARD */
void Board::attach(TriggeredAbility* o) {
    boardObservers.emplace_back(o);
}

void Board::notifyMinionEnterObservers(Minion* targetMinion) {
    for (auto o : boardObservers) {
        if (o->getType() == TriggerType::MinionEnter) {
            o->setTargetMinion(targetMinion);
            o->applyAbility();
        }
    }
}

void Board::notifyMinionLeaveObservers(Minion* targetMinion) {
    for (auto o : boardObservers) {
        if (o->getType() == TriggerType::MinionLeave) {
            o->setTargetMinion(targetMinion);
            o->applyAbility();
        }
    }
}

Minion* Board::getCard(int i) const {
    return theBoard[i];
}

void Board::addCard(Minion *m) {
    theBoard.emplace_back(m);
    notifyMinionEnterObservers(m);
}

void Board::enchantMinion(int i, string minionName) {
    if (minionName == "Giant Strength") theBoard[i] = new GiantStrength(theBoard[i]); 
    else if (minionName == "Enrage") theBoard[i] = new Enrage(theBoard[i]);
    else if (minionName == "Haste") theBoard[i] = new Haste(theBoard[i]);
    else if (minionName == "Magic Fatigue") theBoard[i] = new MagicFatigue(theBoard[i]);
    else if (minionName == "Silence") theBoard[i] = new Silence(theBoard[i]);
}

void Board::restoreAction() {
    for (auto minion : theBoard) {
        minion->setAction(1);
    }
}

bool Board::contains(Minion* m) {
    auto it = find(theBoard.begin(), theBoard.end(), m);
    if (it != theBoard.end()) return true; // found
    return false;
}

void Board::TEST_printBoard() {
    for (size_t i = 0; i < theBoard.size(); ++i) {
        // cout << "Board (" << (i+1) << "): " << theBoard[i];
        cout << "Board (" << (i+1) << "): " << *theBoard[i] <<  " ["<< theBoard[i]->getAction() << " action | " << theBoard[i]->getAttack() << " attack | " << theBoard[i]->getDefense() << " defense]" << endl;
    }
}
