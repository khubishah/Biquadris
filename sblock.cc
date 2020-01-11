#include "sblock.h"
#include "cell.h"
#include "coordinate.h"
using namespace std;

SBlock::SBlock(int levelCreatedIn, int howHeavy): Block{levelCreatedIn, howHeavy} {
    Coordinate init_coord{3,0};
    blockCells.emplace_back(Cell{'S', Coordinate{init_coord.row + 1, init_coord.col}});
    blockCells.emplace_back(Cell{'S', Coordinate{init_coord.row + 1, init_coord.col + 1}});
    blockCells.emplace_back(Cell{'S', Coordinate{init_coord.row, init_coord.col + 1}});
    blockCells.emplace_back(Cell{'S', Coordinate{init_coord.row, init_coord.col + 2}});
}

void SBlock::printLine1() {
    cout << " ";
    for(int i = 0; i < 2; i++) {
        cout<<blockCells[i].getShape();
    }
    cout << "        ";    
}


void SBlock::printLine2() {
     for(int i = 2; i < 4; i++) {
        cout<<blockCells[i].getShape();
    }
    cout << "         ";    
}



