#ifndef _ZBLOCK_H
#define _ZBLOCK_H
#include <vector>
#include <string>
#include "block.h"
class Coordinate;

class ZBlock: public Block {
    // only difference between this and its parent class Block is that ZBlock should draw and designate cells
    // based on ZBlack's unique shape... so we must initialize the vector of cells based on ZBlock's shape
    public:
        char shape = 'Z';
        ZBlock(int levelCreatedIn, int howHeavy);
        void printLine1() override; //prints the top row of the ZBlock
        void printLine2() override;  // pritns the bottom row of the Zblock    

};

#endif



