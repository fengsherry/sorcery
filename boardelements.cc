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
    if (cardName == "Air Elemental") card = new DefaultMinion(CardName::AirElemental, 0, 1, 1, monostate{});
    else if (cardName == "Earth Elemental") card = new DefaultMinion(CardName::EarthElemental, 3, 4, 4, monostate{});
    // minions with abilities: REPLACE MONOSTATE WITH ACTUAL ABILITY OBJECT ONCE THEY'RE MADE
    else if (cardName == "Bone Golem") card = new DefaultMinion(CardName::BoneGolem, 2, 1, 3, new BoneGolemAbility{p, dynamic_cast<Minion*> (card)}, "Gain +1/+1 whenever a minion leaves play.");
    else if (cardName == "Fire Elemental") card = new DefaultMinion(CardName::FireElemental, 2, 2, 2, new FireElementalAbility{p, dynamic_cast<Minion*> (card)}, "Whenever an opponent's minion enters play, deal 1 damage to it.");
    else if (cardName == "Potion Seller") card = new DefaultMinion(CardName::PotionSeller, 2, 1, 3, new PotionSellerAbility{p, dynamic_cast<Minion*> (card)}, "At the end of your turn, all your minions gain +0/+1.");
    else if (cardName == "Novice Pyromancer") card = new DefaultMinion(CardName::NovicePyromancer, 1, 0, 1, monostate{}, "Deal 1 damage to target minion.");
    else if (cardName == "Apprentice Summoner") card = new DefaultMinion(CardName::ApprenticeSummoner, 1, 1, 1, monostate{}, "Summon a 1/1 air elemental.");
    else if (cardName == "Master Summoner") card = new DefaultMinion(CardName::MasterSummoner, 3, 2, 3, monostate{}, "Summon up to three 1/1 air elementals.");

    /* Enchantments: */
    else if (cardName == "Giant Strength") card = new Enchantment(CardName::GiantStrength, 1, "", "+2", "+2");
    else if (cardName == "Enrage") card = new Enchantment(CardName::Enrage, 2, "", "*2", "*2");
    else if (cardName == "Haste") card = new Enchantment(CardName::Haste, 1, "Enchanted minion gains +1 action each turn");
    else if (cardName == "Magic Fatigue") card = new Enchantment(CardName::MagicFatigue, 0, "Enchanted minion's activated ability costs 2 more");
    else if (cardName == "Silence") card = new Enchantment(CardName::Silence, 1, "Enchanted minion cannot use abilities");
    
    /* Spells: */ 
    else if (cardName == "Banish") card = new Spell(CardName::Banish, 2, true, "Destroy target minion or ritual", new BanishAbility{});
    else if (cardName == "Unsummon") card = new Spell(CardName::Unsummon, 1, true, "Return target minion to its owner's hand", new UnsummonAbility{});
    else if (cardName == "Disenchant") card = new Spell(CardName::Disenchant, 1, true, "Destroy the top enchantment on target minion", new DisenchantAbility{});
    else if (cardName == "Raise Dead") card = new Spell(CardName::RaiseDead, 1, false, "Ressurect the top minion in your graveyard and set its defense to 1", new RaiseDeadAbility{});
    else if (cardName == "Recharge") card = new Spell(CardName::Recharge, 1, false, "Your ritual gains 3 charges", new RechargeAbility{});
    else if (cardName == "Blizzard") card = new Spell(CardName::Blizzard, 1, false, "Deals 2 damage to all minions", new BlizzardAbility{});
    

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

        Card* newCard = createCard(cardName, p);

        // add to theDeck if it is a valid card (not nullptr)
        if (newCard) theDeck.emplace_back(newCard);
    }
}

void Deck::TEST_printDeck() {
    for (auto s : theDeck) { cout << s << endl; }
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
    if (theHand.size() == 5) throw full_hand{};
    theHand.emplace_back(c);
}

