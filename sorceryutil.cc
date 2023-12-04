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

string cardTypeToString(CardType t) {
    switch (t) {
        case CardType::Spell : return "Spell";
        case CardType::Minion : return "Minion";
        case CardType::Enchantment : return "Enchantment";
        case CardType::Ritual : return "Ritual";
    }
}

DefaultMinionPtr minionWithTriggerAbilityInit(CardName cn, int cost, int attack, int defense, TriggeredAbility* ta, string desc) {
    DefaultMinionPtr card = std::make_shared<DefaultMinion>(cn, cost, attack, defense, ta, desc);
    card->setTrigOwnerMinion(card);
    return card;
}

CardPtr createCard(string cardName, Player* p) {
    CardPtr card;
    /* Minions: */
    // minions no abilities
    if (cardName == "Air Elemental") card = std::make_shared<DefaultMinion>(CardName::AirElemental, 0, 1, 1, monostate{});
    else if (cardName == "Earth Elemental") card = std::make_shared<DefaultMinion>(CardName::EarthElemental, 3, 4, 4, monostate{});
    // minions with activated abilities: 
    else if (cardName == "Novice Pyromancer") card = std::make_shared<DefaultMinion>(CardName::NovicePyromancer, 1, 0, 1, new NovicePyromancerAbility{}, "Deal 1 damage to target minion.");
    else if (cardName == "Apprentice Summoner") card = std::make_shared<DefaultMinion>(CardName::ApprenticeSummoner, 1, 1, 1, new ApprenticeSummonerAbility{}, "Summon a 1/1 air elemental.");
    else if (cardName == "Master Summoner") card = std::make_shared<DefaultMinion>(CardName::MasterSummoner, 3, 2, 3, new MasterSummonerAbility{}, "Summon up to three 1/1 air elementals.");
    // minions with triggered abilities: 
    else if (cardName == "Bone Golem") card = minionWithTriggerAbilityInit(CardName::BoneGolem, 2, 1, 3, new BoneGolemAbility{p}, "Gain +1/+1 whenever a minion leaves play."); 
    else if (cardName == "Fire Elemental") card = minionWithTriggerAbilityInit(CardName::FireElemental, 2, 2, 2, new FireElementalAbility{p}, "Whenever an opponent's minion enters play, deal 1 damage to it."); 
    else if (cardName == "Potion Seller") card = minionWithTriggerAbilityInit(CardName::PotionSeller, 2, 1, 3, new PotionSellerAbility{p}, "At the end of your turn, all your minions gain +0/+1.");
    
    /* Enchantments: */
    else if (cardName == "Giant Strength") card = std::make_shared<Enchantment>(CardName::GiantStrength, 1, "", "+2", "+2");
    else if (cardName == "Enrage") card = std::make_shared<Enchantment>(CardName::Enrage, 2, "", "*2", "*2");
    else if (cardName == "Haste") card = std::make_shared<Enchantment>(CardName::Haste, 1, "Enchanted minion gains +1 action each turn");
    else if (cardName == "Magic Fatigue") card = std::make_shared<Enchantment>(CardName::MagicFatigue, 0, "Enchanted minion's activated ability costs 2 more");
    else if (cardName == "Silence") card = std::make_shared<Enchantment>(CardName::Silence, 1, "Enchanted minion cannot use abilities");
    
    /* Spells: */ 
    else if (cardName == "Banish") card = std::make_shared<Spell>(CardName::Banish, 2, true, "Destroy target minion or ritual", new BanishAbility{});
    else if (cardName == "Unsummon") card = std::make_shared<Spell>(CardName::Unsummon, 1, true, "Return target minion to its owner's hand", new UnsummonAbility{});
    else if (cardName == "Disenchant") card = std::make_shared<Spell>(CardName::Disenchant, 1, true, "Destroy the top enchantment on target minion", new DisenchantAbility{});
    else if (cardName == "Raise Dead") card = std::make_shared<Spell>(CardName::RaiseDead, 1, false, "Ressurect the top minion in your graveyard and set its defense to 1", new RaiseDeadAbility{});
    else if (cardName == "Recharge") card = std::make_shared<Spell>(CardName::Recharge, 1, false, "Your ritual gains 3 charges", new RechargeAbility{});
    else if (cardName == "Blizzard") card = std::make_shared<Spell>(CardName::Blizzard, 1, false, "Deals 2 damage to all minions", new BlizzardAbility{});
    

    /* Rituals: */ 
    else if (cardName == "Dark Ritual") card = std::make_shared<Ritual>(CardName::DarkRitual, "At the start of your turn, gain 1 magic", 0, 1, 5, new DarkRitualAbility{p});
    else if (cardName == "Aura of Power") card = std::make_shared<Ritual>(CardName::AuraOfPower, "Whenever a minion enters play under your control, it gains +1/+1", 1, 1, 4, new AuraOfPowerAbility{p});
    else if (cardName == "Standstill") card = std::make_shared<Ritual>(CardName::Standstill, "Whenever a minion enters play under your control, destroy it", 3, 2, 4, new StandstillAbility{p});

    else return nullptr;
    return card;
}
