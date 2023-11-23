#include "minion.h"
#include <string>
using namespace std;

Minion::Minion(CardName cardName, int cost, CardType type, string desc): 
    Card{cardName, cost, type, desc} {}