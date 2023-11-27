#include "minion.h"
#include <string>
using namespace std;

Minion::Minion(CardName cardName, int cost, string desc): 
    Card{cardName, cost, CardType::Minion, false, desc} {}

void Minion::decreaseLife(int n) {

}

// void Minion::setAction(int n) {
//     action = n;
// }

