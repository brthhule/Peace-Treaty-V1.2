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
		printXAxis();

	Provinces* getProvince(int row, int column);
private:
	static std::vector <std::vector<Provinces>> map;
};
#endif