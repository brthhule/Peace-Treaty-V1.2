#ifndef BUILD_H
#define BUILD_H

#include<iostream>
#include <array>

#include "..\..\..\..\..\Support\Paths.h"
#include INF_HEADER

namespace BUILD {
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
		OTHER_BUILDING_NAMES;

	extern INF::i5array RESOURCE_PRODUCTION;
}
#endif