#include "minion.h"
#include "defaultminion.h"
#include "enchantmentdec.h"
#include <string>
using namespace std;

Minion::Minion(CardName cardName, int cost, string desc): 
    Card{cardName, cost, CardType::Minion, false, desc} {}

// void Minion::decreaseLife(int n) {

// }

// string Minion::getName() const { return getDefaultMinionName(); }

// void Minion::decreaseDefense(int n) {}
// void Minion::setAction(int n) {
//     action = n;
// }

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

std::ostream& operator<<(std::ostream& out, const Minion* m) {
    if (const DefaultMinion* dm = dynamic_cast<const DefaultMinion*>(m)) {
        out << dm->getDefaultMinionName();
    } else if (const EnchantmentDec* ed = dynamic_cast<const EnchantmentDec*>(m)) {
        out << ed->getDefaultMinionName();
    }
    
    return out;
}

