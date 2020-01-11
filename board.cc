#include "board.h"
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Board::~Board(){
	delete td; //deleting text display
	delete gd; // deleting graphics display
	int length = boardBlocks.size();
	for (int i = 0; i < length; i++) {
		delete boardBlocks[i]; // deleting boardBlocks
	}
} 

void Board::init(Xwindow * w, int playerIndex) { //initializing the board
	numRows = 18;
	numCols = 11;
	vecOfCells.clear();	
	
	delete td;
	delete gd;	
	if (w == nullptr) {
		td  = new TextDisplay{numRows, numCols};
	}
	else {
		gd = new GraphicsDisplay{w, playerIndex};
	}	
	for (int i = 0 ; i < numRows; i++) {
        vector <Cell> row;
        vecOfCells.emplace_back(row);
        for (int j = 0; j < numCols; j++) {
            Coordinate coords{i, j};
            Cell cell{' ', coords};
            vecOfCells[i].emplace_back(cell);
			if (w == nullptr) {
				vecOfCells[i][j].attach(td);
			}
			else {
				vecOfCells[i][j].attach(gd);
			}
			
        }
    }
}

void Board::removeBlock(Block * block) { // removing the block once it has been deleted from the board
	int length = block->blockCells.size();
	vector <Observer<Info>*> obs;
	Observer<Info> * toRemove = nullptr;
	bool firstRound = true;
	vector<Coordinate> coords = block->getBlockCellsCoords();
	for (int i = 0; i < length; i++) {
			if (firstRound == true) {
				obs = vecOfCells[coords[i].row][coords[i].col].getObservers();
				toRemove = obs.back();
				firstRound = false;
			}
			vecOfCells[coords[i].row][coords[i].col].setShape(' ');	
			vecOfCells[coords[i].row][coords[i].col].notifyObservers();
			vecOfCells[coords[i].row][coords[i].col].detach(toRemove);
	}
	boardBlocks.pop_back();
}

bool Board::addBlock(Block * block) { // adding the current block to the board
	int length = block->blockCells.size();
	vector<Coordinate> coords = block->getBlockCellsCoords();
	// checks if the initial spot where you have to add a block to a board is occupied or not (should not be or else you lose)

	bool validMove = isValidMove(coords);
	if (validMove == true) {
		// add the block
		for (int i = 0; i < length; i++) {
			vecOfCells[coords[i].row][coords[i].col].setShape(block->blockCells[i].getShape());
			vecOfCells[coords[i].row][coords[i].col].notifyObservers();
			vecOfCells[coords[i].row][coords[i].col].attach(block);
		}
		boardBlocks.emplace_back(block);
	}
	// if block does or not does successfully fit on the board when you try to first add it, retunrs false--they lost!
	return validMove;
}

//translates the block as many times as possible
void Board::translateBlock(string translateType, int multiplier, Block * block) {
	// the block given is already on the board... player is in the process of taking their turn
	bool validTranslation = true;
	bool happenedOnce = false;
	for (int i = 0; i < multiplier; i++) {
		validTranslation = attemptCellsTranslation(translateType, block);	
		if (validTranslation) {
			happenedOnce = true;
		}
		else {			
			break;
		}
	}
	if (happenedOnce) {
		dropForHeaviness(block);
	}
}

//moves the block as many times as possible
bool Board::attemptCellsTranslation(string translateType, Block *block){
	vector <Coordinate> newCoords = block->getBlockCellsCoords();
	vector <Coordinate> currCoords = block->getBlockCellsCoords();
	char currentShape = vecOfCells[currCoords[0].row][currCoords[0].col].getShape();
	int length = newCoords.size();
	for (int i = 0; i < length; i++) {
		if (translateType == "left") {
			newCoords[i].col--;
			
		}
		else if (translateType == "right") {
			newCoords[i].col++;
		

		}
		else if (translateType == "down") {
			newCoords[i].row++;
		}
	}
	if (translateType == "down") {
		for (int i = 0; i < length; i++) {
			if (newCoords[i].row == 18) {
				return false;
			}
		}
	}
	for (int i = 0; i < length; i++) {
		vecOfCells[currCoords[i].row][currCoords[i].col].setShape(' ');
	}
	bool isValid = isValidMove(newCoords);
	
	for (int i = 0; i < length; i++) {
		vecOfCells[currCoords[i].row][currCoords[i].col].setShape(currentShape);
	}
	
	if (isValid == true) {
		
		moveBlockCells(block, newCoords);
	}
	return isValid;
}

