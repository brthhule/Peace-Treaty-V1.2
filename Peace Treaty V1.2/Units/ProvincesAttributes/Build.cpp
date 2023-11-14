#include "Build.h"

namespace Build {
	/*"BARRACKS",
		"INFIRMARY",
		"LIBRARY",
		"WALL",
		"RESIDENCES" */
	INF::s5array OtherBuildingsString = {
		"BARRACKS",
		"INFIRMARY",
		"LIBRARY",
		"WALL",
		"RESIDENCES"
	};

	/*"FARM",
		"LUMBER_MILL",
		"QUARRY",
		"MINE",
		"CHURCH" */
	INF::s5array ResourceBuildingsString = {
		"FARM",
		"LUMBER_MILL",
		"QUARRY",
		"MINE",
		"CHURCH"
	};
}

std::string Build::OtherBuildingsToString(OtherBuildings arg) {
	//For debugging
	INF::debugFunction("Build, OtherBuildingsToString");

	return OtherBuildingsString[arg];
}

int Build::getOtherBuildingsStringIndex(std::string arg) {
	//For debugging
	INF::debugFunction("Build, getOtherBuildingsStringIndex");

	for (int x = 0; x < (signed) OtherBuildingsString.size(); x++) {
		if (OtherBuildingsString[x] == arg) {
			return x;
		}
	}
	//Error case
	return -1;
}

Build::OtherBuildings Build::stringToOtherBuildings(std::string arg) {
	//For debugging
	INF::debugFunction("Build, stringToOthersBuilding");

	return OtherBuildings(Build::getOtherBuildingsStringIndex(arg));
}


std::string Build::ResourceBuildingsToString(Build::ResourceBuildings arg) {
	//For debugging
	INF::debugFunction("Build, ResourceBuildingToString");

	return OtherBuildingsString[arg];
}

int Build::getResourceBuildingsStringIndex(std::string arg) {
	//For debugging
	INF::debugFunction("Build, getResourceBuildingsStringIndex");

	for (int x = 0; x < (signed) OtherBuildingsString.size(); x++) {
		if (OtherBuildingsString[x] == arg) {
			return x;
		}
	}
	//Error case
	return -1;
}

Build::ResourceBuildings Build::stringToResourceBuildings(std::string arg) {
	//For debugging
	INF::debugFunction("Build, stringToResourceBuildings");

	return Build::ResourceBuildings(Build::getOtherBuildingsStringIndex(arg));
}

