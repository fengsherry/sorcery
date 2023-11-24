#include "minion.h"
#include <string>
using namespace std;

Minion::Minion(CardName cardName, int cost, string desc): 
    Card{cardName, cost, type, desc} {}

void Minion::decreaseLife(int n) {

}

