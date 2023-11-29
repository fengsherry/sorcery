#include "minion.h"
#include "defaultminion.h"
#include "enchantmentdec.h"
#include <string>
using namespace std;

Minion::Minion(CardName cardName, int cost, string desc): 
    Card{cardName, cost, CardType::Minion, false, desc} {}

void Minion::decreaseLife(int n) {

}

// string Minion::getName() const { return getDefaultMinionName(); }

// void Minion::setAction(int n) {
//     action = n;
// }

std::ostream& operator<<(std::ostream& out, const Minion* m) {
    if (const DefaultMinion* dm = dynamic_cast<const DefaultMinion*>(m)) {
        out << dm->getDefaultMinionName();
    } else if (const EnchantmentDec* ed = dynamic_cast<const EnchantmentDec*>(m)) {
        out << ed->getDefaultMinionName();
    }
    
    return out;
}

