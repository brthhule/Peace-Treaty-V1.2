//CoordsBASE.h
//Base Class
//Extended by PrimeUnits

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
	CoordsBASE();
	~CoordsBASE(){}

	//----Setters--------------------------------------------------------------
	void
		setMapIndex(int mapIndex),
		setCoords(ipair systemCoords, ipair userCoords),
		setCoords(std::pair<const ipair&, const ipair&> coords);

	//----Printers-------------------------------------------------------------
	void printCoords(CoordsType type) const;

	//----Getters--------------------------------------------------------------
	ipair getCoords(CoordsType type) const;
	static ipair mapIndexToCoords(int mapIndex, CoordsType type);
	static ipair translateCoords(ipair coords, CoordsType currentType);

	static int coordsTomapIndex(ipair coords, CoordsType type);

	String
		getCoordsString(CoordsType type) const;

	///First one is SYSTEM, second is USER
	std::pair<const ipair&, const ipair&> getPairCoords() const;

protected:
	ipair
		systemCoords,//row, column
		userCoords;//x, y

private:
	int mapIndex;
};

}

#endif COORDINATES_H