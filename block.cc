#include <string>
#include <vector>
#include "block.h"

// ALWAYS UPDATE BLOCKCELLS TO COORDINATE ON BOARD

using namespace std;

int Block:: getPoints() {
    return levelCreatedIn;
}

Block::Block(int levelCreatedIn, int howHeavy): levelCreatedIn{levelCreatedIn}, howHeavy{howHeavy}{}

Block::~Block() {   
}

void Block::notify(Subject<Info> &whoFrom)  { //updates the cells on the board   
    Info theInfo = whoFrom.getInfo();
    Coordinate subjectCoor{theInfo.coordinate.row, theInfo.coordinate.col};
    if (theInfo.partofWhichShape == ' ') {
        // remove this coord from your block cells 
        int len = blockCells.size();
        for (int i = 0; i < len; i++) {
            if (subjectCoor == blockCells[i].getcoordinates()) {
                blockCells.erase(blockCells.begin() + i);
            }
        }
    }
    else {
        int len = blockCells.size();
        bool noMatch = true;
        for (int i = 0; i < len; i++) {
            Coordinate c = blockCells[i].getcoordinates();
            if (subjectCoor.col == c.col && subjectCoor.row == c.row) {
                noMatch = false;
            }
        }
        if (noMatch == true) {
            blockCells.emplace_back(Cell{theInfo.partofWhichShape, subjectCoor});
        }
        
    }

}

vector<Coordinate> Block::getBlockCellsCoords() {
    vector<Coordinate> coordArray;
    int length = blockCells.size();
    for (int i = 0; i < length; i++) {
        Coordinate c = blockCells[i].getcoordinates(); 
        coordArray.emplace_back(c);
    }
    return coordArray;
}

bool Block::isBlockCleared() {
    int length = blockCells.size();
    if (length == 0) {
        return true;
    }
    return false;
}

//accessor methods for all necessary private fields
int Block::getHeavy(){
    return howHeavy;
}
int Block::getLevelCreatedIn(){
    return levelCreatedIn;
}
void Block::setLevelCreatedIn(int n){
    levelCreatedIn = n;
}
void Block::setHeavy(int n){
    howHeavy = n;
}


















    

    
