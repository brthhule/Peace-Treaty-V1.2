#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

#include "../Units/Provinces.h";
#include "../Misc/ConstValues.h"

using namespace CV;

class Map {
public:
	static void setMap();
	static void showMap();
	static void meat(int x, int y);
	static void printXAxis();
	Provinces* getProvince(int row, int column);
private:
	static std::vector <std::vector<Provinces>> map;
};
#endif