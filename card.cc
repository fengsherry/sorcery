#include "card.h"
#include <string>
#include <iostream>
using namespace std;

Card::Card(string cardName) : name{cardName} {}

string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}

// TEMP
ostream &operator<< (ostream &out, const Card &c) {
    out << c.getName();
    return out;
}
// TEMP




