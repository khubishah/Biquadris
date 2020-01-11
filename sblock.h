#ifndef _SBLOCK_H
#define _SBLOCK_H
#include <vector>
#include <string>
#include "block.h"
class Coordinate;

class SBlock: public Block {
    // only difference between this and its parent class Block is that SBlock should draw and designate cells
    // based on SBlack's unique shape... so we must initialize the vector of cells based on SBlock's shape
    public:
        char shape = 'S';
        SBlock(int levelCreatedIn, int howHeavy);
        void printLine1() override; // prints the top row of the SBlock
        void printLine2() override; // prints the bottom row of the SBlock
};

#endif



