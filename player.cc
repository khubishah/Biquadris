#include "player.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


Player::Player(int levelNum, unsigned int seed, string inputFile): levelNum{levelNum}, seed{seed}, inputFile{inputFile} {
    isRandom = true;
}

int Player::getScore() {
    return score;
}

void Player::setScore(int n) {
    score = n;
}

int Player::getLevelNum() {
    return levelNum;
}

Level * Player::initLevel() { // initializes level for each player
    if(levelNum == 0) {
		 return new Level_0(inputFile);
	 }
	 else if (levelNum == 1) {
		 return new Level_1(seed);
	 }
	 else if (levelNum == 2) {
		 return new Level_2(seed);
	 }
	 else if (levelNum == 3) {
		 return new Level_3(seed);
	 }
	 else if (levelNum == 4) {
		 return new Level_4(seed);
	 }
     else {         
         return nullptr; // error
     }
}

// initializes board for each player
void Player::init(Xwindow * w, int playerIndex) {
    delete level;
    level = initLevel();
    currBlock = level->generateBlock(isRandom, inputFile);
    nextBlock = level->generateBlock(isRandom, inputFile);
    board.init(w, playerIndex);
    this->setScore(0);
    isEffectEarned = false;
    roundsWithoutClearing = 0; 
}

//read the commands given by the player
void Player::takeTurn(string whichCommand, int multiplier, bool &failAdd) {
    string direction;
     
    if (whichCommand == "left" || whichCommand == "right" || whichCommand == "down") {    
        direction = whichCommand;  
        board.translateBlock(direction, multiplier, currBlock);        
    }
    else if (whichCommand == "clockwise" || whichCommand == "counterclockwise") {
        direction = whichCommand;
        board.rotateBlock(direction, multiplier, currBlock);        
    }
    // last move before turn will end
    else if (whichCommand == "drop") {
        board.dropBlock(currBlock);
        update(failAdd);
        currBlock = nextBlock;
        nextBlock = level->generateBlock(isRandom, inputFile); //set next block;
        bool success = board.addBlock(currBlock);
        if (success == false) {
            failAdd = true;
            return;
        }
        if (isEffectHeavy) {
            currBlock->setHeavy(currBlock->getHeavy() - 1); //reset after player drops
            isEffectHeavy = false;
        }
    }
    else if (whichCommand == "levelup") {
        for (int i = 0; i < multiplier; i++) {
            if (levelNum < 4) {
                levelNum++;
            }
        }        
        delete level;
        level = initLevel();
    }
    else if (whichCommand == "leveldown") {
        int temp = levelNum;
        for (int i = 0; i < multiplier; i++) {
            if (levelNum > 0) {
                levelNum--;
            }
        }        
        if (levelNum == 0 && inputFile == "") {
            cout << "You cannot play Level 0 without a script file" << endl;
            levelNum = temp;
        }
        else {
            delete level;
            level = initLevel();
        }    
    }
    else if (whichCommand == "restart" || whichCommand == "quit" || whichCommand == "random" || whichCommand == "norandom" || whichCommand == "sequence") {
        cout << "You must first finish your turn (drop this block) before executing this command." << endl;
    }
    // for testing purposes
    else if (whichCommand == "L" || whichCommand == "I" || whichCommand == "J" ||
    whichCommand == "Z" || whichCommand == "O" || whichCommand == "S"
    || whichCommand == "T") {
        board.removeBlock(currBlock);
        delete currBlock;
        if (whichCommand == "I") {
            currBlock = new IBlock(levelNum, 0); 
        }
        else if (whichCommand == "J") {
            currBlock = new JBlock(levelNum, 0);
        }
        else if (whichCommand == "Z") {
            currBlock = new ZBlock(levelNum, 0);
        }
        else if (whichCommand == "O") {
            currBlock = new OBlock(levelNum, 0);
        }
        else if (whichCommand == "S") {
            currBlock = new SBlock(levelNum, 0);
        }
        else if (whichCommand == "T") {
            currBlock = new TBlock(levelNum, 0);
        }
        else if (whichCommand == "L") {
            currBlock = new LBlock(levelNum, 0);
        }
        bool isSuccess = board.addBlock(currBlock);
        if (isSuccess == false) {
            failAdd = true;
            return;
        }        
    }
    else {
        // handle invalid input
        cerr << "Invalid Command. Please enter a valid command." << endl;
    }    
}

