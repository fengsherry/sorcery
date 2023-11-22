#include <iostream>
#include <string>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay() {}
TextDisplay::~TextDisplay() {}


void TextDisplay::displayMsg(string msg) {
    cout << msg << endl;
}
void TextDisplay::displaySorceryBoard() {}
void TextDisplay::displayHand() {}
void TextDisplay::displayMinion() {}