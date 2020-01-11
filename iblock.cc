#include "iblock.h"
#include "cell.h"
#include "coordinate.h"
using namespace std;

IBlock::IBlock(int levelCreatedIn, int howHeavy): Block{levelCreatedIn, howHeavy} {    
    Coordinate init_coord{3,0};     
    blockCells.emplace_back(Cell{'I', Coordinate{init_coord.row, init_coord.col}});
    blockCells.emplace_back(Cell{'I', Coordinate{init_coord.row, init_coord.col + 1}});
    blockCells.emplace_back(Cell{'I', Coordinate{init_coord.row, init_coord.col + 2}});
    blockCells.emplace_back(Cell{'I', Coordinate{init_coord.row, init_coord.col + 3}});    
}

void IBlock::printLine1() {
    int length = blockCells.size();
    for (int i = 0; i < length; i++) {
        cout << blockCells[i].getShape();
    }
    cout << "       ";    
}

void IBlock::printLine2() {
    cout << "           ";
} //do nothing







