#include "Coordinates.h"

Coords::Coords(int index) {
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