//Map.h
//Class
//Inherited by Participants

#ifndef MAP_H
#define MAP_H
#define MAP

#include <iostream>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER
#include INF_HEADER

using namespace INF;
using namespace PROV;

BASE_CLASS
class Map {
public:
METHODS START
	CONSTRUCTOR
	Map();

	GETTER SETTER CALCULATE
	static void 
		setMap(),
		showMap(),
		meat(int x, int y),
		printXAxis(),
		updateTurnResources();

	GETTER
	static provSPTR 
		getSystemProvince(ipair systemCoords),
		getUserProvince(ipair userCoords);
METHODS END

VARIABLES START
	typedef std::unordered_map <std::string, provSPTR> ProvincesMap;
	typedef std::vector <std::vector<provSPTR>> ProvincesVector;

	static ProvincesVector map;
	static ProvincesMap mapMap;
VARIABLES END
};
#endif