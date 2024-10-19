#include "..\..\..\..\..\Support\Paths.h"
#include CAVALRY_HEADER

Cavalry::Cavalry(int level, int baseHealth, int tier, std::array<int, 3> baseDamage, TROOP::TroopTypes thisType) : TroopUnitsBASE(level, baseHealth, tier, baseDamage, thisType) {

}