#include "enchantment.h"
#include <string>
using namespace std;

Enchantment::Enchantment(CardName cardName, int cost, string desc, string attackModifier, string defenseModifer) : 
    Card{cardName, cost, CardType::Enchantment, true, desc}, attackModifier{attackModifier}, defenseModifier{defenseModifer} { }

Enchantment::~Enchantment(){}

// string Enchantment::getAttackModifier() const { return attackModifier; };

// string Enchantment::getDefenseModifier() const { return defenseModifier; };

