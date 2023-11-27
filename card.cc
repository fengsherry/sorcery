#include "card.h"
#include <string>
#include <iostream>
using namespace std;

string cardNameToString(CardName c) {
    switch (c) {
        /* Minions: */
        case CardName::AirElemental:
            return "Air Elemental";
        case CardName::EarthElemental:
            return "Earth Elemental";
        case CardName::BoneGolem:
            return "Bone Golem";
        case CardName::FireElemental:
            return "Fire Elemental";
        case CardName::PotionSeller:
            return "Potion Seller";
        case CardName::NovicePyromancer:
            return "Novice Pyromancer";
        case CardName::ApprenticeSummoner:
            return "Apprentice Summoner";
        case CardName::MasterSummoner:
            return "Master Summoner";
        /* Enchantments: */
        case CardName::GiantStrength:
            return "Giant Strength";
        case CardName::Enrage:
            return "Enrage";
        case CardName::Haste:
            return "Haste";
        case CardName::MagicFatigue:
            return "MagicFatigue";
        case CardName::Silence:
            return "Silence";
    }
}

// Card::Card() {}

Card::Card(CardName cardName, int cost, CardType type, string desc): 
name{cardName}, cost{cost}, type{type}, desc{desc} {}

string Card::getName() const {return cardNameToString(name);}

CardType Card::getType() {return type;}

int Card::getCost() const {return cost;}

// TEMP
ostream &operator<< (ostream &out, const Card &c) {
    out << c.getName();
    return out;
}
// TEMP

// Card::~Card() {}




