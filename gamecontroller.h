#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include "gamemaster.h"

class GameController {
    GameMaster gm; 
    // TextDisplay td;
    // GraphicsDisplay gd;

    // private helper functions here

    public:
        GameController();
        ~GameController();
        
        void go();
};


#endif
