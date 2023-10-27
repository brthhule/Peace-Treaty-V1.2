#include "Troops.h"

Troops::Troops() {
	//Empty
}

std::array<int, 5> Troops::getAllOneTroop(CV::TROOPS type) {
	return *allTroops[type];
}

void Troops::mutateTroop(CV::TROOPS type, int level, CV::MutateDirection) {

}


//--------Troop Functions--------
//Return a troop by index or all troops-- done by type
std::array<int, 5> Troops::getTroop(CV::MutateTroopType type, int troopIndex, Quantity amount) {

	std::array<int, 5> troopCopy;

	if (amount == SINGLE) {
		troopCopy = *allTroopTypes[type];
		troopCopy[0] = troopCopy[troopIndex];
		return troopCopy;
	}
	
	return *allTroopTypes[type];
}

//----Mutators----
//Change troops of type index at this unit by amount
template<typename T>
T Troops::mutateTroop(CV::MutateTroopType type, int troopIndex, T amount, CV::MutateDirection direction) {
	T* troopPtr;
	std::array<int*, 3> troop = { &troopsPresent[troopIndex], &troopsInjured[troopIndex], &troopsLost[troopIndex] };
	std::array<std::array<int, 5>*, 3> allTroops = { &troopsPresent, &troopsInjured, &troopsLost };

	if constexpr (std::is_same_v<T, int>) {
		troopPtr = troopTypes[type];

		if (direction) {
			troopPtr += amount;
			delete troopPtr;
			return;
		}
		troopPtr -= amount;
		delete troopPtr;
		return;
	}
	else if (constexpr (std::is_same_v < T, std::array<int, 5>)) {
		troopPtr = allTroops[type];
		*troopPtr = OF::modifyArray(*troopsPtr, amounts, direction);
		delete troopPtr;
		return;
	}
}

