#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include BUILD_HEADER

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
		if (stringArg == "") {
			return std::make_pair(BuildingStrings.at(enumArg), enumArg);
		}

		if (enumArg != -1) {
			return std::make_pair("", 0);
		}

		for (int index = 0; index < 10; index++) {
			if (stringArg == BuildingStrings.at(index)) {
				return std::make_pair(stringArg, BuildingsEnum(index));
				break;
			}
		}
	}
}