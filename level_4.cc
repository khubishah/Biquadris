#include <vector>
#include <cstdlib>
#include <iostream>
#include "level_4.h"
#include "iblock.h"
#include "jblock.h"
#include "zblock.h"
#include "lblock.h"
#include "sblock.h"
#include "oblock.h"
#include "tblock.h"

using namespace std;

Level_4::Level_4(unsigned int seed): seed{seed}{
	srand(seed);
     counter = 0;
}
Block * Level_4::generateBlock(bool isRandom, std::string file){
     if (isRandom == true) { // if norandom has been set
          int dropLimit = 1;
          Block * send;
          
          int prob = rand() % 9 + 1; // generates number from 1 to 9
          
          if(prob == 1 || prob == 2) {
               send = new ZBlock{score,dropLimit};
          }
          else if (prob == 3 || prob == 4) {
               send = new SBlock{score,dropLimit};
          }
          else if (prob == 5) {
               send = new IBlock{score,dropLimit};
          }
          else if (prob == 6) {
               send = new JBlock{score,dropLimit};
          }
          else if (prob == 7) {
               send = new LBlock{score,dropLimit};
          }
          else if (prob == 8) {
               send = new OBlock{score,dropLimit};
          }
          else {
               send = new TBlock{score,dropLimit};
          }
          return send;
     }
	

     else  { // if norandom has been set
          char blockchar;          
          ifstream readFile{file};
          while (readFile >> blockchar) {
               commandsVec.emplace_back(blockchar);
          }
          char blocknext = commandsVec[counter];   
          int temp = commandsVec.size();
          Block * send = nullptr;          
          int dropLimit = 1;
          if (blocknext == 'S') {
               send = new SBlock{score, dropLimit};	
          }
          else if (blocknext == 'Z') {
               send = new ZBlock{score, dropLimit};
          }
          else if(blocknext == 'I') {        
               send = new IBlock{score, dropLimit};
          }
          else if (blocknext == 'J') {
               send = new JBlock{score, dropLimit};
          } 
          else if (blocknext == 'O') {
               send = new OBlock{score, dropLimit};
          }
          else if (blocknext == 'T') {
               send = new TBlock{score, dropLimit};
          }
          else if (blocknext == 'L') {
               send = new LBlock{score, dropLimit};
          }
          counter++;           
          if(counter == temp) {
               counter = 0;
          } 
          return send;
     }
}






