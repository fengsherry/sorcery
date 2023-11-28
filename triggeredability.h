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
  vector<Player*> targetPlayers;
  vector<Minion*> targetMinions;

 public:
  TriggeredAbility(TriggerType type, vector<Player*> targetPlayers, vector<Minion*> targetMinions);
  virtual void applyAbility(Player* activePlayer) = 0; 
  virtual TriggerType getType();
  virtual ~TriggeredAbility() = default;
};

class DarkRitualAbility : public TriggeredAbility {
 public:
    DarkRitualAbility(Player* targetPlayer);
    //void addTarget(Player* targetPlayer);
    void applyAbility(Player* activePlayer);
};
#endif