#include "Coordinates.h"

void Coords::setOverallIndex (int index) {
	overallIndex = index;
	systemCoords.first = overallIndex / CV::continentSize;
	systemCoords.second = overallIndex % CV::continentSize;

	userCoords.first = (overallIndex % CV::continentSize) + 1;
	userCoords.second = CV::continentSize - (overallIndex / CV::continentSize);
}

std::pair<int, int> Coords::getSystemCoords() {
	return systemCoords;
}

std::pair<int, int> Coords::getUserCoords() {
	return userCoords;
}

void Coords::printUserCoords() {
	std::cout << "(" << userCoords.first << ", " << userCoords.second << ")";
}

void Coords::setCoords(std::pair<int, int> systemCoordsArg,
	std::pair<int, int> userCoordsArg) {
	systemCoords = systemCoordsArg;
	userCoords = userCoordsArg;
}

//Gets passed user coords, translates them to system coords
std::pair<int, int> Coords::translateToSystemCoords(std::pair<int, int> userCoordsArg) {
	std::pair<int, int> returnSystemCoords;
	//Add implementation here

	return returnSystemCoords;
}

std::string Coords::getUserCoordsString() {
	return "(" + std::to_string(userCoords.first) + ", " + std::to_string(userCoords.second) + ")";
}

std::string Coords::getSystemCoordsString() {
	return "(" + std::to_string(systemCoords.first) + ", " + std::to_string(systemCoords.second) + ")";
}