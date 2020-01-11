#ifndef __COORDINATE_H__
#define __COORDINATE_H__

class Coordinate {   
    //height and width of the board
    const int height = 18;
    const int width = 11; 
    public:
    int row = 0;
	int col = 0; 
    Coordinate(int row, int col);
    bool outofbound(); // checks if the coordinates are out of bound
    bool operator==(const Coordinate& other) const; // to check if two cells have equal coordinates
    Coordinate &operator=(const Coordinate &other); // copy assignment operator to copy coordinate from one to another	
};

#endif





