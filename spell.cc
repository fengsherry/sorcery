#include "spell.h"
using namespace std;

Spell::Spell(CardName cardName, int cost, string desc, ActivatedAbility* aa, bool needTarget):
    Card {cardName, cost, CardType::Spell, desc}, aa {aa}, needTarget {needTarget} {}

bool Spell::getNeedTarget() {return needTarget;}

Spell::applyAbility(Player& player) {
    aa->applyAbility(player);
}