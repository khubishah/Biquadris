#ifndef _IBLOCK_H
#define _IBLOCK_H
#include <vector>
#include <string>
#include "block.h"

class IBlock: public Block {
    // only difference between this and its parent class Block is that IBlock should draw and designate cells
    // based on IBlack's unique shape... so we must initialize the vector of cells based on IBlock's shape
    public: 
        char shape = 'I';
        IBlock(int levelCreatedIn, int howHeavy);
        void printLine1() override; // prints the top row of the IBlock
        void printLine2() override; // prints the bottom row of the IBlock
};

#endif






