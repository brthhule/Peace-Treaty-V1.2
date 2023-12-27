//CoordsBASE.h
//Base Class
//Extended by PrimeUnits

#ifndef COORDS_BASE_H
#define COORDS_BASE_H

#include <iostream>
#include <string>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INF_HEADER					    //Namespace

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
		setCoords(INF::ipair systemCoords, INF::ipair userCoords),
		setCoords(std::pair<const INF::ipair&, const INF::ipair&> coords);

	//----Printers-------------------------------------------------------------
	void printCoords(CoordsType type) const;

	//----Getters--------------------------------------------------------------
	INF::ipair getCoords(CoordsType type) const;
	static INF::ipair mapIndexToCoords(int mapIndex, CoordsType type);
	static INF::ipair translateCoords(INF::ipair coords, CoordsType currentType);

	static int coordsTomapIndex(INF::ipair coords, CoordsType type);

	std::string
		getCoordsString(CoordsType type) const;

	///First one is SYSTEM, second is USER
	std::pair<const INF::ipair&, const INF::ipair&> getPairCoords() const;

protected:
	INF::ipair 
		systemCoords,//row, column
		userCoords;//x, y

private:
	int mapIndex;
};

}

#endif COORDINATES_H