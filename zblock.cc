#include "zblock.h"
#include "cell.h"
#include "coordinate.h"
using namespace std;

ZBlock::ZBlock(int levelCreatedIn, int howHeavy): Block{levelCreatedIn, howHeavy} {
    Coordinate init_coord{3,0};
    blockCells.emplace_back(Cell{'Z', Coordinate{init_coord.row, init_coord.col}});
    blockCells.emplace_back(Cell{'Z', Coordinate{init_coord.row, init_coord.col + 1}});
    blockCells.emplace_back(Cell{'Z', Coordinate{init_coord.row + 1, init_coord.col + 1}});
    blockCells.emplace_back(Cell{'Z', Coordinate{init_coord.row + 1, init_coord.col + 2}});
}


void ZBlock::printLine1() { 
    for(int i = 0; i < 2; i++) {
        cout<< blockCells[i].getShape();
    }
    cout << "         ";   
}

void ZBlock::printLine2() {
    int length = blockCells.size();
    cout<<" ";
    for(int i = 2; i < length; i++) {
        cout<<blockCells[i].getShape();
    }
    cout << "        ";
}





