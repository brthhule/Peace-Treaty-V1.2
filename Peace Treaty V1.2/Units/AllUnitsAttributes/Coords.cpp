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

ipair Coords::getSystemCoords() {
	//For debugging
	INF::debugFunction("Coords, getSystemCoords");

	return systemCoords;
}

ipair Coords::getUserCoords() {
	//For debugging
	INF::debugFunction("Coords, getUserCoords");

	return userCoords;
}

void Coords::printUserCoords() {
	//For debugging
	INF::debugFunction("Coords, printUserCoords");

	std::cout << "(" << userCoords.first << ", " << userCoords.second << ")";
}

void Coords::setCoords(ipair systemCoords, ipair userCoords) {
	//For debugging
	INF::debugFunction("Coords, setCoords");

	this->systemCoords = systemCoordsArg;
	this->userCoords = userCoordsArg;
}

//Gets passed user coords, translates them to system coords
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