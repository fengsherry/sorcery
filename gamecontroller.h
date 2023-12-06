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

    // TextDisplay *td = nullptr;
    // GraphicsDisplay *gd = nullptr;

    /* private helper functions */
    // helper function to find command line variables
    bool findIndex(int argc, char* argv[], string s, int& i);

    void testCmdArg(string arg, string filename = "n/a");

    void notifyDisplays(); // board
    void notifyGraphicDisplays();
    void notifyDisplays(MinionPtr m); // describe minion
    void notifyDisplays(int p); // hand
    void notifyDisplays(string msg, int p); // message
    void notifyDisplays(vector<string> msg, int p); // mutiple messages
    void notifyDisplaysErr(string err, int p);

    public:
        GameController();
        ~GameController();
        
        void go(int argc, char *argv[]);
};

#endif
