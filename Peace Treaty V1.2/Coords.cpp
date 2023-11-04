#include "Coords.h"

void Coords::setOverallIndex (int index) {
	//For debugging
	OF::debugFunction("Coords, OtherBuildingsToString");

	overallIndex = index;
	systemCoords.first = overallIndex / CV::continentSize;
	systemCoords.second = overallIndex % CV::continentSize;

	userCoords.first = (overallIndex % CV::continentSize) + 1;
	userCoords.second = CV::continentSize - (overallIndex / CV::continentSize);
}

std::pair<int, int> Coords::getSystemCoords() {
	//For debugging
	OF::debugFunction("Coords, getSystemCoords");

	return systemCoords;
}

std::pair<int, int> Coords::getUserCoords() {
	//For debugging
	OF::debugFunction("Coords, getUserCoords");

	return userCoords;
}

void Coords::printUserCoords() {
	//For debugging
	OF::debugFunction("Coords, printUserCoords");

	std::cout << "(" << userCoords.first << ", " << userCoords.second << ")";
}

void Coords::setCoords(std::pair<int, int> systemCoordsArg, std::pair<int, int> userCoordsArg) {
	//For debugging
	OF::debugFunction("Coords, setCoords");

	systemCoords = systemCoordsArg;
	userCoords = userCoordsArg;
}

//Gets passed user coords, translates them to system coords
std::pair<int, int> Coords::translateToSystemCoords(std::pair<int, int> userCoordsArg) {
	//For debugging
	OF::debugFunction("Coords, translateToSystemCoords");

	std::pair<int, int> returnSystemCoords;
	//Add implementation here

	return returnSystemCoords;
}

std::string Coords::getUserCoordsString() {
	//For debugging
	OF::debugFunction("Coords, getUserCoordsString");

	return "(" + std::to_string(userCoords.first) + ", " + std::to_string(userCoords.second) + ")";
}

std::string Coords::getSystemCoordsString() {
	//For debugging
	OF::debugFunction("Coords, getSystemCoordsString");

	return "(" + std::to_string(systemCoords.first) + ", " + std::to_string(systemCoords.second) + ")";
}