// Public interface for Enchantment

#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include "card.h"
#include <string>
using namespace std;

class Enchantment: public Card {
    CardType type = CardType::Enchantment;
    string attackModifier;
    string defenseModifer;

    public:
        Enchantment(CardName cardName, int cost, string desc, string attackModifier = "", string defenseModifer = "");
        ~Enchantment();
};

#endif