#ifndef _LEVEL_0_H
#define _LEVEL_0_H
#include <string>
#include <fstream>
#include "level.h"
#include "block.h"

class Level_0 : public Level{
    std::string inputfile; // file with the block sequence
    std::vector<char> commandsVec; // create a vector of chars	
    int counter = 0; 
    public:
    Block * generateBlock(bool isRandom, std::string file) override;
    Level_0(std::string inputfile);
};

#endif