//rotates the block as many times as possible
void Board::rotateBlock(string rotateType, int multiplier, Block * block) {
	bool validRotation = true;
	bool happenedOnce = false;
	for (int i = 0; i < multiplier; i++) {
		validRotation = attemptCellsRotation(rotateType, block);
		if (validRotation == true) {			
			happenedOnce = true;
		}
		else {		
			break;
		}
	}
	if (happenedOnce == true) {	
		dropForHeaviness(block);
	}
}

// rotated as many times as possible
// used the rotation matrix
bool Board::attemptCellsRotation(string rotateType, Block *block) {
	bool isOriginR = false;
	bool isOriginC = false;
	int rowMin = 0;
	int colMin = 0;
	int originR, originC;
	vector <Coordinate> blockCoords = block->getBlockCellsCoords();
	char currentShape = vecOfCells[blockCoords[0].row][blockCoords[0].col].getShape();
	int length = blockCoords.size();
	vector<Coordinate> newCoords;	

	for (int i = 0; i < length; i++) {
		newCoords.emplace_back(blockCoords[i]);
		Coordinate current = newCoords.back();
		if (isOriginC == false || current.col < originC) {
			isOriginC = true;
			originC = current.col;
		}
		if (isOriginR == false|| current.row < originR) {
			isOriginR = true;
			originR = current.row;
		}
		
	}
	
	for (int i = 0; i < length; i++) {
		int intermediate = newCoords[i].col;
		if (rotateType == "clockwise") {
			newCoords[i].col = 0 - (newCoords[i].row - originR);
			newCoords[i].row = intermediate - originC;
		}
		else if (rotateType == "counterclockwise") {
			newCoords[i].col = newCoords[i].row - originR;
			newCoords[i].row = 0 - (intermediate  - originC);
		}		
		if (newCoords[i].row < rowMin) {
			rowMin = newCoords[i].row;
		}
		if (newCoords[i].col < colMin) {
			colMin = newCoords[i].col;
		}
	}
	for (int i = 0; i < length; i++) {
		newCoords[i].row += originR - rowMin;
		newCoords[i].col += originC - colMin;
	}
	
	for (int i = 0; i < length; i++) {
		vecOfCells[blockCoords[i].row][blockCoords[i].col].setShape(' ');
	}

	bool isSuccess = isValidMove(newCoords);

	for (int i = 0; i < length; i++) {
		vecOfCells[blockCoords[i].row][blockCoords[i].col].setShape(currentShape);
	}

    if (isSuccess == true) {
        moveBlockCells(block, newCoords);
    }

    return isSuccess;
}


void Board::dropForHeaviness(Block * b) {
	int times = b->getHeavy();
	for (int i = 0; i < times; i++) {
		bool isSuccess = attemptCellsTranslation("down", b);
		if (isSuccess == false) break;
	}
}

void Board::dropBlock(Block *block) {
		// keep dropping the block until it is valid to do so	
	while (attemptCellsTranslation("down", block)) {
		// just a loop
	}
}

//checks if the block movement does not colide with another block
// checks if the block movement is within the boundary of the board
bool Board::isValidMove(vector<Coordinate> coords) {
	int length = coords.size();
	for (int i = 0; i < length; i++) {
		if (coords[i].row < 0 || coords[i].row >= numRows || coords[i].col < 0 || coords[i].col >= numCols) {
			return false;
		}
		if (vecOfCells[coords[i].row][coords[i].col].getShape() != ' ') {
			return false;
		}		
	}	
	return true;
}

