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

	c
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

	ipair tempPair = NULL;
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

//Gets user coords, translates them to system coords
ipair Coords::translateToSystemCoords(ipair userCoordsArg) {
	//For debugging
	INF::debugFunction("Coords, translateToSystemCoords");

	ipair returnSystemCoords;
	//Add implementation here

	return returnSystemCoords;
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