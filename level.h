#ifndef _LEVEL_H
#define _LEVEL_H
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

class Block; // forward declaration

// a level has level_0, level_1, level_2, level_3, level_4
    // level_0: takes its block in sequence from a file provided; once the file ends read from beginning again
    // level_1: S and Z block have a probability of 1/12 the rest have a probability of 1/6
    // level_2: all blocks have an equal probabilty (1/7)
    // level_3: S and Z have a probability of 2/9, and other blocks have a probability of 1/9
    //          blocks generated in level 3 are heavy
    // level_4: S and Z have a probability of 2/9, and other blocks have a probability of 1/9
    //          blocks generated in level 3 are heavy
    //          everytime you place 5 blocks without clearing a row,  a 1x1 block is dropped on the center coloumn

class Level {      
    public:
    virtual Block * generateBlock(bool isRandom, std::string file) = 0;
    virtual ~Level(); // destructor  
};

#endif






