#ifndef _LBLOCK_H
#define _LBLOCK_H
#include <vector>
#include <string>
#include "block.h"

class Coordinate;

class LBlock: public Block {
    // only difference between this and its parent class Block is that LBlock should draw and designate cells
    // based on LBlack's unique shape... so we must initialize the vector of cells based on LBlock's shape
    public: 
        char shape = 'L';
        LBlock(int levelCreatedIn, int howHeavy);
        void printLine1() override; //prints the top row of the LBlock
        void printLine2() override; // prints the bottom row of the LBlock
};

#endif



