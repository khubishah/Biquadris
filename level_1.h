#ifndef _LEVEL_1_H
#define _LEVEL_1_H
#include <string>
#include <vector>
#include <fstream>
#include "level.h"
#include "block.h"

class Level_1 : public Level{
	int score = 1;
	int counter = 0;
	unsigned int seed;
	public:  	
	Block * generateBlock(bool isRandom, std::string file) override;
		Level_1(unsigned int seed);   
};

#endif









