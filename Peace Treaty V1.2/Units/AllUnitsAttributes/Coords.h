#ifndef COORDS_H
#define COORDS_H

#include <iostream>
#include <string>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"

#include INF_HEADER

using namespace INF;

class Coords
{
public:
	/*SYSTEM, USER*/
	enum CoordsType { SYSTEM, USER };

	void
		setIndex(int index),
		setCoords(ipair systemCoords, ipair userCoords),
		printCoords(CoordsType type);

	ipair
		getCoords(CoordsType type),
		indexToCoords(int index, CoordsType type),
		translateCoords(ipair coords, CoordsType currentType);

	int coordsToIndex(ipair coords, CoordsType type);

	String
		getSystemCoordsString(),
		getUserCoordsString();


protected:
	ipair
		systemCoords,//row, column
		userCoords;//x, y

private:
	int index;
};

#endif COORDINATES_H