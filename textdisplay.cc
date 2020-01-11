#include "textdisplay.h"

using namespace std;

//Set up the display of an EMPTY board
TextDisplay::TextDisplay(int height, int width): boardHeight{height}, boardWidth{width} {
    theDisplay.assign(height, vector <char> (width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                    theDisplay.at(i).at(j) = ' ';
            }
        }
}

void TextDisplay::notify(Subject<Info> &whoNotified) { //cell sends itself in as whoNotified. So we have access to cell's params
    Info theInfo = whoNotified.getInfo();
    int i = theInfo.coordinate.row;
    int j = theInfo.coordinate.col;
    if (theInfo.partofWhichShape == 'I' && theDisplay.at(i).at(j) != 'I') {
        theDisplay.at(i).at(j) = 'I';
    }
    else if (theInfo.partofWhichShape == 'J' && theDisplay.at(i).at(j) != 'J') {
        theDisplay.at(i).at(j) = 'J';
    }
    else if (theInfo.partofWhichShape == 'O' && theDisplay.at(i).at(j) != 'O') {
        theDisplay.at(i).at(j) = 'O';
    }
    else if (theInfo.partofWhichShape == 'S' && theDisplay.at(i).at(j) != 'S') {
        theDisplay.at(i).at(j) = 'S';
    }
    else if (theInfo.partofWhichShape == 'Z' && theDisplay.at(i).at(j) != 'Z') {
        theDisplay.at(i).at(j) = 'Z';
    }
    else if (theInfo.partofWhichShape == 'T' && theDisplay.at(i).at(j) != 'T') {
        theDisplay.at(i).at(j) = 'T';
    }
    else if (theInfo.partofWhichShape == 'L' && theDisplay.at(i).at(j) != 'L') {
        theDisplay.at(i).at(j) = 'L';
    }
    else if (theInfo.partofWhichShape == '*' && theDisplay.at(i).at(j) != '*') {
        theDisplay.at(i).at(j) = '*';
    }
    else if (theInfo.partofWhichShape == '?' && theDisplay.at(i).at(j) != '?') {
        theDisplay.at(i).at(j) = '?';
    }
    else if (theInfo.partofWhichShape == ' ' && theDisplay.at(i).at(j) != ' ') {
        theDisplay.at(i).at(j) = ' ';
    }

}

void TextDisplay::print(int i, bool isEffectBlind) {
    if (!isEffectBlind) {
        for (int j = 0; j < boardWidth; j++) {
        cout << theDisplay.at(i).at(j);
        }
    }
    else if (isEffectBlind) {
        if (i >= 2 && i <= 11) { 
            for (int j = 0; j < boardWidth; j++) {
                if (j >= 2 && j <= 8) {
                    cout << "?";
                }
                else 
                    cout << theDisplay.at(i).at(j);
            }
        }
        else {
            for (int j = 0; j < boardWidth; j++) {
                cout << theDisplay.at(i).at(j);
            }
        }
    }
}





