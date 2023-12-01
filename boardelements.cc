#include <iostream>
#include <fstream>
#include "boardelements.h"
#include "exceptions.h"
using namespace std;

Deck::Deck() {

}

Deck::~Deck() {}

CardPtr createCard(string cardName) {
    CardPtr card;
    /* Minions: */
    if (cardName == "Air Elemental") card.reset(new DefaultMinion(CardName::AirElemental, 0, 1, 1));
    else if (cardName == "Earth Elemental") card.reset(new DefaultMinion(CardName::EarthElemental, 3, 4, 4));
    else if (cardName == "Bone Golem") card.reset(new DefaultMinion(CardName::BoneGolem, 2, 1, 3, "Gain +1/+1 whenever a minion leaves play."));
    else if (cardName == "Fire Elemental") card.reset(new DefaultMinion(CardName::FireElemental, 2, 2, 2, "Whenever an opponent's minion enters play, deal 1 damage to it."));
    else if (cardName == "Potion Seller") card.reset( new DefaultMinion(CardName::PotionSeller, 2, 1, 3, "At the end of your turn, all your minions gain +0/+1."));
    else if (cardName == "Novice Pyromancer") card.reset( new DefaultMinion(CardName::NovicePyromancer, 1, 0, 1, "Deal 1 damage to target minion."));
    else if (cardName == "Apprentice Summoner") card.reset(new DefaultMinion(CardName::ApprenticeSummoner, 1, 1, 1, "Summon a 1/1 air elemental."));
    else if (cardName == "Master Summoner") card.reset( new DefaultMinion(CardName::MasterSummoner, 3, 2, 3, "Summon up to three 1/1 air elementals."));

    /* Enchantments: */
    else if (cardName == "Giant Strength") card.reset( new Enchantment(CardName::GiantStrength, 1, "", "+2", "+2"));
    else if (cardName == "Enrage") card.reset( new Enchantment(CardName::Enrage, 2, "", "*2", "*2"));
    else if (cardName == "Haste") card.reset( new Enchantment(CardName::Haste, 1, "Enchanted minion gains +1 action each turn"));
    else if (cardName == "Magic Fatigue") card.reset(new Enchantment(CardName::MagicFatigue, 0, "Enchanted minion's activated ability costs 2 more"));
    else if (cardName == "Silence") card.reset(new Enchantment(CardName::Silence, 1, "Enchanted minion cannot use abilities"));
    
    /* Spells: */ 
    else if (cardName == "Recharge") card.reset(new Spell(CardName::Recharge, 1, false, "Your ritual gains 3 charges", new RechargeAbility{}));

    /* Rituals: */ 
    else if (cardName == "Dark Ritual") card.reset(new Ritual(CardName::DarkRitual, "At the start of your turn, gain 1 magic", 0, 1, 5));
    // to do: add decorators (done?) and abilities to minions, add other kinds of cards
 
    return card;
}

void Deck::init(ifstream& file) {
    string cardName;
    while (getline(file, cardName) && cardName != "") {
        // an function to make the different cards?

        CardPtr newCard = createCard(cardName);

        // add to theDeck if it is a valid card (not nullptr)
        if (newCard) theDeck.emplace_back(newCard);
    }
}

void Deck::TEST_printDeck() {
    for (auto s : theDeck) { cout << *s << endl; }
}

CardPtr Deck::drawCard() {
    CardPtr card = theDeck.back();
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

void Hand::addCard(CardPtr c) {
    if (theHand.size() == 5) throw invalid_play{"Hand is already full. Draw failed."};
    theHand.emplace_back(c);
}

CardPtr Hand::getCard(int i) const {
    return theHand[i];
}

void Hand::TEST_printHand() {
    for (size_t i = 0; i < theHand.size(); ++i) {
        cout << "Hand (" << (i+1) << "): " << *theHand[i] << endl;
    }
}

void Hand::restoreAction() {
    for (auto card : theHand) {
        // type check for Minions
        Minion *minionCard = dynamic_cast<Minion*>(card.get());
        if (minionCard != nullptr) {
            
            minionCard->setAction(1);
        }

        // MinionPtr minionCard = dynamic_cast<MinionPtr>(card);
        // minionCard->setAction(1);
    }
}

void Hand::removeCard(int i) {
    theHand.erase(theHand.begin() + i);
}

int Hand::getSize() { return theHand.size(); }

/* BOARD */
MinionPtr Board::getCard(int i) const {
    return theBoard[i];
}

void Board::addCard(MinionPtr m) {
    theBoard.emplace_back(m);
}

void Board::enchantMinion(int i, string minionName) {
    if (minionName == "Giant Strength") theBoard[i].reset(new GiantStrength(theBoard[i])); 
    else if (minionName == "Enrage") theBoard[i].reset(new Enrage(theBoard[i]));
    else if (minionName == "Haste") theBoard[i].reset(new Haste(theBoard[i]));
    else if (minionName == "Magic Fatigue") theBoard[i].reset(new MagicFatigue(theBoard[i]));
    else if (minionName == "Silence") theBoard[i].reset(new Silence(theBoard[i]));
}

void Board::restoreAction() {
    for (auto minion : theBoard) {
        minion->setAction(1);
    }
}

void Board::TEST_printBoard() {
    for (size_t i = 0; i < theBoard.size(); ++i) {
        // cout << "Board (" << (i+1) << "): " << theBoard[i];
        cout << "Board (" << (i+1) << "): " << *theBoard[i] <<  " ["<< theBoard[i]->getAction() << " action | " << theBoard[i]->getAttack() << " attack | " << theBoard[i]->getDefense() << " defense]" << endl;
    }
}

int Board :: getBoardSize() {
    return theBoard.size();
}
