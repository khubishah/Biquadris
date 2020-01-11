#ifndef _PLAYER_H
#define _PLAYER_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "block.h"
#include "cell.h"
#include "iblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "jblock.h"
#include "lblock.h"
#include "starblock.h"
#include "level.h"
#include "level_0.h"
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include "level_4.h"
#include "window.h"
#include "board.h"

class Player {
    Level *level = nullptr; //Player HAS-A Level
    int score;
    int roundsWithoutClearing;
    int levelNum;
    unsigned int seed;

    public:
    std::string inputFile;
    Block * currBlock = nullptr;
    Block * nextBlock = nullptr;
    Board board; //Player HAS_A Board (public FOR NOW)
    bool isEffectHeavy = false;
    bool isEffectBlind = false;
    bool isEffectEarned = false;
    bool isRandom = true;
    //Ctor:
    // player doesn't have to specify inputFile (default file given)
    // player doesn't have to specify level (default level given)
    // player doesn't have to specify seed (default seed should be given)
    Player(int levelNum = 0, unsigned int seed = 592, std::string inputFile = ""); 
    ~Player(); //dtor
    void init(Xwindow * w = nullptr, int playerIndex = 0);
    int getScore();
    void setScore(int n);
    Level * initLevel();
    int getLevelNum();
    void tprint(int i);
    void gprint(Xwindow * w, int width, int height);    
    void takeTurn(std::string whichCommand, int multiplier, bool &failAdd); //what happens during a player's turn 
    void update(bool & failAdd);   
};



#endif



