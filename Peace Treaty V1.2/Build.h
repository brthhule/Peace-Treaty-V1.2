#ifndef BUILD_H
#define BUILD_H

#include<iostream>
#include <array>

namespace Build {
	enum OtherBuildings { BARRACKS, INFIRMARY, LIBRARY, WALL, RESIDENCES };
	enum ResourceBuildings { FARM, LUMBER_MILL, QUARRY, MINE, CHURCH };
	enum BuildingType { RESOURCE, OTHER };

	std::array<std::string, 5> 
		OtherBuildingsString = { "BARRACKS", "INFIRMARY", "LIBRARY", "WALL", "RESIDENCES" },
		ResourceBuildingsString = { "FARM", "LUMBER_MILL", "QUARRY", "MINE", "CHURCH" };

	//Converts from enum to string
	std::string 
		OtherBuildingsToString(Build::OtherBuildings arg),
		ResourceBuildingsToString(Build::ResourceBuildings arg);
	//Gets index of arg in list
	int getOtherBuildingsStringIndex(std::string arg),
		getResourceBuildingsStringIndex(std::string arg);
	//Cast the string into enum?
	OtherBuildings stringToOtherBuildings(std::string arg);
	ResourceBuildings stringToResourceBuildings(std::string arg);
	
}
#endif