#include "Coords.h"

void Coords::setIndex (int index) {
	//For debugging
	INF::debugFunction("Coords, OtherBuildingsToString");

	this->index = index;

	//Set systemCoords
	systemCoords = std::make_pair(
		index / INF::continentSize, 
		index % INF::continentSize);

	//Set userCoords
	userCoords = std::make_pair(
		(index % INF::continentSize) + 1,
		INF::continentSize - (index / INF::continentSize));
}

ipair Coords::getCoords(CoordsType type) {
	INF::debugFunction("Coords, getCoords");

	std::pair<int, int> tempPair;
	switch (type) {
	case SYSTEM:
		tempPair = systemCoords;
		break;
	case USER:
		tempPair = userCoords;
		break;
	}

	return tempPair;
}

void Coords::printCoords(CoordsType type) {
	INF::debugFunction("Coords, printCoords");

	ipair tempPair;
	switch (type) {
	case SYSTEM:
		tempPair = systemCoords;
		break;
	case USER:
		tempPair = userCoords;
		break;
	}

	std::cout << "(" << tempPair.first << ", " << tempPair.second << ")";
}

void Coords::setCoords(ipair systemCoords, ipair userCoords) {
	//For debugging
	INF::debugFunction("Coords, setCoords");

	this->systemCoords = systemCoords;
	this->userCoords = userCoords;
}

/*Translate coords of currentType to other type
If current type is SYSTEM, translate to USER, vice versa*/
ipair Coords::translateCoords(ipair coords, CoordsType currentType) {
	//For debugging
	INF::debugFunction("Coords, translateCoords");

	int index = coordsToIndex(coords, currentType);

	switch (currentType) {
		case SYSTEM:
			return indexToCoords(index, USER);
		case USER:
		default:
			return indexToCoords(index, SYSTEM);
	}
	
}

std::string Coords::getUserCoordsString() {
	//For debugging
	INF::debugFunction("Coords, getUserCoordsString");

	return "(" + std::to_string(userCoords.first) + ", " + std::to_string(userCoords.second) + ")";
}

std::string Coords::getSystemCoordsString() {
	//For debugging
	INF::debugFunction("Coords, getSystemCoordsString");

	return "(" + std::to_string(systemCoords.first) + ", " + std::to_string(systemCoords.second) + ")";
}

ipair Coords::indexToCoords(int index, CoordsType type) {
	INF::debugFunction("Coords, indexToCoords");
	int row = 0, col = 0, x = 0, y = 0;

	switch (type) {
		case SYSTEM:
			row = index / continentSize;
			col = index % continentSize;
			return std::make_pair(row, col);

			//Use this for "initialization of 'row' is skipped by 'case' label" error
			break;
		case USER:
		default:
			x = (index % continentSize) + 1;
			y = continentSize - (index / continentSize);
			return std::make_pair(x, y);
			break;
	}
}

int Coords::coordsToIndex(ipair coords, CoordsType type) {
	INF::debugFunction("Coords, coordsToIndex");
	switch (type) {
		case SYSTEM:
			return (coords.first * continentSize) + coords.second;
		case USER:
		default:
			return (continentSize * (continentSize - coords.second)) +
				(coords.first - 1);
	}
}