#include "..\..\..\..\..\Support\Paths.h"
#include ARCHERS_HEADER

Archers::Archers(int level, int baseHealth, int tier, std::array<int, 3> baseDamage, TROOP::TroopTypes thisType) : TroopUnitsBASE(level, baseHealth, tier, baseDamage, thisType) {

}