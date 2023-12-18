//CoordsBASE.h
//Base Class
//Extended by AllUnits

#ifndef COORDS_BASE_H
#define COORDS_BASE_H

#include <iostream>
#include <string>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INF_HEADER					    //Namespace

using namespace INF;

class CoordsBASE {
public:
	CoordsBASE(){}
	~CoordsBASE(){}

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