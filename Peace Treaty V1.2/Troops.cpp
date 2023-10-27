#include "Troops.h"

Troops::Troops() {
	//Empty
}

std::array<int, 5> Troops::getAllOneTroop(CV::TROOPS type) {
	return *allTroops[type];
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
void Troops::mutateTroop(CV::MutateTroopType type, int troopIndex, std::array<int,5> amount, Quantity quant, CV::MutateDirection direction) {
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

