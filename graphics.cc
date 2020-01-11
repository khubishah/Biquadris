#include "graphics.h"
#include <vector>
using namespace std;

// initializes the graphics board
GraphicsDisplay:: GraphicsDisplay(Xwindow * w, int i): w{w}, i{i}{
    theDisplay.assign(18, vector <char> (11));
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 11; j++) {
                    theDisplay.at(i).at(j) = ' ';
            }
        }
    int width = w->getWidth();
    int height = 500;
    w->fillRectangle(0,0, width, height, Xwindow::Black);    
}

//notifies the changes to the board
void GraphicsDisplay::notify(Subject<Info> &whoNotified) {
    Info theInfo = whoNotified.getInfo();
    int c = theInfo.coordinate.col;
    int r = theInfo.coordinate.row;
    int x = theInfo.coordinate.col * cellWidth;
    int y = theInfo.coordinate.row * cellHeight;
    int colour;
    if (theInfo.partofWhichShape == ' ' && theDisplay.at(r).at(c) != ' ') {
        theDisplay.at(r).at(c) = ' ';
        colour = Xwindow::Black;
    }
    else if (theInfo.partofWhichShape == 'L' && theDisplay.at(r).at(c) != 'L') {
        theDisplay.at(r).at(c) = 'L';
        colour = Xwindow::Green;
    }
    else if (theInfo.partofWhichShape == 'J' && theDisplay.at(r).at(c) != 'J') {
        theDisplay.at(r).at(c) = 'J';
        colour = Xwindow::Blue;
    }
    else if (theInfo.partofWhichShape == 'S' && theDisplay.at(r).at(c) != 'S') {
        theDisplay.at(r).at(c) = 'S';
        colour = Xwindow::Orange;
    }
    else if (theInfo.partofWhichShape == 'Z' && theDisplay.at(r).at(c) != 'Z') {
        theDisplay.at(r).at(c) = 'Z';
        colour = Xwindow::Yellow;
    }
    else if (theInfo.partofWhichShape == 'O' && theDisplay.at(r).at(c) != 'O') {
        theDisplay.at(r).at(c) = 'O';
        colour = Xwindow::Cyan;
    }
    else if (theInfo.partofWhichShape == 'T' && theDisplay.at(r).at(c) != 'T') {
        theDisplay.at(r).at(c) = 'T';
        colour = Xwindow::Magenta;
    }
    else if (theInfo.partofWhichShape == '*' && theDisplay.at(r).at(c) != '*') {
        theDisplay.at(r).at(c) = '*';
        colour = Xwindow::DarkGreen;
    }
    else if (theInfo.partofWhichShape == 'I' && theDisplay.at(r).at(c) != 'I') {
        theDisplay.at(r).at(c) = 'I';
        colour = Xwindow::Brown;
    }   
    w->fillRectangle(x+ 220*i,y+50, cellWidth , cellHeight, colour);   
}

GraphicsDisplay::~GraphicsDisplay() {    
}





