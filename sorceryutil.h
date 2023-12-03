// This is the public interface for Sorcery Util, helpful tools to be used in the sorcery program
#ifndef __SORCERYUTIL_H__
#define __SORCERYUTIL_H__

#include <string>
#include "card.h"
#include "player.h"

string cardNameToString(CardName c);

CardPtr createCard(std::string cardName, Player* p);

#endif
