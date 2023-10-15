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
//Return a troop by index or all troops-- done by type. Pass -1 for troopIndex to return all troops of a type
template<typename T>
T Troops::getTroop(CV::MutateTroopType type, int troopIndex, T data) {
	std::array<int*, 3> troop = { &troopsPresent[troopIndex], &troopsInjured[troopIndex], &troopsLost[troopIndex] };
	std::array<std::array<int, 5>*, 3> allTroops = { &troopsPresent, &troopsInjured, &troopsLost };
	T* troopPtr;

	if (troopIndex == -1) {
		troopPtr = allTroops[type];
	}
	else {
		troopPtr = troop[type];
	}
	return *troopPtr;
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

