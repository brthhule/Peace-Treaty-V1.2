#include "Build.h"

std::string Build::OtherBuildingsToString(OtherBuildings arg) {
	return OtherBuildingsString[arg];
}

int Build::getOtherBuildingsStringIndex(std::string arg) {
	for (int x = 0; x < OtherBuildingsString.size(); x++) {
		if (OtherBuildingsString[x] == arg) {
			return x;
		}
	}
	//Error case
	return -1;
}

Build::OtherBuildings Build::stringToOtherBuildings(std::string arg) {
	return OtherBuildings(Build::getOtherBuildingsStringIndex(arg));
}


std::string Build::ResourceBuildingsToString(Build::ResourceBuildings arg) {
	return OtherBuildingsString[arg];
}

int Build::getResourceBuildingsStringIndex(std::string arg) {
	for (int x = 0; x < OtherBuildingsString.size(); x++) {
		if (OtherBuildingsString[x] == arg) {
			return x;
		}
	}
	//Error case
	return -1;
}

Build::ResourceBuildings Build::stringToResourceBuildings(std::string arg) {
	return Build::ResourceBuildings(Build::getOtherBuildingsStringIndex(arg));
}

