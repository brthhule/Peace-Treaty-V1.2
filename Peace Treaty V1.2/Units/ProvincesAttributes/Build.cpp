#include "Build.h"

namespace Build {
	/*"BARRACKS",
		"INFIRMARY",
		"LIBRARY",
		"WALL",
		"RESIDENCES" */
	CV::StringArray OtherBuildingsString = {
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
	CV::StringArray ResourceBuildingsString = {
		"FARM",
		"LUMBER_MILL",
		"QUARRY",
		"MINE",
		"CHURCH"
	};
}

std::string Build::OtherBuildingsToString(OtherBuildings arg) {
	//For debugging
	CV::debugFunction("Build, OtherBuildingsToString");

	return OtherBuildingsString[arg];
}

int Build::getOtherBuildingsStringIndex(std::string arg) {
	//For debugging
	CV::debugFunction("Build, getOtherBuildingsStringIndex");

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
	CV::debugFunction("Build, stringToOthersBuilding");

	return OtherBuildings(Build::getOtherBuildingsStringIndex(arg));
}


std::string Build::ResourceBuildingsToString(Build::ResourceBuildings arg) {
	//For debugging
	CV::debugFunction("Build, ResourceBuildingToString");

	return OtherBuildingsString[arg];
}

int Build::getResourceBuildingsStringIndex(std::string arg) {
	//For debugging
	CV::debugFunction("Build, getResourceBuildingsStringIndex");

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
	CV::debugFunction("Build, stringToResourceBuildings");

	return Build::ResourceBuildings(Build::getOtherBuildingsStringIndex(arg));
}

