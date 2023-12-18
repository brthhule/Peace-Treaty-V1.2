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

namespace COORD {

/*SYSTEM, USER*/
enum CoordsType { SYSTEM, USER };

///Get a random coordinate, used in Map creation?
int getRandomCoordinate();

class CoordsBASE {
public:
	//----Constructors---------------------------------------------------------
	CoordsBASE(){}
	~CoordsBASE(){}

	//----Setters--------------------------------------------------------------
	void
		setIndex(int index),
		setCoords(ipair systemCoords, ipair userCoords);

	//----Printers-------------------------------------------------------------
	void
		printCoords(CoordsType type);

	//----Getters--------------------------------------------------------------
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


}

#endif COORDINATES_H