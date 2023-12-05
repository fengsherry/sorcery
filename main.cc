// This program implements the "Sorcery" game

// #include <iostream>
// #include <string>
// #include <fstream>
#include "gamemaster.h"
#include "gamecontroller.h"
using namespace std;

int main(int argc, char *argv[]) {
    GameController controller;
    controller.go(argc, argv);
    
}
