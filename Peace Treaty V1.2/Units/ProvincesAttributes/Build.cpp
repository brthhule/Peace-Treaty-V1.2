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
		if (enumArg == NULL) {
			int index = 0;
			for (int x = 0; x < 10; x++) {
				if (stringArg == BuildingStrings.at(x)) {
					index = x;
					break;
				}
			}

			return std::make_pair(stringArg, BuildingsEnum(index));
		}
	}
}