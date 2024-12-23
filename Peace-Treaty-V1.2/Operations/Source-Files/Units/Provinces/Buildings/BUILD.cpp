#include "..\..\..\..\..\Support\Paths.h"
#include BUILD_HEADER

using namespace INF;

namespace BUILD {
	std::array<std::string, 10> BuildingStrings = {
			"FARM",
			"LUMBER_MILL",
			"QUARRY",
			"MINE",
			"CHURCH",
			"BARRACKS",
			"INFIRMARY",
			"LIBRARY",
			"WALL",
			"RESIDENCES"
	};
	/*
	* Null setting for stringArg is ""
	* Null setting for enumArg is 0
	*/
	std::pair<std::string, BuildingsEnum> translateEnumString (std::string stringArg, BuildingsEnum enumArg) {
		if (stringArg == "") { return std::make_pair(BuildingStrings.at(enumArg), enumArg); }

		if (enumArg != -1) { return std::make_pair("", FARM); }

		for (int index = 0; index < 10; index++) {
			if (stringArg == BuildingStrings.at(index)) {
				return std::make_pair(stringArg, BuildingsEnum(index));
				break;
			}
		}

		//Not all control paths return a value
		return std::make_pair("", FARM); 
	}

	/*RESOURCE_PRODUCTION = 5, 4, 3, 2, 1 */
	i5array RESOURCE_PRODUCTION = { 5,4,3,2,1 };

	/*RESOURCE_BUILDING = Farm, Lumber Mill, Quarry, Mine, Church*/
	s5array RESOURCE_BUILDING_NAMES = {
		"Farm",
		"Lumber Mill",
		"Quarry",
		"Mine",
		"Church"
	};

	/*OTHER_BUILDING = Barracks, Infirmary, Library, Wall, Residences*/
	s5array OTHER_BUILDING_NAMES = {
		"Barracks",
		"Infirmary",
		"Library",
		"Wall",
		"Residences"
	};
}