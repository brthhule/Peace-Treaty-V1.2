#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

#include "../Units/Provinces.h"

#include "../Misc/CV.h"

using namespace CV;

class Map {
public:
	Map();

	static void 
		setMap(),
		showMap(),
		meat(int x, int y),
		printXAxis(),
		updateTurnResources();

	
	Provinces
		*getSystemProvince(std::pair<int, int> systemCoords),
		*getUserProvince(std::pair<int, int> userCoords);


	typedef std::vector <std::vector<Provinces*>> ProvincesVector;
	typedef std::unordered_map <std::string, Provinces*> ProvincesMap;

	static ProvincesVector map;
	static ProvincesMap mapMap;
};
#endif