// handles calculation of the score
void Player::update(bool & failAdd) {    
    pair<int, int> numRowsAndScore = board.updateBoard();    
    score += numRowsAndScore.second; //block score
    if (numRowsAndScore.first != 0) {
        score += (numRowsAndScore.first + levelNum) * (numRowsAndScore.first + levelNum); //update score based on numRows deleted
    }
    if (numRowsAndScore.first >= 2) {
        isEffectEarned = true;
    }
    if (numRowsAndScore.first == 0 && levelNum == 4) {
        roundsWithoutClearing ++;
    }
    if (roundsWithoutClearing == 5 && levelNum == 4) {
        currBlock = new StarBlock(levelNum, 0);
        bool success = board.addBlock(currBlock);        
        if (success == false) {
            cout << "Star block cannot be placed." << endl;
            failAdd = true;
            return;
        }
        else {
            board.dropBlock(currBlock);
        }
        roundsWithoutClearing = 0;
    }
}

Player::~Player() { //destroy player
    delete level;
    delete nextBlock;   
}

// text display for each player
void Player::tprint(int i) {
    if (i == 1) {
        cout << "Level: " << "   " << levelNum;        
    }
    else if (i == 2) {
        cout << "Score: " << "   " << score;        
    }
    else if (i == 3) {
        cout << "-----------";
    }
    else if (i <= 21) {
        board.tprint(i-4);
    }
    else if (i == 22) {
        cout << "-----------";
    }
    else if (i == 23) {
        cout << "Next:      ";
    }
    else if (i== 24) {
        nextBlock->printLine1();        
    }
    else if (i == 25) {
        nextBlock->printLine2();
    }
}

// graphics display for each player
void Player::gprint(Xwindow * w, int width, int height) {
    ostringstream l;
    l << levelNum;
    ostringstream s;
    s << score;
    string lvl = "Level: " + l.str();
    string pts = "Score: " + s.str();
    w->drawString(width + 2, 20, lvl, Xwindow::Cyan);
    w->drawString(width + 2, 40, pts, Xwindow::Cyan);
    w->fillRectangle(width, 50, 220, 1, Xwindow::White);
    w->fillRectangle(width, 410, 220, 1, Xwindow::White);
    w->fillRectangle(width + 218, 0, 1, 500, Xwindow::White);
    w->drawString(width + 2, 450, "Next: ", Xwindow::Cyan);
    w->fillRectangle(width, 460, 80, 20, Xwindow::Black);
    w->fillRectangle(width, 480, 80, 20, Xwindow::Black);
    if (isEffectBlind) {
        w->fillRectangle(width + 60, 120, 120, 160, Xwindow::White);     
    }
    if (nextBlock->blockCells[0].getShape() == 'I') {
        w->fillRectangle(width, 460, 80, 20, Xwindow::Brown);
    }
    else if (nextBlock->blockCells[0].getShape() == 'O') {
        w->fillRectangle(width, 460, 40, 40, Xwindow::Cyan);
    }
    else if (nextBlock->blockCells[0].getShape() == 'J') {
        w->fillRectangle(width, 460, 20, 20, Xwindow::Blue);
        w->fillRectangle(width, 480, 60, 20, Xwindow::Blue);
    }
    else if (nextBlock->blockCells[0].getShape() == 'L') {
        w->fillRectangle(width + 40, 460, 20, 20, Xwindow::Green);
        w->fillRectangle(width, 480, 60, 20, Xwindow::Green);
    }
    else if (nextBlock->blockCells[0].getShape() == 'S') {
        w->fillRectangle(width + 20, 460, 40, 20, Xwindow::Orange);
        w->fillRectangle(width, 480, 40, 20, Xwindow::Orange);
    }
    else if (nextBlock->blockCells[0].getShape() == 'Z') {
        w->fillRectangle(width, 460, 40, 20, Xwindow::Yellow);
        w->fillRectangle(width + 20, 480, 40, 20, Xwindow::Yellow);
    }
    else if (nextBlock->blockCells[0].getShape() == 'T') {
        w->fillRectangle(width, 460, 60, 20, Xwindow::Magenta);
        w->fillRectangle(width + 20, 480, 20, 20, Xwindow::Magenta);
    }
}




