#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "coordinate.h"
#include "subject.h"
#include "info.h"

class Block; // forward declaration;

class Cell: public Subject<Info>{        
    char partofWhichShape = ' ';
    public: 
               
        Coordinate coordinate = Coordinate{3,0};
        // the block that a cell is part of
        Cell(char partofWhichShape, Coordinate coordinate);
        Coordinate getcoordinates() const; // gets the coordinate of the cell
        void setcoordinates(Coordinate &other); // sets the coordinate of the cell
        Cell& operator=(const Cell &other); // assignment operator
        Info getInfo() const override; // for observer pattern
        void setShape(char shape); // sets the shape of the cell
        char getShape(); // get the partofWhichShape of a cell
        
    
};

#endif







