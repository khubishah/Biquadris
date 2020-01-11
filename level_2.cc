#include <vector>
#include <cstdlib>
#include <iostream>
#include "level_2.h"
#include "iblock.h"
#include "jblock.h"
#include "zblock.h"
#include "lblock.h"
#include "sblock.h"
#include "oblock.h"
#include "tblock.h"

using namespace std;

Level_2::Level_2(unsigned int seed): seed{seed}{
	srand(seed);
}
Block * Level_2::generateBlock(bool isRandom, std::string file){
	int dropLimit = 0;
     Block * send;	
	int prob = rand() % 7 + 1; // generates number from 1 to 7
     if(prob == 1) {
        send = new ZBlock{score,dropLimit};
    }
    else if (prob == 2) {
         send = new SBlock{score,dropLimit};
    }
    else if (prob == 3) {
         send = new IBlock{score,dropLimit};
    }
    else if (prob == 4) {
         send = new JBlock{score,dropLimit};
    }
    else if (prob == 5) {
         send = new LBlock{score,dropLimit};
    }
    else if (prob == 6) {
         send = new OBlock{score,dropLimit};
    }
    else {
         send = new TBlock{score,dropLimit};
    }
    return send;
}






