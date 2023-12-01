#include "sorceryutil.h"

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
        case CardName::Banish:
            return "Banish";
        case CardName::Unsummon:
            return "Unsummon";
        case CardName::Recharge:
            return "Recharge";
        case CardName::Disenchant:
            return "Disenchant";
        case CardName::RaiseDead:
            return "Raise Dead";
        case CardName::Blizzard:
            return "Blizzard";
            
        /* Enchantments: */
        case CardName::GiantStrength:
            return "Giant Strength";
        case CardName::Enrage:
            return "Enrage";
        case CardName::Haste:
            return "Haste";
        case CardName::MagicFatigue:
            return "Magic Fatigue";
        case CardName::Silence:
            return "Silence";
        case CardName::ModifyAttack:
            return "Modify Attack";
        case CardName::ModifyDefense:
            return "Modify Defense";
        case CardName::ModifyAbility:
            return "Modify Ability";

        /* Rituals: */
        case CardName::DarkRitual:
            return "Dark Ritual";
        case CardName::AuraOfPower:
            return "Aura of Power";
        case CardName::Standstill:
            return "Standstill";
    }
}