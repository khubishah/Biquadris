#include "jblock.h"
#include "cell.h"
#include "coordinate.h"
using namespace std;

JBlock::JBlock(int levelCreatedIn, int howHeavy): Block{levelCreatedIn, howHeavy} {    
    Coordinate init_coord{3,0};   
    blockCells.emplace_back(Cell{'J', Coordinate{init_coord.row, init_coord.col}});
    blockCells.emplace_back(Cell{'J', Coordinate{init_coord.row + 1, init_coord.col }});
    blockCells.emplace_back(Cell{'J', Coordinate{init_coord.row + 1, init_coord.col + 1}});
    blockCells.emplace_back(Cell{'J', Coordinate{init_coord.row + 1, init_coord.col + 2}});
}

void JBlock::printLine1() {    
    cout << blockCells[0].getShape();
    cout << "          ";
}

void JBlock::printLine2() {
    int length = blockCells.size();
    for (int i = 1; i < length; i++) {
    cout << blockCells[i].getShape();
    }
    cout << "        ";
}





