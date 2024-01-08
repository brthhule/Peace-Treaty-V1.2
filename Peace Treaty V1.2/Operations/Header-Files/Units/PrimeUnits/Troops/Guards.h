#include <iostream>
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include TROOP_UNITS_BASE_HEADER

class Guards : TroopUnitsBASE {
	Guards (int level, int baseHealth, int tier, std::array<int, 3> baseDamage, TROOP::TroopTypes thisType);
};