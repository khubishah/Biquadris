#include "oblock.h"
#include "coordinate.h"
#include "cell.h"
#include <iostream>
using namespace std;

OBlock::OBlock(int levelCreatedIn, int howHeavy): Block{levelCreatedIn, howHeavy} {
    Coordinate init_coord{3,0};
    blockCells.emplace_back(Cell{'O', Coordinate{init_coord.row + 1, init_coord.col}});
    blockCells.emplace_back(Cell{'O', Coordinate{init_coord.row, init_coord.col + 1}});
    blockCells.emplace_back(Cell{'O', Coordinate{init_coord.row, init_coord.col}});
    blockCells.emplace_back(Cell{'O', Coordinate{init_coord.row + 1, init_coord.col + 1}});
}

void OBlock::printLine1() {
    int length = blockCells.size();    
    for (int i = 0; i < length/2; i++) {
        cout << blockCells[i].getShape();
    }
    cout << "         ";    
}

void OBlock::printLine2() {
    int length = blockCells.size();
    for (int i = 0; i < length/2; i++) {        
        cout << blockCells[i].getShape();
    }
    cout << "         ";    
}







