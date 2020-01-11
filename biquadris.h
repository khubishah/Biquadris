#ifndef _BIQUADRIS_H
#define _BIQUADRIS_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "player.h"
#include "block.h"
#include "window.h"

class Biquadris {
    int highScore = 0;
    unsigned int seed = 592;
    int level = 0;
    std::vector<Player> vecOfPlayers;
    bool graphics = true;

    public:
        Xwindow *w = nullptr; // the window the game will be played on
        Biquadris(unsigned int seed, int level, bool graphics);        
        void initGame(bool graphics, int level, unsigned int seed); //intializes the game
        void addPlayer(int level, unsigned int seed, std::string inputFile = ""); //set default to ""
        void startPlaying();
        void restart(); //restart the game for ALL players
        int matchCommands(std::string & input); // matches the commands to the command provided by the player
        void print(); //to print the board
        // text display print
        void tprint();
        // graphics print
        void gprint();       
};

#endif


