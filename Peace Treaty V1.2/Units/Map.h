#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

#include "../Units/Provinces.h";
#include "../Misc/ConstValues.h"

using namespace CV;

class Map {
public:
	static void 
		setMap(),
		showMap(),
		meat(int x, int y),
		printXAxis(),
		updateTurnResources();

	
	static Provinces* getProvince(std::pair<int, int> coords);
protected:
	static std::vector <std::vector<Provinces>> map;
	static std::unordered_map <std::string, Provinces*> mapMap;
};
#endif