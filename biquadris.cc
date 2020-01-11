#include "biquadris.h"
#include <vector> 
#include <array>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

Biquadris::Biquadris(unsigned int seed, int level, bool graphics): seed{seed}, level{level}, graphics{graphics} {
    highScore = 0;
    w = nullptr;
}

void Biquadris::initGame(bool graphics, int level, unsigned int seed) {
    this->level = level;
    this->seed = seed;
}

void Biquadris::addPlayer(int level, unsigned int seed, string inputFile) {
    Player newPlayer{level, seed, inputFile};
    vecOfPlayers.emplace_back(newPlayer); //add the newPlayer to the vector of Players
}

void Biquadris::restart() { //restarts game
    if (graphics == true) { //initializing graphics mode
        delete w;
        int numPlayers = vecOfPlayers.size();
        int boardWidth = numPlayers * 220;
        int boardHeight = 500;
        w = new Xwindow{boardWidth, boardHeight};
    }
    int length = vecOfPlayers.size();
    
    for (int i = 0; i < length; i++) {
        delete vecOfPlayers[i].nextBlock;
        vecOfPlayers[i].init(w, i);
    }
}

int Biquadris::matchCommands(string &input) {
        vector <string> commands = {"left", "right", "down", "clockwise", "counterclockwise",
        "drop", "levelup", "leveldown", "norandom", "random", "sequence",
        "restart", "I", "J", "L", "S", "Z", "T", "O"};
        int multiplier = 1;
        string copy = input;
        int readMult;
        istringstream ss{input};
        istringstream scopy{copy};
        string cmd = "";
        if(scopy >> readMult){
            multiplier = readMult;
            scopy >> cmd;
        }
        else {
            ss >> cmd;
        }
    
        int length = commands.size();
        bool match = true;
        // length of the command that the user entered
        int cmdLen = cmd.length();

        // finds the command that the user input matches with
        for (int i = 0; i < length; i++) { 
            
            for (int j = 0; j < cmdLen; j++) {
                if (cmd[j] != commands[i][j]) {
                    match = false;
                    break;
                }
            }
            if (match == true) {
                input = commands[i];
                break;
            }
            else {
                match = true;
            }
        }

        return multiplier;
    
}
void Biquadris::startPlaying() {
    
    string input = "";
    bool noLoses = true;
    int multiplier = 1; // default
    
    int numPlayers = vecOfPlayers.size();
    int turn = 0;
    ifstream readFile;
    restart();
    for (int i = 0; i < numPlayers; i++) {   // adding a currblock for each player   
        vecOfPlayers[i].board.addBlock(vecOfPlayers[i].currBlock);
    }
    print(); //printing the board at the beginning of the game
    bool sequence = false;
    bool addFail = false;
    cout << "Player 1, please enter a command:" << endl;
    while (noLoses) {
        if (vecOfPlayers[turn % numPlayers].isEffectHeavy) {
            vecOfPlayers[turn % numPlayers].currBlock->setHeavy(vecOfPlayers[turn % numPlayers].currBlock->getHeavy() + 1);
        }
        if (sequence == false) { //if the sequence file is not given
            cin >> input;
            if(cin.eof()) {
                        break;
            }
        }
        else if (sequence == true) { //if the sequence file is given
            readFile >> input;
            if(readFile.eof()) {
                cout << "All commands in the file provided have been completed. Game is now ending" << endl;
                break;
            }
        }
           
        
        multiplier = matchCommands(input);   

        if (input== "restart") {
            restart();
            for (int i = 0; i < numPlayers; i++) {      
                vecOfPlayers[i].board.addBlock(vecOfPlayers[i].currBlock);
            }
            print();            
        }
        else if (input == "norandom") {
            string file;
            if (sequence == false) {
                    cin >> file;
                    if(cin.eof()) {
                        break;
                    }
                }
            else if (sequence == true) {
                readFile >> file;
                if (readFile.eof()) {
                    break;
                }
            }
            if (file == "") {
                cout << "You must provide a valid file." << endl;                
            }  
            if (vecOfPlayers[turn % numPlayers].getLevelNum() == 3 || vecOfPlayers[turn % numPlayers].getLevelNum() == 4) {
                vecOfPlayers[turn % numPlayers].inputFile = file;
                vecOfPlayers[turn % numPlayers].isRandom = false;
                cout << "Nonrandom mode activated. Reading blocks from file: "<< file << "." << endl;
            }
            else {
                cout << "This command is only valid for Level 3 and 4." << endl;
            }
        }
        else if (input == "random") {
            if (vecOfPlayers[turn % numPlayers].getLevelNum() == 3 || vecOfPlayers[turn % numPlayers].getLevelNum()== 4) {
                vecOfPlayers[turn % numPlayers].inputFile = "";
                vecOfPlayers[turn % numPlayers].isRandom = true;
                cout << "Random mode activated" << endl;
            }
            else {
                cout << "This command is only valid for Level 3 and 4." << endl;
            }
        }
        else if (input == "sequence") {
            string file;
            cin >> file;
            readFile.open(file);
            sequence = true;
        }
        else if (input == "quit") {
            cout << "Thanks for playing! Bye bye." << endl;
            
            break;
        }
        else {
            
            while (input != "drop") {                 
                //current player's turn keeps executing until they don't input "drop"  
                vecOfPlayers[turn % numPlayers].takeTurn(input, multiplier, addFail);
                print();
                cout << "Player " << ((turn % numPlayers) + 1) << ", please enter a command: " << endl;
                if (sequence == false) {
                    cin >> input;
                    if(cin.eof()) {
                        break;
                    }
                }
                else if (sequence == true) {
                    readFile >> input;
                    if (readFile.eof()) {
                        break;
                    }
                }
                
                multiplier = matchCommands(input); //handles input if substring matches one of the command
            }
            if (addFail == true) {
                break;
            }
            if (input == "drop") { //complete current player's last turn            
                vecOfPlayers[turn % numPlayers].takeTurn(input, multiplier, addFail);
                if (addFail == true) {
                    cout << "Game over. Player "<< ((turn % numPlayers) + 1) <<" lost. New block could not be added to the board." << endl;
                    delete vecOfPlayers[turn % numPlayers].currBlock;
                    cout << "High Score: " << highScore << endl;
                    noLoses = false;
                    break;
                }
                if (vecOfPlayers[turn % numPlayers].isEffectBlind == true) {
                    vecOfPlayers[turn % numPlayers].isEffectBlind = false;
                    vecOfPlayers[turn % numPlayers].board.isEffectBlind = false;
                    if (graphics == true) {                    
                        vecOfPlayers[turn % numPlayers].board.resetBlind();
                    }          
                }                
                print();
                if (highScore < vecOfPlayers[turn % numPlayers].getScore()) {
                    highScore = vecOfPlayers[turn % numPlayers].getScore();
                }
                //if block could not be added successfully or if didYouLose returns true, then player has lost.
            
                if (vecOfPlayers[turn % numPlayers].board.didYouLose(vecOfPlayers[turn % numPlayers].currBlock)) {
                    
                    cout << "Game over. Player "<< ((turn % numPlayers) + 1) <<" lost. A column has been filled." << endl;                 
                    cout << "High Score: " << highScore << endl;
                    noLoses = false;
                    break;
                }
                
            }
            if (vecOfPlayers[turn % numPlayers].isEffectEarned) { //if current player has earned a special effect
                //ask current player what effect they want
                cout << "Player " << (turn % numPlayers) + 1 << " earned a special effect! Please enter which effect: (blind, heavy, or force) ";
                string whichEffect;
                if (sequence == false) {
                    cin >> whichEffect;
                    if (cin.eof()) {
                        break;
                    }
                }
                else if (sequence == true) {
                    readFile >> whichEffect;
                    if (readFile.eof()) {
                        break;
                    }
                } 
                if (whichEffect == "blind") { // blind effect makes a part of the board invisible                    
                    for (int i = 0; i < numPlayers; i++) {
                        if (i != turn % numPlayers) { //we don't want to apply the effect on ourself!
                            vecOfPlayers[i].isEffectBlind = true;
                            vecOfPlayers[i].board.isEffectBlind = true;
                        }
                    }
                    print();
                    
                }
                else if (whichEffect == "heavy") { // makes the block drop 1 after every translation
                    for (int i = 0; i < numPlayers; i++) {
                        if (i != turn % numPlayers) { 
                            vecOfPlayers[i].isEffectHeavy = true;

                        }
                    }
                }
                else if (whichEffect == "force") {
                    cout << "You chose force. Please enter which block you would like to force: ";
                    char whichBlock; //which block they want to force
                    if (sequence == false) {
                        cin >> whichBlock;
                        if (cin.eof()) {
                            break;
                        }
                    }
                    else if (sequence == true) {
                        readFile >> whichBlock;
                        if (readFile.eof()) {
                             break;
                        }
                    }
                    bool successForce = true; 
                    for (int i = 0; i < numPlayers; i++) {
                        int levelNum = vecOfPlayers[i].getLevelNum();
                        if (i != turn % numPlayers) { 
                            vecOfPlayers[i].board.removeBlock(vecOfPlayers[i].currBlock); //call board's remove block.
                            delete vecOfPlayers[i].currBlock;
                            if (whichBlock == 'I') { // adding the new block to the board, the one requested by the player
                                vecOfPlayers[i].currBlock = new IBlock(levelNum, 0);
                            }
                            else if (whichBlock == 'J') {
                                vecOfPlayers[i].currBlock = new JBlock(levelNum, 0);
                            }
                            else if (whichBlock == 'Z') {
                                vecOfPlayers[i].currBlock = new ZBlock(levelNum, 0);
                            }
                            else if (whichBlock == 'O') {
                                vecOfPlayers[i].currBlock = new OBlock(levelNum, 0);
                            }
                            else if (whichBlock == 'S') {
                                vecOfPlayers[i].currBlock = new SBlock(levelNum, 0);
                            }
                            else if (whichBlock == 'T') {
                                vecOfPlayers[i].currBlock = new TBlock(levelNum, 0);
                            }
                            else if (whichBlock == 'L') {
                                vecOfPlayers[i].currBlock = new LBlock(levelNum, 0);
                            }
                            
                            successForce = vecOfPlayers[i].board.addBlock(vecOfPlayers[i].currBlock);
                            print();
                        }
                        if (!successForce) { //someone lost.
                            delete vecOfPlayers[i].currBlock;
                            cout << "Forced block cannot be added! Player "<< (i+1) <<" lost. Game over." << endl;
                            cout << "High Score: " << highScore << endl;
                
                            break;
                            
                        }
                    }
                    if (!successForce) {
                        break;
                    }
                    
                }
                else {
                    cout << "Invalid effect. Opportunity Lost." << endl; //invalid force was given
                }
                vecOfPlayers[turn % numPlayers].isEffectEarned = false;
            }
            turn++;
            cout << "Player " << ((turn % numPlayers) + 1) << ", please enter a command: " << endl;
        }
    }
}

void Biquadris::tprint() {
    for (int i = 1; i < 26; i++) {
        for (auto &p: vecOfPlayers) {
            p.tprint(i);
            cout << "      ";
        }
        cout << endl;
    }
}

void Biquadris::print() {
    if (graphics == true) {
        gprint();
    }
    else {
        tprint();
    }
}

void Biquadris::gprint() {
    int length = vecOfPlayers.size();
    int boardHeight = 500;

    for (int i = 0; i < length; i++){
        vecOfPlayers[i].gprint(w, i*220, boardHeight);
    }

}


