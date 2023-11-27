#include <iostream>
#include <fstream>
#include "boardelements.h"
using namespace std;

Deck::Deck() {

}

Deck::~Deck() {}

Card* createCard(string cardName) {
    Card* card;
    if (cardName == "Air Elemental") card = new DefaultMinion(CardName::AirElemental, 0, CardType::Minion, 1, 1);
    else if (cardName == "Earth Elemental") card = new DefaultMinion(CardName::EarthElemental, 3, CardType::Minion, 4, 4);
    else if (cardName == "Bone Golem") card = new DefaultMinion(CardName::BoneGolem, 2, CardType::Minion, 1, 3, "Gain +1/+1 whenever a minion leaves play.");
    else if (cardName == "Fire Elemental") card = new DefaultMinion(CardName::FireElemental, 2, CardType::Minion, 2, 2, "Whenever an opponent's minion enters play, deal 1 damage to it.");
    else if (cardName == "Potion Seller") card = new DefaultMinion(CardName::PotionSeller, 2, CardType::Minion, 1, 3, "At the end of your turn, all your minions gain +0/+1.");
    else if (cardName == "Novice Pyromancer") card = new DefaultMinion(CardName::NovicePyromancer, 1, CardType::Minion, 0, 1, "Deal 1 damage to target minion.");
    else if (cardName == "Apprentice Summoner") card = new DefaultMinion(CardName::ApprenticeSummoner, 1, CardType::Minion, 1, 1, "Summon a 1/1 air elemental.");
    else if (cardName == "Master Summoner") card = new DefaultMinion(CardName::MasterSummoner, 3, CardType::Minion, 2, 3, "Summon up to three 1/1 air elementals.");
    // to do: add decorators and abilities to minions, add other kinds of cards
    else return nullptr;
    return card;
}

void Deck::init(ifstream& file) {
    string cardName;
    while (getline(file, cardName) && cardName != "") {
        // an function to make the different cards?

        Card* newCard = createCard(cardName);

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

Card* Hand::getCard(int i) const {
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
        Minion* minionCard = dynamic_cast<Minion*>(card);
        minionCard->setAction(1);
    }
}

void Hand::removeCard(int i) {
    theHand.erase(theHand.begin() + i);
}

/* BOARD */
Minion* Board::getCard(int i) const {
    return theBoard[i];
}

void Board::addCard(Minion *m) {
    theBoard.emplace_back(m);
}

void Board::restoreAction() {
    for (auto minion : theBoard) {
        minion->setAction(1);
    }
}

void Board::TEST_printBoard() {
    for (size_t i = 0; i < theBoard.size(); ++i) {
        cout << "Board (" << (i+1) << "): " << *theBoard[i] << " [" << theBoard[i]->getAction() << " action]" << endl;
    }
}