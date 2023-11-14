#include "Troops.h"

Troops::Troops() {
	//For debugging
	INF::debugFunction("Troops, Troops");

	//Empty
}

std::array<int, 5> Troops::getAllOneTroop(INF::TROOPS type) {
	//For debugging
	INF::debugFunction("Troops, getAllOneTroop");

	return *allTroops[type];
}



//--------Troop Functions--------
//Return a troop by index or all troops-- done by type
std::array<int, 5> Troops::getTroop(INF::MutateTroopType type, int troopIndex, Quantity amount) {
	//For debugging
	INF::debugFunction("Troops, getTroop");

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
void Troops::mutateTroop(INF::MutateTroopType type, int troopIndex, std::array<int,5> amount, Quantity quant, INF::MutateDirection direction) {
	//For debugging
	INF::debugFunction("Troops, mutateTroop");

	int modifier = -1;

	if (direction == INCREASE) {
		modifier = 1;
	}
	
	switch (quant) {
		case SINGLE: {
			allTroopTypes[type]->at(troopIndex) += amount[0] * modifier;
			break;
		}
		case ALL: {
			for (int x = 0; x < 5; x++) {
				allTroopTypes[type]->at(troopIndex) += amount[x];
			}
			break;
		}
	}
}

