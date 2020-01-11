#ifndef _LEVEL_2_H
#define _LEVEL_2_H
#include <string>
#include <vector>
#include <fstream>
#include "level.h"
#include "block.h"

class Level_2 : public Level{
	 int score = 2;
	unsigned int seed;
	public:   
	Block * generateBlock(bool isRandom, std::string file) override;	
		Level_2(unsigned int seed);   
};

#endif





