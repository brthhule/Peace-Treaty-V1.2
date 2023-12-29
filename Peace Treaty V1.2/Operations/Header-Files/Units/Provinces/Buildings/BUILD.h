#ifndef BUILD_H
#define BUILD_H

#include<iostream>
#include <array>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include INF_HEADER

namespace BUILD {
	/*FARM, 
	LUMBER_MILL,
	QUARRY, 
	MINE,
	CHURCH 
	
	BARRACKS,
	INFIRMARY,
	LIBRARY,
	WALL,
	RESIDENCES*/
	enum BuildingsEnum {
		FARM, 
		LUMBER_MILL,
		QUARRY, 
		MINE,
		CHURCH,
		BARRACKS,
		INFIRMARY,
		LIBRARY,
		WALL,
		RESIDENCES
	};

	extern std::array<std::string, 10> BuildingStrings;

	/*RESOURCE, 
	OTHER */
	enum BuildingType { 
		RESOURCE, 
		OTHER 
	};


	//Conversions
	std::pair<std::string, BuildingsEnum> translateEnumString(std::string stringArg, BuildingsEnum enumArg);

	extern INF::s5array
		RESOURCE_BUILDING_NAMES,
		OTHER_BUILDING_NAMES,
		RESOURCE_NAMES,
		RESOURCE_PRODUCTION;
}
#endif