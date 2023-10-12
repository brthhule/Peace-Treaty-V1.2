#ifndef COORDINATES_H
#define COORDINATES_H

#include <iostream>
#include "Misc/ConstValues.h"

using namespace CV;

class Coords
{
public:
	Coords(int index);
	std::pair<int, int> getSystemCoords();
	std::pair<int, int> getUserCoords();
private:
	std::pair<int, int> systemCoords;//row, column
	std::pair<int, int> userCoords;//x, y
	int overallIndex;
};

#endif COORDINATES_H