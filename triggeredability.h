// Public interface for TriggeredAbility (Observer + Command)

#ifndef _TRIGGEREDABILITY_H_
#define _TRIGGEREDABILITY_H_
#include <vector>
using namespace std;

class Player;
class Minion;

enum class TriggerType { StartTurn, EndTurn, MinionEnter, MinionLeave };

class TriggeredAbility {
 protected:
  TriggerType type;  
  Player* p1;
  Player* p2;
  Player* owner; // some abilities need to know difference between owner and opponent
  Minion* ownerMinion; // only set if the ta belongs to a minion (not a ritual)
  vector<Player*> targetPlayers;
  vector<Minion*> targetMinions;

 public:
  TriggeredAbility(TriggerType type, Player* owner, Minion* ownerMinion = nullptr);
  virtual void applyAbility() = 0; 
  virtual TriggerType getType();
  virtual void setTargetPlayer(Player* targetPlayer);
  virtual void setTargetMinion(Minion* targetMinion);
  virtual void setTargetPlayers(vector<Player*> targetPlayers);
  virtual void setTargetMinions(vector<Minion*> targetMinions);
  virtual ~TriggeredAbility() = default;
};


class DarkRitualAbility : public TriggeredAbility {
 public:
    DarkRitualAbility(Player* owner);
    void applyAbility();
};


class AuraOfPowerAbility : public TriggeredAbility {
  public:
    AuraOfPowerAbility(Player* owner);
    void applyAbility();
};


class StandstillAbility : public TriggeredAbility {
  public:
    StandstillAbility(Player* owner); 
    void applyAbility();
};

class BoneGolemAbility : public TriggeredAbility {
  public:
    BoneGolemAbility(Player* owner, Minion* ownerMinion); 
    void applyAbility();
};

class FireElementalAbility : public TriggeredAbility {
  public:
    FireElementalAbility(Player* owner, Minion* ownerMinion); 
    void applyAbility();
};

class PotionSellerAbility : public TriggeredAbility {
  public:
    PotionSellerAbility(Player* owner, Minion* ownerMinion); 
    void applyAbility();
};

#endif

