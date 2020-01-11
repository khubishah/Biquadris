#include <vector>
#include <cstdlib>
#include <iostream>
#include "level_1.h"
#include "iblock.h"
#include "jblock.h"
#include "zblock.h"
#include "lblock.h"
#include "sblock.h"
#include "oblock.h"
#include "tblock.h"
#include "coordinate.h"
using namespace std;

Level_1::Level_1(unsigned int seed): seed{seed}{
	srand(seed);
}
Block * Level_1::generateBlock(bool isRandom, std::string file){
	int dropLimit = 0;     
     Block * send;	
	int prob = rand() % 12 + 1; // generates number from 1 to 12	
     if(prob == 1) {
        send = new ZBlock{score,dropLimit};
    }
    else if (prob == 2) {
         send =  new SBlock{score,dropLimit};
    }
    else if (prob == 3 || prob == 4) {
         send = new IBlock{score,dropLimit};
    }
    else if (prob == 5 || prob == 6) {
         send = new JBlock{score,dropLimit};
    }
    else if (prob == 7 || prob == 8) {
         send = new LBlock{score,dropLimit};
    }
    else if (prob == 9 || prob == 10) {
         send = new OBlock{score,dropLimit};
    }
    else {
         send = new TBlock{score,dropLimit};
    }    
    return send;
}







