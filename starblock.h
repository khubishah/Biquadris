#ifndef _STARBLOCK_H
#define _STARBLOCK_H
#include <vector>
#include <string>
#include "block.h"
class Coordinate;

class StarBlock: public Block {
    // only difference between this and its parent class Block is that StarBlock should draw and designate cells
    // based on StarBlock's unique shape... so we must initialize the vector of cells based on StarBlock's shape
    public: 
        char shape = '*';
        StarBlock(int levelCreatedIn, int howHeavy);
        void printLine1() override;
         void printLine2() override;
        
};

#endif



