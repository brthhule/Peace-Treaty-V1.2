#include <iostream>
#include "..\..\..\..\..\Support\Paths.h"

#include TROOP_UNITS_BASE_HEADER

class Infantry : TroopUnitsBASE {
	Infantry(int level, int baseHealth, int tier, std::array<int, 3> baseDamage, TROOP::TroopTypes thisType);
};