// This is the public interface for a card.

#ifndef __CARD_H__
#define __CARD_H__
#include <string>
#include <memory>
using namespace std;

enum class CardType { Spell, Minion, Enchantment, Ritual };

// contains only minions for now
enum class CardName { 
    /* Minions: */ AirElemental, EarthElemental, BoneGolem, FireElemental, PotionSeller, NovicePyromancer, ApprenticeSummoner, MasterSummoner,
    /* Enchantments (non-hidden): */ GiantStrength, Enrage, Haste, MagicFatigue, Silence,
    /* Enchantments (hidden:) */ ModifyAttack, ModifyDefense, ModifyAbility,
    /* Spells */ Banish, Unsummon, Recharge, Disenchant, RaiseDead, Blizzard,
    /* Rituals */ DarkRitual 
};
string cardNameToString(CardName c);

// every card has a name and a cost
class Card {   
    CardName name;
    int cost;
    CardType type;
    string desc;
    bool needTarget; // true if the Card requires a target to be played

 public:
    // Card();
    Card(CardName cardName, int cost, CardType type, bool needTarget, string desc = "");
    virtual ~Card() = default;
    virtual string getName() const;
    // virtual string getAttackModifier() const;
    // virtual string getDefenseModifier() const;
    string getDesc() const;
    int getCost() const;
    CardType getType();
    CardName getCardName();
    bool getNeedTarget();

};
typedef std::shared_ptr<Card> CardPtr;

ostream &operator<< (ostream &out, const Card *c);

#endif
