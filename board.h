#ifndef _BOARD_H
#define _BOARD_H
#include <vector>
#include <utility>
#include <iostream>
#include "cell.h"
#include "coordinate.h"
#include "info.h"
#include "textdisplay.h"
#include "graphics.h"
#include "block.h"
#include "observer.h"
#include "window.h"
class Board {
    int numCols = 11; // width
    int numRows = 18; // height
    GraphicsDisplay *gd= nullptr;
    std::vector<Block*> boardBlocks;
    std::vector<std::vector<Cell>> vecOfCells; // cells of the entire board 
    public:
    
    TextDisplay *td = nullptr;
    bool isEffectBlind = false;
      
        ~Board();
        // initializes the board
        void init(Xwindow * w = nullptr, int playerIndex = 0);
        // clears a given cell on the board
        void clearCell(Coordinate coordinate);
        // adds a given block to the board... throw excpetion if new block cannot fit in the top left corner of the board
        bool addBlock(Block * block);
        void removeBlock(Block * block);
        // based on the coords given, it drops the block with those cell coords as low as it can go on the board
        void translateBlock(std::string translateType, int multiplier, Block * block);
        void rotateBlock(std::string rotateType, int multiplier, Block * block);
        bool attemptCellsTranslation(std::string translateType, Block *block);
        bool attemptCellsRotation(std::string rotateType, Block *block);
        void dropBlock(Block *block);
        void dropForHeaviness(Block * b);
        void resetBlind();
        // updateBoard checks if any row is full, and then calls shiftCellsDown which shifts each row above the cleared  row
        // scores: cleared rows and cleared blocks
        // for each cell of the row that's being deleted, we call notifyObservers on that cell
        std::pair<int, int> updateBoard();
        void shiftCellsDown(int row);

        // takes every cell at the old coordinate addresses and places them at the new coordinate addresses
        void moveBlockCells(Block * block, std::vector <Coordinate> newCoords);
        
        // check if a cell ptr at a given coordinate points to nullptr
        bool isCellEmpty(Coordinate coordinate);
        // check if the 3rd row from the top has an occupied block cell in it (1 of the losing cases)
        bool didYouLose(Block * b);
        void tprint(int i);       
        bool isValidMove(std::vector <Coordinate> coords);    
};


#endif



