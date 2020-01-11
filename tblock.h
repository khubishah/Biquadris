#ifndef _TBLOCK_H
#define _TBLOCK_H
#include <vector>
#include <string>
#include "block.h"

class Coordinate;
class TBlock: public Block{
    // only difference between this and its parent class Block is that TBlock should draw and designate cells
    // based on TBlack's unique shape... so we must initialize the vector of cells based on TBlock's shape
    public:
        char shape = 'T';
        TBlock(int levelCreatedIn, int howHeavy);
        void printLine1() override; //prints the top row of the TBlock
         void printLine2() override; //prints the bottom row of the TBlock
        

};

#endif



