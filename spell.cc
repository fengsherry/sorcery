#include "spell.h"
using namespace std;

Spell::Spell(CardName cardName, int cost, bool needTarget, string desc, ActivatedAbility* aa, Player* target):
    Card {cardName, cost, CardType::Spell, needTarget, desc}, aa {aa} {}


void Spell::applyAbility(Player& player1, Player& player2) {
    aa->applyAbility(player1, player2);
}

void Spell::applyAbility(Player& player1, Player& player2, int i) {
    aa->applyAbility(player1, player2, i);
}
