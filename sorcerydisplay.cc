#include "sorcerydisplay.h"
#include <string>
using namespace std;

void SorceryDisplay::displayErrMsg(string msg, int p) {
    displayMsg(vector<string>{"Error: " + msg}, p);
}
