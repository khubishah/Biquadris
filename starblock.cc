#include "starblock.h"
#include "cell.h"
#include "coordinate.h"
using namespace std;

StarBlock::StarBlock(int levelCreatedIn, int howHeavy): Block{levelCreatedIn, howHeavy} {
     Coordinate init_coord{3,0};
    blockCells.emplace_back(Cell{'*', Coordinate{init_coord.row, init_coord.col + 5}});
}

void StarBlock::printLine1() {
    cout << blockCells[0].getShape()<<"          ";    
}

void StarBlock::printLine2() {
    cout<<"           " ;
}



