//Map.h
//Class
//Inherited by Participants

#ifndef MAP_H
#define MAP_H
#define MAP

#include <iostream>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include PROVINCES_HEADER
#include INF_HEADER

using namespace INF;

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
	static Provinces
		*getSystemProvince(std::pair<int, int> systemCoords),
		*getUserProvince(std::pair<int, int> userCoords);
METHODS END

VARIABLES START
	typedef std::vector <std::vector<Provinces*>> ProvincesVector;
	typedef std::unordered_map <std::string, Provinces*> ProvincesMap;

	static ProvincesVector map;
	static ProvincesMap mapMap;
VARIABLES END
};
#endif