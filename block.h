#ifndef _BLOCK_H
#define _BLOCK_H
#include <vector>
#include <array>
#include <string>
#include "cell.h"
#include "observer.h"
#include "subject.h"
#include "coordinate.h"
#include "info.h"

class Block: public Observer<Info> {
    // this int to be used when giving scores when the block is cleared from a board
    int levelCreatedIn;
    int howHeavy;

    public:        
        
        // the cells of the block on the board (pointers to the cell* on the grid)
        std::vector<Cell> blockCells;
        // initialized differently for every block depending on its shape inside child classes for block
        char shape;
        int getHeavy();
        int getLevelCreatedIn();
        void setLevelCreatedIn(int n);
        void setHeavy(int n);
        Block(int levelCreatedIn, int howHeavy);
        // copy constructor for the block
        //Block(const Block & otgher);
        virtual ~Block();
        void notify(Subject<Info> &whoFrom) override;
        int getPoints();
        // returns an array of coordinates for the cells that comprise block
        std::vector<Coordinate> getBlockCellsCoords();
        //void updateCoordsVec(std::vector <Coordinate> updatedBlockCellCoords);
        bool isBlockCleared();
        virtual void printLine1() = 0;
        virtual void printLine2() = 0;
        //friend std::ostream &operator<<(std::ostream &out, const Block &b);

};

#endif












