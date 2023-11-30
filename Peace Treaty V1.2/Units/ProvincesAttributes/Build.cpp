#include "Build.h"

namespace BUILD {
	std::pair<std::string, BuildingsEnum> translateEnumString(std::string stringArg, BuildingsEnum enumArg) {
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

		if (stringArg == NULL) {
			return std::make_pair(BuildingStrings.at(enumArg), enumArg);
		}

		if (enumArg != NULL) {
			return;
		}

		for (int index = 0; index < 10; index++) {
			if (stringArg == BuildingStrings.at(x)) {
				return std::make_pair(stringArg, BuildingsEnum(index));
				break;
			}
		}
	}
}