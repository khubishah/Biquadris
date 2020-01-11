#ifndef _LEVEL_3_H
#define _LEVEL_3_H
#include <string>
#include <vector>
#include <fstream>
#include "level.h"
#include "block.h"

class Level_3 : public Level{
	 int score = 3;
	 int counter = 0;
	 std::vector<char> commandsVec;
	unsigned int seed;
	public:   
	Block * generateBlock(bool isRandom, std::string file) override;	
		Level_3(unsigned int seed);   
};

#endif





