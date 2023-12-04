// Public interface for Enchantment

#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include "card.h"
#include <string>
using namespace std;

class Enchantment: public Card {
    CardType type = CardType::Enchantment;
    bool needTarget = true;
    string attackModifier;
    string defenseModifier;

    public:
        // string getAttackModifier() const override;
        // string getDefenseModifier() const override;
        Enchantment(CardName cardName, int cost, string desc, string attackModifier = "", string defenseModifer = "");
        ~Enchantment();
};

typedef shared_ptr<Enchantment> EnchantmentPtr;

#endif
