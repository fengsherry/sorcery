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

class empty_grave : public std::exception {
    string msg;
    public:
        empty_grave() {}
        string what () {
            return "The graveyard is empty.";
        }
};

class outside_range : public std::exception {
    public:
        outside_range() {}
        string what () {
            return "Out of range.";
        }
};

#endif
