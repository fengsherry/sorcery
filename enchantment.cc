#include "enchantment.h"
#include <string>
using namespace std;

Enchantment::Enchantment(CardName cardName, int cost, string desc, string attackModifier, string defenseModifer) : 
    Card{cardName, cost, CardType::Enchantment, needTarget, desc}, attackModifier{attackModifier}, defenseModifer{defenseModifer} { }

Enchantment::~Enchantment(){}

