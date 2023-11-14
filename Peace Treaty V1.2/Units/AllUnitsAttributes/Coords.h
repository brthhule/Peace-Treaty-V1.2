#ifndef COORDS_H
#define COORDS_H

#include <iostream>
#include <string>

#include "../Misc/INF.h"

using namespace INF;

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
	std::string
		getSystemCoordsString(),
		getUserCoordsString();

	std::pair<int, int> translateToSystemCoords(std::pair<int, int> userCoordsArg);

protected:
	std::pair<int, int>
		systemCoords,//row, column
		userCoords;//x, y

private:
	int overallIndex;
};

#endif COORDINATES_H