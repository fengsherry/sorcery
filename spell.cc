#include "spell.h"
using namespace std;

Spell::Spell(CardName cardName, int cost, CardType type, string desc, ActivatedAbility* aa):
    Card {cardName, cost, type, desc}, aa {aa} {}
