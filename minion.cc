#include "minion.h"
#include "defaultminion.h"
#include "enchantmentdec.h"
#include "boardelements.h"
#include <string>
using namespace std;

Minion::Minion(CardName cardName, int cost, string desc): 
    Card{cardName, cost, CardType::Minion, false, desc}, desc{desc} {}

// void Minion::decreaseLife(int n) {

// }

string Minion::getName() const { return Card::getName(); }

string Minion::getDesc() const { return desc; }

// void Minion::decreaseDefense(int n) {}
// void Minion::setAction(int n) {
//     action = n;
// }

void NoDeleter::operator()(Minion*) const {}

void Minion::destroy() {
    int i = board->find(MinionPtr(this, NoDeleter{})); 
    board->destroyMinion(i);
}

void Minion::modifyDefence(int n) {
    int i = board->find(MinionPtr(this, NoDeleter{}));
    board->enchantMinion(i, "Modify Defense", n);
}

void Minion::modifyAttack(int n) {
    int i = board->find(MinionPtr(this, NoDeleter{}));
    board->enchantMinion(i, "Modify Attack", n);
}

void Minion::setBoard(Board* b) {board = b;}

bool Minion::isDead() {
    return getDefense() <= 0;
}

void Minion::TEST_printInspectMinion() {
    if (DefaultMinion* dm = dynamic_cast<DefaultMinion*>(this)) {
        cout << dm->getName() << endl;
    } else {
        EnchantmentDec* ed = dynamic_cast<EnchantmentDec*>(this);
        cout << ed->getName() << " -> ";
        ed->getNext()->TEST_printInspectMinion();
    }
}

std::ostream& operator<<(std::ostream& out, const MinionPtr m) {
    if (const auto dm = dynamic_pointer_cast<const DefaultMinion>(m)) {
        out << dm->getDefaultMinionName();
    } else if (const auto ed = dynamic_pointer_cast<const EnchantmentDec>(m)) {
        out << ed->getDefaultMinionName();
    }
    
    return out;
}
