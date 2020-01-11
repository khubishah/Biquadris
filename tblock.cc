#include "tblock.h"

#include "cell.h"
#include "coordinate.h"
using namespace std;
TBlock::TBlock(int levelCreatedIn, int howHeavy): Block{levelCreatedIn, howHeavy} {
 Coordinate init_coord{3,0};
    blockCells.emplace_back(Cell{'T', Coordinate{init_coord.row, init_coord.col}});
    blockCells.emplace_back(Cell{'T', Coordinate{init_coord.row, init_coord.col + 1}});
    blockCells.emplace_back(Cell{'T', Coordinate{init_coord.row, init_coord.col + 2}});
    blockCells.emplace_back(Cell{'T', Coordinate{init_coord.row + 1, init_coord.col + 1}});
}

void TBlock::printLine1() {    
    for (int i = 0; i < 3; i++) {        
        cout << blockCells[i].getShape();
    }
    cout << "        ";    
}

void TBlock::printLine2() {    
    cout << " " << blockCells[3].getShape() << "         ";
}





