#ifndef _JBLOCK_H
#define _JBLOCK_H
#include <vector>
#include <string>
#include "block.h"

class Coordinate;

class JBlock: public Block {
    // only difference between this and its parent class Block is that JBlock should draw and designate cells
    // based on JBlack's unique shape... so we must initialize the vector of cells based on JBlock's shape
    public: 
        char shape = 'J';
        JBlock(int levelCreatedIn, int howHeavy);
        void printLine1() override; //prints the top row of the JBlock
        void printLine2() override; // prints the bottom row of the JBlock

};

#endif





