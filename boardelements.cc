#include <iostream>
#include <fstream>
#include "boardelements.h"
#include "exceptions.h"
#include "sorceryutil.h"
using namespace std;

Deck::Deck() {

}

Deck::~Deck() {}

void Deck::init(ifstream& file, Player* p, bool random) {
    this->random = random;
    string cardName;
    while (getline(file, cardName) && cardName != "") {

        CardPtr newCard = createCard(cardName, p);

        // add to theDeck if it is a valid card (not nullptr)
        if (newCard) theDeck.emplace_back(newCard);
    }
}

void Deck::TEST_printDeck() {
    for (auto s : theDeck) { cout << s << endl; }
}

CardPtr Deck::drawCard() {
    CardPtr card;
    if (random) {
        // cout << "random!" << endl;
        int randomNumber = std::rand() % theDeck.size();
        // cout << randomNumber << endl;
        card = theDeck[randomNumber];
        theDeck.erase(theDeck.begin()+randomNumber);
    } else {
        card = theDeck.back();
        theDeck.pop_back();
    }
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
    if (theHand.size() == 5) throw full_hand{};
    theHand.emplace_back(c);
}

CardPtr Hand::getCard(int i) const {
    return theHand[i];
}

size_t Hand::getSize() {return theHand.size();}

void Hand::TEST_printHand() {
    for (size_t i = 0; i < theHand.size(); ++i) {
        cout << "Hand (" << (i+1) << "): " << theHand[i] << endl;
    }
}

