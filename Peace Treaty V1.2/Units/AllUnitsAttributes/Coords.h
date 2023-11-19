#ifndef COORDS_H
#define COORDS_H

#include <iostream>
#include <string>

#include "../Misc/INF.h"

using namespace INF;

class Coords
{
public:
	/*SYSTEM, USER*/
	static enum CoordsType { SYSTEM, USER };

	void
		setIndex(int index),
		printCoords(USER),
		setCoords(ipair systemCoords, ipair userCoords),
		printCoords(CoordsType type);

	ipair
		getCoords(CoordsType type);

	String
		getSystemCoordsString(),
		getUserCoordsString();

	ipair translateToSystemCoords(ipair userCoordsArg);

protected:
	ipair
		systemCoords,//row, column
		userCoords;//x, y

private:
	int index;
};

#endif COORDINATES_H