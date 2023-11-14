#include "Coords.h"

void Coords::setOverallIndex (int index) {
	//For debugging
	INF::debugFunction("Coords, OtherBuildingsToString");

	overallIndex = index;
	systemCoords.first = overallIndex / INF::continentSize;
	systemCoords.second = overallIndex % INF::continentSize;

	userCoords.first = (overallIndex % INF::continentSize) + 1;
	userCoords.second = INF::continentSize - (overallIndex / INF::continentSize);
}

std::pair<int, int> Coords::getSystemCoords() {
	//For debugging
	INF::debugFunction("Coords, getSystemCoords");

	return systemCoords;
}

std::pair<int, int> Coords::getUserCoords() {
	//For debugging
	INF::debugFunction("Coords, getUserCoords");

	return userCoords;
}

void Coords::printUserCoords() {
	//For debugging
	INF::debugFunction("Coords, printUserCoords");

	std::cout << "(" << userCoords.first << ", " << userCoords.second << ")";
}

void Coords::setCoords(std::pair<int, int> systemCoordsArg, std::pair<int, int> userCoordsArg) {
	//For debugging
	INF::debugFunction("Coords, setCoords");

	systemCoords = systemCoordsArg;
	userCoords = userCoordsArg;
}

//Gets passed user coords, translates them to system coords
std::pair<int, int> Coords::translateToSystemCoords(std::pair<int, int> userCoordsArg) {
	//For debugging
	INF::debugFunction("Coords, translateToSystemCoords");

	std::pair<int, int> returnSystemCoords;
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