void Hand::restoreAction() {
    for (auto card : theHand) {
        // type check for Minions
       //  Minion *minionCard = dynamic_cast<Minion*>(card.get());
       MinionPtr minionCard = dynamic_pointer_cast<Minion>(card);
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

/* BOARD */
void Board::init(observersList* ol, Graveyard* gy) {
    this->ol = ol;
    grave = gy;
}

void Board::attach(TriggeredAbility* o) {
    ol->observers.emplace_back(o);
    
}

void Board::detach(TriggeredAbility* o) {
    for (auto it = ol->observers.begin(); it != ol->observers.end();) {
        if (*it == o) ol->observers.erase(it);
        else ++it;
    }
}

void Board::notifyMinionEnterObservers(MinionPtr targetMinion) {
    // for (auto o = observers->begin(); o != observers->end();) {
    //     try {
    //         if ((*o)->getType() == TriggerType::MinionEnter) {
    //             (*o)->setTargetMinion(targetMinion);
    //             (*o)->applyAbility();   
    //         }
    //         ++o;
    //     } catch (not_enough_charge& e) {
    //         observers->erase(o);
    //     }
    // }

    // with apnap
    
    try {
        auto o = ol->observers.begin();
        while (o != ol->observers.end()) {
            // cout << " HELLO " << z
            if ((*o)->getType() == TriggerType::MinionEnter && (*o)->getOwner() == ol->activePlayer && (*o)->getEnoughCharge()) { // TODO
                (*o)->setTargetMinion(targetMinion);
                (*o)->applyAbility();   
            }
            ++o;
        }
        o = ol->observers.begin();
        while (o != ol->observers.end()) {
            if ((*o)->getType() == TriggerType::MinionEnter && (*o)->getOwner() != ol->activePlayer && (*o)->getEnoughCharge()) { 
                (*o)->setTargetMinion(targetMinion);
                (*o)->applyAbility();   
            }
            ++o;
        }
    } catch (not_enough_charge& e) {}
}

void Board::notifyMinionLeaveObservers(MinionPtr targetMinion) {
    // for (auto o = observers->begin(); o != observers->end();) {
    //     try {
    //         if ((*o)->getType() == TriggerType::MinionLeave) {
    //             (*o)->setTargetMinion(targetMinion);
    //             (*o)->applyAbility();   
    //         }
    //         ++o;
    //     } catch (not_enough_charge& e) {
    //         observers->erase(o);
    //     }
    // }
    auto o = ol->observers.begin();
    try {
        while (o != ol->observers.end()) {
            if ((*o)->getType() == TriggerType::MinionLeave && (*o)->getOwner() == ol->activePlayer) { // TODO
                (*o)->setTargetMinion(targetMinion);
                cout << "target minion:" << targetMinion->getName() << "attack: " << targetMinion->getAttack() << "defense: " << targetMinion->getDefense();
                (*o)->applyAbility();   
            }
            ++o;
        }
        o = ol->observers.begin();
        while (o != ol->observers.end()) {
            if ((*o)->getType() == TriggerType::MinionLeave && (*o)->getOwner() != ol->activePlayer) { // TODO
                (*o)->setTargetMinion(targetMinion);
                (*o)->applyAbility();   
            }
            ++o;
        }
    } catch (not_enough_charge& e) {}
}


MinionPtr Board::getCard(int i) const {
    // if (i > theBoard.size()) {
    //     throw invalid_card_inspect();
    // } 
    // else if (i < theBoard.size()) {
    //     throw dne_card_inspect();
    // }
    return theBoard[i];
}

void Board::addCard(MinionPtr m) {
    if (theBoard.size() == 5) throw full_board{};
    theBoard.emplace_back(m);

    // attach board* to the minion
    m->setBoard(this);

    // notify observers
    notifyMinionEnterObservers(m);

    // attach trigger to observers
    auto a = m->getAbility();
    if (holds_alternative<TriggeredAbility*>(a)) attach(get<TriggeredAbility*>(a));

}

MinionPtr Board::removeCard(int i) {
    if (static_cast<int>(theBoard.size()) > i) {
        MinionPtr m = theBoard[i];
        notifyMinionLeaveObservers(m);

        // remove trigger from observers if minion has a triggerAbility
        auto a = m->getAbility();
        if (holds_alternative<TriggeredAbility*>(a)) detach(get<TriggeredAbility*>(a));

        // flatten fields, then remove enchantments
        int attack = theBoard[i]->getAttack();
        int defense = theBoard[i]->getDefense();
        int action = theBoard[i]->getAction();

        cout << "removing!! attack: " << attack << "defence " << defense << "action " << action << endl;

        this->stripEnchants(i);

        theBoard[i]->setAttack(attack);
        theBoard[i]->setDefense(defense);
        theBoard[i]->setAction(action); // implement in Minion

        cout << "the minion reassigned!! attack: " << theBoard[i]->getAttack() << "defence " << theBoard[i]->getDefense() << "action " << theBoard[i]->getAction()  << endl;

        // cout << "attack: " << theBoard[i]->getAttack() << endl;
        // cout << "defense: " << theBoard[i]->getDefense()<< endl;
        // cout << "action: " << theBoard[i]->getAction() << endl;

        // m->setBoard(nullptr);
        MinionPtr res = theBoard[i];

        theBoard.erase(theBoard.begin() + i);

        return res;
    } else {throw invalid_play{"Cannot access index " + to_string(i) + " in the board."}; } // should never happen
    
}

int Board::find(MinionPtr m) {
    for (size_t i = 0; i < theBoard.size(); i++) {
        // need to get default minion here before comparing - not just theBoard[i]
        Minion* dm = theBoard[i]->getDefaultMinion();
        if (m.get() == dm) {
            return i; 
        }
    }
    return -1;
}


MinionPtr Board::enchantMinion(int i, string minionName, int modifyval) {
    // EXCEPTION: check for i

    // // this vector will hold the updated MinionPtrs that point at the top layer (after adding enchantdecs)
    // vector<MinionPtr> res;

    MinionPtr res;
    
    if (minionName == "Giant Strength") theBoard[i] = make_shared<GiantStrength>(theBoard[i]); 
    else if (minionName == "Enrage") theBoard[i] = make_shared<Enrage>(theBoard[i]);
    else if (minionName == "Haste") theBoard[i] = make_shared <Haste>(theBoard[i]);
    else if (minionName == "Magic Fatigue") theBoard[i] = make_shared <MagicFatigue>(theBoard[i]);
    else if (minionName == "Silence") theBoard[i] = make_shared <Silence>(theBoard[i]);
    else if (minionName == "Modify Attack") theBoard[i] = make_shared <ModifyAttack>(theBoard[i], modifyval);
    else if (minionName == "Modify Defense") theBoard[i] = make_shared <ModifyDefense>(theBoard[i], modifyval);

    res = theBoard[i];

    // check if minions are dead (should only go off when modifying defense)
    if (minionName == "Modify Defense") {
        if (this->getCard(i)->isDead()) {
            // send to graveyard
            grave->push(this->removeCard(i));
        }
    } else {
        // attach trigger if applicable
        TriggeredAbility* a = dynamic_pointer_cast<EnchantmentDec>(theBoard[i])->getEnchantmentAbility();
        if (a)  attach(a);
    }

    return res;

}

void Board::stripEnchants(int i) {
    CardPtr noenchantMinionCard = createCard(theBoard[i]->getDefaultMinionName(), nullptr);
    MinionPtr noenchantMinion = dynamic_pointer_cast<Minion>(noenchantMinionCard);
    theBoard[i] = noenchantMinion;
    // cout << "noenchant defense: " << noenchantMinion->getDefense() << endl;
}

void Board::stripTopEnchant(int i) {
    MinionPtr m = theBoard[i];
    if (DefaultMinionPtr dm = dynamic_pointer_cast<DefaultMinion>(m)) {
        throw no_enchantments(m);
    } else { // m points at hidden or non-hidden enchantment decorator
        // careful that EnchantmentDecs also contain "hidden" Enchantments, which are not legit Enchantments - they will be flattened into the fields
        EnchantmentDecPtr curr = dynamic_pointer_cast<EnchantmentDec>(m);
        EnchantmentDecPtr prev = curr;
        EnchantmentDecPtr ednext; // will be set if applicable
        MinionPtr next = curr->getNext();
        while (curr->isHidden()) { // while curr is not a legit Enchantment
            if (ednext = dynamic_pointer_cast<EnchantmentDec>(next)) { // if we have not hit base case
                prev = curr;
                curr = ednext;
                next = ednext->getNext();
            } else { // hit the base case
                throw no_enchantments(m);
            }
        }
        cout << "prev: " << prev->getName() << endl;
        cout << "curr: " << curr->getName() << endl;
        curr->setNext(nullptr);
        
        // if curr has a trigged ability, remove the observer
        TriggeredAbility* ta = curr->getEnchantmentAbility();
        if (ta) {
            detach(ta);
        }

        cout << "next: " << next->getName() << endl;
        prev->setNext(next);
        // cout << theBoard[i] << endl;
    }
}

void Board::restoreAction() {
    for (auto minion : theBoard) {
        minion->setAction(1);
    }
}

void Board::destroyMinion(int i) {
    theBoard.erase(theBoard.begin() + i);
}

int Board::size() { return static_cast<int>(theBoard.size()); }

bool Board::contains(MinionPtr m) {
    return (this->find(m) >= 0);
    // for (int i = 0; i < theBoard.size(); i++) {
    //     // MinionPtr dm = theBoard[i]->getDefaultMinion();
    //     if (m == theBoard[i]) {
    //        // cout << "rar" << theBoard[i]->getName() << endl;
    //         return true;
    //     }
    // }
    // return false;
}

void Board::TEST_printBoard() {
    for (size_t i = 0; i < theBoard.size(); ++i) {
        // cout << "Board (" << (i+1) << "): " << theBoard[i];
        cout << "Board (" << (i+1) << "): " << theBoard[i] <<  " ["<< theBoard[i]->getAction() << " action | " << theBoard[i]->getAttack() << " attack | " << theBoard[i]->getDefense() << " defense]" << endl;
    }
}

int Board :: getBoardSize() {
    return theBoard.size();
}

stack<MinionPtr>& Graveyard::getGrave(){ return theGrave; }

Graveyard::Graveyard(){}
Graveyard::~Graveyard(){}
bool Graveyard::isEmpty() { return theGrave.empty(); }
MinionPtr Graveyard::getTop() { return theGrave.top(); }
void Graveyard::removeTop() { return theGrave.pop(); }
void Graveyard::push(MinionPtr m) { return theGrave.push(m); }

void Graveyard::TEST_printGrave() {
    stack<MinionPtr> temp = theGrave;
    int i = 1;
    while (!temp.empty()) {
        cout << "Grave (" << i << "): " << temp.top() << endl;
        temp.pop();
        ++i;
    }
}

