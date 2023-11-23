// This is the public interface for a card.

#ifndef __CARD_H__
#define __CARD_H__
#include <string>
using namespace std;

enum class CardType { Spell, Minion, Enchantment, Ritual };

// contains only minions for now
enum class CardName { 
    AirElemental, EarthElemental, BoneGolem, FireElemental, PotionSeller, NovicePyromancer, ApprenticeSummoner, MasterSummoner
};
string cardNameToString(CardName c);

// every card has a name and a cost
class Card {   
    CardName name;
    int cost;
    CardType type;
    string desc;

 public:
    // Card();
    Card(CardName cardName, int cost, CardType type, string desc = "");
    virtual ~Card() = default;
    string getName() const;
    int getCost() const;
    CardType getType();

};

ostream &operator<< (ostream &out, const Card &c);

#endif
