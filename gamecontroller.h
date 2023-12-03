#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include <stdexcept>
#include <vector>
#include "gamemaster.h"
#include "sorcerydisplay.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class GameController {
    GameMaster gm; 
    std::vector<SorceryDisplay*> displays;

    TextDisplay *td = nullptr;
    GraphicsDisplay *gd = nullptr;

    /* private helper functions */
    // helper function to find command line variables
    bool findIndex(int argc, char* argv[], string s, int& i);

    void testCmdArg(string arg, string filename = "n/a");

    public:
        GameController();
        ~GameController();
        
        void go(int argc, char *argv[]);
};


#endif
