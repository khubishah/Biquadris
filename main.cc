#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include "biquadris.h"
using namespace std;


int main(int argc, char *argv[]) {


  // command line -text, -seed xxx, -scriptfile1 xxx, -scriptfile2 xxx, - startlevel n (default 0)
    int numPlayers = 0;
    cout<<"--------------------------------" <<endl;
    cout<<"Welcome! Time to play Biquadris!" <<endl;    
    cout<<"--------------------------------" <<endl;
    cout << "Enter the number of players:" << endl;
    cin >> numPlayers;
    if(cin.eof()) {
        return 1;
    }
    if(numPlayers <= 0) {
        cerr << "Invalid number of players." << endl;    
        return 1;
    }
    bool graphics = true;
    unsigned int seed = 592;
    int level = 0;    
    // each index of the following array corresponds to the scriptfile for the index i+1th
    string playerFiles[numPlayers];
    for (int i = 0; i < numPlayers; i++) {
        playerFiles[i] = "";

    }    
    // interpreting the command line arguments and setting the variables of seed, level, files accordingly
    for (int i = 1; i < argc;  i++) {
        string arg{argv[i]};
        if (arg == "-text" ) {
            graphics = false;

        }
        else if (arg == "-scriptfile") {
            cerr << "Invalid command line argument" << endl;
            return 1;
        }
        else if (arg.substr(0, 11) == "-scriptfile") {
            // get the scriptfile NUMBER only
            string temp = arg.substr(11, arg.length() - 11);
            
            istringstream fileNum{temp};
            int n;
            fileNum >> n;
            playerFiles[n - 1] = argv[i+1];
           
            i++;
        }
        else if (arg == "-startlevel") {
            istringstream s(argv[i+1]);
            i++;
	        s >> level;

        }
        else if (arg == "-seed") {
            istringstream s(argv[i+1]);
            i++;
	        s >> seed;
        }
        else {
            cerr << "Invalid command line arguments" << endl;
            return 1;
        }

    }
    // initialize the game 
    // initalize the boards for each player
    // initialize the players
    // initialize the level (each level initializes each block and adds it to a vector of blocks)
    // initalize currblock, nextblock, score
    Biquadris b{seed, level, graphics};
    b.initGame(graphics, level, seed);
    // for multiplayer, we would need a for-loop to initialize each player in a game 
    for (int i = 0; i < numPlayers; i++) {
        if (playerFiles[i] == "" && level == 0) {
            cerr << "Players cannot play level 0 without a script file" << endl;
            return 1;
        }
        if (playerFiles[i] != "") {
            b.addPlayer(level, seed, playerFiles[i]);            
        }
        else {
            b.addPlayer(level, seed); 
            // deal with the fact that they don't have a file in the addPlayer function
        }
    }
    b.startPlaying();
}








