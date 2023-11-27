#include "spell.h"
using namespace std;

Spell::Spell(CardName cardName, int cost, bool needTarget, string desc, ActivatedAbility* aa, Player* target):
    Card {cardName, cost, CardType::Spell, needTarget, desc}, aa {aa}, needTarget {needTarget} {}

bool Spell::getNeedTarget() {return needTarget;}

void Spell::applyAbility(Player& player) {
    aa->applyAbility(player);
}
