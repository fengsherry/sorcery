#include "minion.h"
#include <string>
using namespace std;

Minion::Minion(CardName cardName, int cost, string desc): 
    Card{cardName, cost, CardType::Minion, needTarget, desc} {}

void Minion::decreaseLife(int n) {

}

