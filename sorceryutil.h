// This is the public interface for Sorcery Util, helpful tools to be used in the sorcery program
#ifndef __SORCERYUTIL_H__
#define __SORCERYUTIL_H__

#include <string>
#include "card.h"
#include "player.h"
#include "exceptions.h"

string cardNameToString(CardName c);

string cardTypeToString(CardType t);

CardPtr createCard(std::string cardName, Player* p);

void checkRange(int i, int max);

#endif
