#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__
#include <stdexcept>
#include "gamemaster.h"
using namespace std;

class not_enough_action : public std::exception {
    Player p;
    public:
        not_enough_action(Player& p) : p{p} {}
        string what () {
            return p.getName() + " has 0 action. Unable to attack.";
        }
};

class not_enough_magic : public std::exception {
    Player p;
    public:
        not_enough_magic(Player& p) : p{p} {}
        string what () {
            return p.getName() + " does not have enough magic. Play failed.";
        }
};

class not_enough_charge : public std::exception {
    Ritual* r;
    public:
        not_enough_charge(Ritual* r): r{r} {}
        string what() {
            return r->getName() + "does not have enough charge. Ritual not triggered.";
        }

};
class no_target_provided : public std::exception {
    Card c;
    public:
        no_target_provided(Card& c) : c{c} {}
        string what () {
            return c.getName() + " cannot be played without a target. Play failed.";
        }
};
class no_target_needed : public std::exception {
    Card c;
    public:
        no_target_needed(Card& c) : c{c} {}
        string what () {
            return c.getName() + " cannot be played with a target. Play failed.";
        }
};
class invalid_play : public std::exception {
    string msg;
    public:
        invalid_play(string msg) : msg{msg} {}
        string what () {
            return msg;
        }
};

class deck_empty : public std::exception {
    Player* p;
 public:
    deck_empty(Player* p): p {p} {}
    string what() {
        return p->getName() + "'s deck is empty. Unable to draw card.";
    }
};

class empty_grave : public std::exception {
    string msg;
    public:
        empty_grave() {}
        string what () {
            return "The graveyard is empty.";
        }
};

class full_hand : public std::exception {
    public:
        full_hand() {}
        string what() {
            return "The hand is full.";
        }
};

class full_board : public std::exception {
    public:
        full_board() {}
        string what() {
            return "The board is full.";
        }
};

class full_inspect : public std::exception {
    public:
        full_inspect() {}
        string what() {
            return "The inspect is full.";
        }
};

class outside_range : public std::exception {
    public:
        outside_range() {}
        string what () {
            return "Out of range.";
        }
};

class no_enchantments : public std::exception {
    MinionPtr m;
    public:
        no_enchantments(MinionPtr m) : m{m} {}
        string what () {
            return m->getName() + " has no enchanments.";
        }
};

class ability_silenced : public std::exception {
    public:
        ability_silenced() {}
        string what () {
            return "Cannot apply abilities. Minion has been enchanted with Silence.";
        }
};

// class detach_game_observer : public std::exception {
//     TriggeredAbility* ta;
//     public:
//         detach_game_observer(TriggeredAbility* ta ) : ta{ta} {}
//         string what () {
//             return "Removing a TriggeredAbility from gameObservers.";
//         }
// };

class invalid_inspect_type : public std::exception {
    MinionPtr m;
    public:
        invalid_inspect_type(MinionPtr _m) : m{_m} {}
        string what () {
            return "Unable to inspect: " + m->getName() + " is not a Minion.";
        }
};

class invalid_card_inspect : public std::exception {
    public:
        invalid_card_inspect() = default;
        string what () {
            return "Unable to inspect - card is not on the inspect.";
        }
};

class dne_card_inspect : public std::exception {
    public:
    dne_card_inspect() = default;
    string what() {
        return "Unable to inspect - card does not exist.";
    }
};

#endif
