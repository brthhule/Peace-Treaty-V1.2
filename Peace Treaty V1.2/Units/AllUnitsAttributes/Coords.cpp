#include "Coords.h"

void Coords::setOverallIndex (int index) {
	//For debugging
	CV::debugFunction("Coords, OtherBuildingsToString");

	overallIndex = index;
	systemCoords.first = overallIndex / CV::continentSize;
	systemCoords.second = overallIndex % CV::continentSize;

	userCoords.first = (overallIndex % CV::continentSize) + 1;
	userCoords.second = CV::continentSize - (overallIndex / CV::continentSize);
}

std::pair<int, int> Coords::getSystemCoords() {
	//For debugging
	CV::debugFunction("Coords, getSystemCoords");

	return systemCoords;
}

std::pair<int, int> Coords::getUserCoords() {
	//For debugging
	CV::debugFunction("Coords, getUserCoords");

	return userCoords;
}

void Coords::printUserCoords() {
	//For debugging
	CV::debugFunction("Coords, printUserCoords");

	std::cout << "(" << userCoords.first << ", " << userCoords.second << ")";
}

void Coords::setCoords(std::pair<int, int> systemCoordsArg, std::pair<int, int> userCoordsArg) {
	//For debugging
	CV::debugFunction("Coords, setCoords");

	systemCoords = systemCoordsArg;
	userCoords = userCoordsArg;
}

//Gets passed user coords, translates them to system coords
std::pair<int, int> Coords::translateToSystemCoords(std::pair<int, int> userCoordsArg) {
	//For debugging
	CV::debugFunction("Coords, translateToSystemCoords");

	std::pair<int, int> returnSystemCoords;
	//Add implementation here

	return returnSystemCoords;
}

std::string Coords::getUserCoordsString() {
	//For debugging
	CV::debugFunction("Coords, getUserCoordsString");

	return "(" + std::to_string(userCoords.first) + ", " + std::to_string(userCoords.second) + ")";
}

std::string Coords::getSystemCoordsString() {
	//For debugging
	CV::debugFunction("Coords, getSystemCoordsString");

	return "(" + std::to_string(systemCoords.first) + ", " + std::to_string(systemCoords.second) + ")";
}