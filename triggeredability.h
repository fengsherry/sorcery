// Public interface for TriggeredAbility (Observer + Command)

#ifndef _TRIGGEREDABILITY_H_
#define _TRIGGEREDABILITY_H_
#include <vector>
#include <memory>
using namespace std;

class Player;
class Minion;
typedef std::shared_ptr<Minion> MinionPtr;


enum class TriggerType { StartTurn, EndTurn, MinionEnter, MinionLeave };
enum class TriggerCardType {Minion, Ritual};

class TriggeredAbility {
 protected:
  TriggerType type;  
  TriggerCardType cardType;
  Player* owner; // some abilities need to know difference between owner and opponent
  MinionPtr ownerMinion; // only set if the ta belongs to a minion (not a ritual)
  vector<Player*> targetPlayers;
  vector<MinionPtr> targetMinions;
  Player* activePlayer;

 public:
  TriggeredAbility(TriggerType type, TriggerCardType cardType, Player* owner, MinionPtr ownerMinion = nullptr);
  virtual void applyAbility(); 
  Player* getOwner();
  Player* getActivePlayer();
  TriggerType getType();
  TriggerCardType getCardType();
  void setOwnerMinion(MinionPtr m);
  void setActivePlayer(Player* ap);
  virtual void setTargetPlayer(Player* targetPlayer);
  virtual void setTargetMinion(MinionPtr targetMinion);
  virtual void setTargetPlayers(vector<Player*> targetPlayers);
  virtual void setTargetMinions(vector<MinionPtr> targetMinions);
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
    BoneGolemAbility(Player* owner); 
    void applyAbility();
};

class FireElementalAbility : public TriggeredAbility {
  public:
    FireElementalAbility(Player* owner); 
    void applyAbility();
};

class PotionSellerAbility : public TriggeredAbility {
  public:
    PotionSellerAbility(Player* owner); 
    void applyAbility();
};

class HasteAbility : public TriggeredAbility {
  public:
    HasteAbility(MinionPtr ownerMinion); 
    void applyAbility();
};

#endif

