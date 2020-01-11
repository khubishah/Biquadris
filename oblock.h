#ifndef _OBLOCK_H
#define _OBLOCK_H
#include <vector>
#include <string>
#include "block.h"
class Coordinate;

class OBlock: public Block {
    // only difference between this and its parent class Block is that OBlock should draw and designate cells
    // based on OBlack's unique shape... so we must initialize the vector of cells based on OBlock's shape
    public:
        char shape = 'O';
        OBlock(int levelCreatedIn, int howHeavy);
        void printLine1() override; //printing the top half of the OBlock
        void printLine2() override; //printing the bottom half of the OBlock
};

#endif