Card* Hand::getCard(int i) const {
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

void Board::removeCard(int i) {
    if (static_cast<int>(theBoard.size()) > i) {
        theBoard.erase(theBoard.begin() + i);
    } else {throw invalid_play{"Cannot access index " + to_string(i) + " in the board."}; } // should never happen
    
}

int Board::find(Minion* m) {
    for (int i = 0; i < theBoard.size(); i++) {
        // need to get default minion here before comparing - not just theBoard[i]
        if (m == theBoard[i]) return i;
    }
    return -1;
}

void Board::addCard(Minion *m) {
    if (theBoard.size() == 5) throw full_board{};
    theBoard.emplace_back(m);
    notifyMinionEnterObservers(m);
}

void Board::enchantMinion(int i, string minionName, int modifyval) { // use enum class instead of string??
    if (minionName == "Giant Strength") theBoard[i] = new GiantStrength(theBoard[i]); 
    else if (minionName == "Enrage") theBoard[i] = new Enrage(theBoard[i]);
    else if (minionName == "Haste") theBoard[i] = new Haste(theBoard[i]);
    else if (minionName == "Magic Fatigue") theBoard[i] = new MagicFatigue(theBoard[i]);
    else if (minionName == "Silence") theBoard[i] = new Silence(theBoard[i]);
    else if (minionName == "Modify Attack") theBoard[i] = new ModifyAttack(theBoard[i], modifyval);
    else if (minionName == "Modify Defense") theBoard[i] = new ModifyDefense(theBoard[i], modifyval);
    // need option another for Modify Ability 
}

void Board::stripEnchants(int i, Player& p) {
    Card* noenchantMinionCard = createCard(theBoard[i]->getDefaultMinionName(), nullptr);
    Minion* noenchantMinion = dynamic_cast<Minion*>(noenchantMinionCard);
    theBoard[i] = noenchantMinion;
}

void Board::stripTopEnchant(int i) {
    Minion* m = theBoard[i];
    if (DefaultMinion* dm = dynamic_cast<DefaultMinion*>(m)) {
        throw no_enchantments(m);
    } else { // m points at hidden or non-hidden enchantment decorator
        // careful that EnchantmentDecs also contain "hidden" Enchantments, which are not legit Enchantments in this context
        EnchantmentDec* curr = dynamic_cast<EnchantmentDec*>(m);
        EnchantmentDec* prev = curr;
        EnchantmentDec* ednext; // will be set if applicable
        Minion* next = curr->getNext();
        while (curr->isHidden()) { // while curr is not a legit Enchantment
            if (ednext = dynamic_cast<EnchantmentDec*>(next)) { // if we have not hit base case
                prev = curr;
                curr = ednext;
                next = ednext->getNext();
            } else { // hit the base case
                throw no_enchantments(m);
            }
        }
        // Minion* m = ed->getNext();
        cout << "prev: " << prev->getName() << endl;
        cout << "curr: " << curr->getName() << endl;
        curr->setNext(nullptr);
        
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

bool Board::contains(Minion* m) {
    return (this->find(m) >= 0);
}

void Board::TEST_printBoard() {
    for (size_t i = 0; i < theBoard.size(); ++i) {
        // cout << "Board (" << (i+1) << "): " << theBoard[i];
        cout << "Board (" << (i+1) << "): " << theBoard[i] <<  " ["<< theBoard[i]->getAction() << " action | " << theBoard[i]->getAttack() << " attack | " << theBoard[i]->getDefense() << " defense]" << endl;
    }
}

Graveyard::Graveyard(){}
Graveyard::~Graveyard(){}
bool Graveyard::isEmpty() { return theGrave.empty(); }
Minion* Graveyard::getTop() { return theGrave.top(); }
void Graveyard::removeTop() { return theGrave.pop(); }
void Graveyard::push(Minion* m) { return theGrave.push(m); }

void Graveyard::TEST_printGrave() {
    stack<Minion*> temp = theGrave;
    int i = 1;
    while (!temp.empty()) {
        cout << "Grave (" << i << "): " << temp.top() << endl;
        temp.pop();
        ++i;
    }
}

