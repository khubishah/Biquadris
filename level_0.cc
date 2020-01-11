#include <fstream>
#include <vector>
#include "level_0.h"
#include "iblock.h"
#include "jblock.h"
#include "zblock.h"
#include "lblock.h"
#include "sblock.h"
#include "oblock.h"
#include "tblock.h"
using namespace std;

Level_0::Level_0(string inputfile): inputfile{inputfile} {
	char blockchar;
     counter = 0;
	ifstream readfile {inputfile};
	while(readfile >> blockchar) {
          
          commandsVec.emplace_back(blockchar);
     }		
}

// creates the vector of blocks using the sequence of blocks from input file

// sends blocks in order that they appear in the vector blocks
Block * Level_0::generateBlock(bool isRandom, std::string file) {
     char blocknext = commandsVec[counter];   
     int temp = commandsVec.size();
     Block * send = nullptr;      
     int dropLimit = 0;
     if (blocknext == 'S') {
           send = new SBlock{0, dropLimit};	
        }
     else if (blocknext == 'Z') {
          send = new ZBlock{0, dropLimit};
        }
     else if(blocknext == 'I') {        
          send = new IBlock{0, dropLimit};
        }
     else if (blocknext == 'J') {
          send = new JBlock{0, dropLimit};
        } 
     else if (blocknext == 'O') {
          send = new OBlock{0, dropLimit};
        }
      else if (blocknext == 'T') {
          send = new TBlock{0, dropLimit};
        }
     else if (blocknext == 'L') {
          send = new LBlock{0, dropLimit};
        }     

     counter++;  
     
     if(counter == temp) {
           counter = 0;
      }   

     return send;      
}






