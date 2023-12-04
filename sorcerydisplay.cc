#include "sorcerydisplay.h"
#include <string>
using namespace std;

void SorceryDisplay::displayErrMsg(string msg, int p) {
    displayMsg("Error: " + msg, p);
}
