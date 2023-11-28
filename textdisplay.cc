#include <iostream>
#include <string>
#include "textdisplay.h"
using namespace std;

// TextDisplay Constructor
TextDisplay::TextDisplay() {
  theHand.resize(10, std::vector<char>(100));
  for (size_t i = 0; i < theHand.size(); ++i) {
    theHand[i][0] = '┃';
    for (size_t j = 1; j < theHand[i].size(); ++j) {
      theHand[i][j] = '━';
    }
    theHand[i][theHand.size()] = '┃';
  }
}

TextDisplay::~TextDisplay() {}


void TextDisplay::displayMsg(string msg) {
    cout << msg << endl;
}

void TextDisplay::displaySorceryBoard() {}
void TextDisplay::displayHand() {}
void TextDisplay::displayMinion() {}

int nameLength(GameMaster &gm) {

}

void notify(GameMaster &gm) {
    
}

ostream &operator<<(std::ostream &out, const TextDisplay &td){
  for(auto row: td.theBoard) {
    for(auto c: row){
      out << c;
    }
    out << endl;
  }
  return out;
}