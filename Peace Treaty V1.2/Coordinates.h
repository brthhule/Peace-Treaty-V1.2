#ifndef COORDINATES_H
#define COORDINATES_H

#include <iostream>
#include "Misc/ConstValues.h"

using namespace CV;

class Coords
{
public:
	void
		setOverallIndex(int index),
		printUserCoords(),
		setCoords(
			std::pair<int, int> systemCoordsArg,
			std::pair<int, int> userCoordsArg);

	std::pair<int, int> 
		getSystemCoords(),
		getUserCoords();

	std::pair<int, int> translateSystemUser(std::pair<int, int> userCoordsArg);

protected:
	std::pair<int, int>
		systemCoords,//row, column
		userCoords;//x, y

private:
	int overallIndex;
};

#endif COORDINATES_H