// handles deleting a row once a row has been filled
std::pair <int, int> Board::updateBoard() {
	bool fullRow = true;
	int numRowsCleared = 0;
	int blockClearingPoints = 0;
	vector <Observer<Info>*> obs;	
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {			
			if(vecOfCells[i][j].getShape() == ' ') {
				fullRow = false;
			}
		}
		if (fullRow == true) {		
			// the given row was full
			for (int k = 0; k < numCols; k++) {			
				Coordinate coord{i, k};
				obs = vecOfCells[coord.row][coord.col].getObservers();				
				Observer<Info> * o = obs.back();				
				clearCell(coord);			
				vecOfCells[coord.row][coord.col].notifyObservers();			
				vecOfCells[coord.row][coord.col].detach(o);				
			}			
			shiftCellsDown(i);	
			numRowsCleared++;
		}
		else {
			fullRow = true;
		}
	}
	int numBlocks = boardBlocks.size();
	int i = 0;
	while (i < numBlocks){
		if (boardBlocks[i]->isBlockCleared() == true) {	
			blockClearingPoints += ((boardBlocks[i]->getLevelCreatedIn() + 1) * (boardBlocks[i]->getLevelCreatedIn() + 1));
			delete boardBlocks[i];
			boardBlocks.erase(boardBlocks.begin() + i);
			numBlocks--;		
		}
		else {		
			i++;
		}
	}
	return std::pair<int,int> (numRowsCleared, blockClearingPoints);
}

// used by update to move the above rows down once a row has a
void Board::shiftCellsDown(int row) {
	vector <Observer<Info>*> obs;

	Observer<Info> * o;

	for (int i = row - 1; i >= 3; i--) {
		for (int j = 0; j < numCols; j++) {
			if (vecOfCells[i][j].getShape() != ' ') {
				obs = vecOfCells[i][j].getObservers();
				o = obs.back();
				vecOfCells[i+1][j].setShape(vecOfCells[i][j].getShape());
			
				vecOfCells[i+1][j].attach(o);
				vecOfCells[i+1][j].notifyObservers();
				vecOfCells[i][j].setShape(' ');
				
				vecOfCells[i][j].notifyObservers();
				vecOfCells[i][j].detach(o);
			}
		}
	}
}

// moves the block to a new location and notifies the observer
void Board::moveBlockCells(Block * block, std::vector <Coordinate> newCoords) {
	int length = block->blockCells.size();
	vector <Coordinate> old = block->getBlockCellsCoords();
	char set;
	vector <Observer<Info>*> obs;
	bool firstRound = true;
	Observer<Info> * toRemove = nullptr;
	for (int i = 0; i < length; i++) {
		if (firstRound == true) {
			obs = vecOfCells[old[i].row][old[i].col].getObservers();
			toRemove = obs.back();
			firstRound = false;
		}
		set = vecOfCells[old[i].row][old[i].col].getShape();		
		vecOfCells[old[i].row][old[i].col].setShape(' ');
		vecOfCells[old[i].row][old[i].col].notifyObservers();
		vecOfCells[old[i].row][old[i].col].detach(toRemove);
	}
	for (int i = 0; i < length; i++) {
		vecOfCells[newCoords[i].row][newCoords[i].col].setShape(set);
		vecOfCells[newCoords[i].row][newCoords[i].col].attach(toRemove);
		vecOfCells[newCoords[i].row][newCoords[i].col].notifyObservers();		
	}
}

//checks if a cell is empty (' ') or not
bool Board::isCellEmpty(Coordinate coordinate) {
	if (vecOfCells[coordinate.row][coordinate.col].getShape() == ' ') {
		return true;
	}
	else {
		return false;
	}
}

bool Board::didYouLose(Block * b) {
	// if any one of the cells in the third are not empty, then you lose
	bool inCurr = false;
	int len = b->blockCells.size();
	for (int i = 0; i < numCols; i++) {		
		if (vecOfCells[3][i].getShape() != ' ') {			
			for (int j = 0; j < len; j++) {				
				Coordinate c = b->blockCells[j].getcoordinates();	
				if (3 == c.row && i == c.col) {
					inCurr = true;
				}
			}
			if (inCurr == false) {				
				return true;				
			}
			else {
				inCurr = false;
			}		
		}
	}
	return false;
}

// sets the cell to ' '
void Board::clearCell(Coordinate coordinate) {
	vecOfCells[coordinate.row][coordinate.col].setShape(' ');
}

void Board::tprint(int i) { // textdisplay
	  td->print(i, isEffectBlind);
}

void Board::resetBlind() { // removes the blind effect
	  for (int i = 2; i <= 11; i++) {
		  for (int j = 2; j <= 8; j++) {
			  vecOfCells[i][j].notifyObservers();
		  }
	  }
  }



  
