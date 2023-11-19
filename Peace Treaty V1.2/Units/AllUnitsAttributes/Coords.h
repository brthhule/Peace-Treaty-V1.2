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
		setCoords(ipair systemCoords, ipair userCoords);

	ipair
		getSystemCoords(),
		getUserCoords();
	std::string
		getSystemCoordsString(),
		getUserCoordsString();

	ipair translateToSystemCoords(ipair userCoordsArg);

protected:
	ipair
		systemCoords,//row, column
		userCoords;//x, y

private:
	int overallIndex;
};

#endif COORDINATES_H