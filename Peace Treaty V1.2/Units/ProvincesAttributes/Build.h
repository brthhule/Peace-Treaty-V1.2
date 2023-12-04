#ifndef BUILD_H
#define BUILD_H

#include<iostream>
#include <array>

#include "../Misc/INF.h"
#include "../Misc/INF.h"



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
	
}
#endif