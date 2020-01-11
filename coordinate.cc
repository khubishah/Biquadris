#include "coordinate.h"

using namespace std;

Coordinate::Coordinate(int row, int col):row{row}, col{col}{};

bool Coordinate::operator==(const Coordinate& other) const{ 	
    return (row == other.row && col == other.col);
}

Coordinate& Coordinate::operator=(const Coordinate &other){ // makes coordinates of one cell equal to another
	row = other.row;
    col = other.col;
    return *this;
}

bool Coordinate::outofbound() { // true if it is out of bound else false
    if(this->row >= height || this->col >= width || this->row < 0 || this->col < 0) {
        return true;
    }
    else {
        return false;
    }
}








