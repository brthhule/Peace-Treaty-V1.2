#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include COORDS_BASE_HEADER

using namespace COORD;
using namespace INF;

void CoordsBASE::setMapIndex (int mapIndex) {
	//For debugging
	DEBUG_FUNCTION("Coords.cpp", "OtherBuildingsToString");

	this->mapIndex = mapIndex;

	//Set systemCoords
	systemCoords = std::make_pair(
		mapIndex / INF::continentSize, 
		mapIndex % INF::continentSize);

	//Set userCoords
	userCoords = std::make_pair(
		(mapIndex % INF::continentSize) + 1,
		INF::continentSize - (mapIndex / INF::continentSize));
}

CoordsBASE::CoordsBASE() {
	mapIndex = 0;
}

ipair CoordsBASE::getCoords(CoordsType type) const{
	DEBUG_FUNCTION("Coords.cpp", "getCoords");

	if (type == SYSTEM) { return systemCoords; }
	return userCoords;
}

void CoordsBASE::printCoords(CoordsType type) const {
	DEBUG_FUNCTION("Coords.cpp", "printCoords");

	ipair tempPair = userCoords;
	if (type == SYSTEM) { tempPair = systemCoords; }
	std::cout << "(" << tempPair.first << ", " << tempPair.second << ")";
}

void CoordsBASE::setCoords(ipair systemCoords, ipair userCoords) {
	//For debugging
	DEBUG_FUNCTION("Coords.cpp", "setCoords");

	this->systemCoords = systemCoords;
	this->userCoords = userCoords;
}

/*Translate coords of currentType to other type
If current type is SYSTEM, translate to USER, vice versa*/
ipair CoordsBASE::translateCoords(ipair coords, CoordsType currentType) {
	//For debugging
	DEBUG_FUNCTION("Coords.cpp", "translateCoords");

	int mapIndex = coordsTomapIndex(coords, currentType);

	if (currentType == SYSTEM) { return mapIndexToCoords(mapIndex, USER); }
	return mapIndexToCoords(mapIndex, SYSTEM);

}

std::string CoordsBASE::getCoordsString(CoordsType type) const {
	ipair coords = userCoords;
	if (type == SYSTEM) { coords = systemCoords; }

	return "(" + std::to_string(coords.first) + ", " + std::to_string(coords.second) + ")"; 
}

ipair CoordsBASE::mapIndexToCoords(int mapIndex, CoordsType type) {
	DEBUG_FUNCTION("Coords.cpp", "mapIndexToCoords");
	int row = 0, col = 0, x = 0, y = 0;

	if (type == SYSTEM) {
		row = mapIndex / continentSize;
		col = mapIndex % continentSize;
		return std::make_pair(row, col);
	}

	x = (mapIndex % continentSize) + 1;
	y = continentSize - (mapIndex / continentSize);
	return std::make_pair(x, y);
}

int CoordsBASE::coordsTomapIndex(ipair coords, CoordsType type) {
	DEBUG_FUNCTION("Coords.cpp", "coordsTomapIndex");
	if (type == SYSTEM) { return (coords.first * continentSize) + coords.second; }

	return (continentSize * (continentSize - coords.second)) + (coords.first - 1);
}

int COORD::getRandomCoordinate() {   
	//For debugging
	DEBUG_FUNCTION("Map.cpp", "getRandomCoordinate");
	return rand() % INF::continentSize; 
}

void CoordsBASE::setCoords(std::pair<const ipair&, const ipair&> coords) {  
	systemCoords = coords.first; 
	userCoords = coords.second;
} 

std::pair<const ipair&, const ipair&> CoordsBASE::getPairCoords() const {  
	return std::make_pair(systemCoords, userCoords); 
}