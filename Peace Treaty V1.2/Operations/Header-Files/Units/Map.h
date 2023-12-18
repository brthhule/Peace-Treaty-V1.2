//Map.h
//Base Class
//Inherited by Participants

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER				//Composition
#include INF_HEADER						//Utility

using namespace INF;
using namespace PROV;
using namespace COORD;

/*TODO
* Potentially implement lamda in showMap();
*/
class Map {
public:
	//----Constructors---------------------------------------------------------
	Map() {}
	~Map(){}

	///Creates the map
	static void setMap();
	///Shows the map
	static void showMap();

	///Takes a coordinate, assigns the proper map symbol and color, prints
	static void meat(int x, int y);
	///Auxiliary method of showMap(), self explanatory
	static void printXAxis();
	///Iterate through all the provinces and update resource amounts
	static void updateTurnResources();

	static provSPTR getProvince(CoordsType typeWant, CoordsType coordsType, ipair coords);
	static provSPTR getSystemProvince(ipair systemCoords);
	static provSPTR getUserProvince(ipair userCoords);
	
	typedef std::unordered_map <std::string, provSPTR> ProvincesMap;
	typedef std::vector <std::vector<provSPTR>> ProvincesVector;

	static ProvincesVector map;
	static ProvincesMap mapMap;
};
#endif