#ifndef _LEVEL_4_H
#define _LEVEL_4_H
#include <string>
#include <vector>
#include <fstream>
#include "level.h"
#include "block.h"

class Level_4 : public Level{
	int score = 4;
	int counter = 0;
	std::vector<char> commandsVec;
	unsigned int seed;
	public:    
	Block * generateBlock(bool isRandom, std::string file) override;	
		Level_4(unsigned int seed);   
};

#endif






