#include "cell.h"
#include "coordinate.h"

using namespace std;

 Cell::Cell(char partofWhichShape, Coordinate coordinate): partofWhichShape{partofWhichShape},coordinate{coordinate} {}

void Cell::setcoordinates(Coordinate& other) { // sets coordinate of a cell to the given value
	this->coordinate = other;
}

 Coordinate Cell::getcoordinates() const{ // gets the coordinate of a cell
	return coordinate;
}

Info Cell::getInfo() const{ // gets the coordinate and the type of the cell
	return Info{coordinate, partofWhichShape};
}

Cell& Cell::operator=(const Cell &other){ // cell copy assignment operator
	this->partofWhichShape = other.partofWhichShape;
	this->coordinate = other.coordinate;
	
	return *this;
}

void Cell::setShape(char shape) { // sets the shape of the cell
	this->partofWhichShape = shape;
}

char Cell::getShape() { // gets the shape of the cell
	return partofWhichShape;
}












