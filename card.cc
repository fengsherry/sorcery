#include "card.h"
#include "sorceryutil.h"
#include <string>
#include <iostream>
using namespace std;

// string cardNameToString(CardName c) {
//     switch (c) {
//         /* Minions: */
//         case CardName::AirElemental:
//             return "Air Elemental";
//         case CardName::EarthElemental:
//             return "Earth Elemental";
//         case CardName::BoneGolem:
//             return "Bone Golem";
//         case CardName::FireElemental:
//             return "Fire Elemental";
//         case CardName::PotionSeller:
//             return "Potion Seller";
//         case CardName::NovicePyromancer:
//             return "Novice Pyromancer";
//         case CardName::ApprenticeSummoner:
//             return "Apprentice Summoner";
//         case CardName::MasterSummoner:
//             return "Master Summoner";
//         case CardName::Banish:
//             return "Banish";
//         case CardName::Unsummon:
//             return "Unsummon";
//         case CardName::Recharge:
//             return "Recharge";
//         case CardName::Disenchant:
//             return "Disenchant";
//         case CardName::RaiseDead:
//             return "Raise Dead";
//         case CardName::Blizzard:
//             return "Blizzard";
            
//         /* Enchantments: */
//         case CardName::GiantStrength:
//             return "Giant Strength";
//         case CardName::Enrage:
//             return "Enrage";
//         case CardName::Haste:
//             return "Haste";
//         case CardName::MagicFatigue:
//             return "Magic Fatigue";
//         case CardName::Silence:
//             return "Silence";
//         case CardName::ModifyAttack:
//             return "Modify Attack";
//         case CardName::ModifyDefense:
//             return "Modify Defense";
//         case CardName::ModifyAbility:
//             return "Modify Ability";

//         /* Rituals: */
//         case CardName::DarkRitual:
//             return "Dark Ritual";
//     }
// }

// Card::Card() {}

Card::Card(CardName cardName, int cost, CardType type, bool needTarget, string desc): 
name{cardName}, cost{cost}, type{type}, needTarget{needTarget}, desc{desc} {}

string Card::getName() const {
    return cardNameToString(getCardName());
}
string Card::getDesc() const {return desc;}

CardType Card::getType() {return type;}

CardName Card::getCardName() const {return name;}

bool Card::getNeedTarget() {return needTarget;}

int Card::getCost() const {return cost;}

// TEMP
// ostream &operator<< (ostream &out, const Card *c) {
//     out << c->getName();
//     return out;
// }
// TEMP

// Card::~Card() {}




