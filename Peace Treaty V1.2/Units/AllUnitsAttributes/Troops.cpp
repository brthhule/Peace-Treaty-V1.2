#include "Troops.h"

Troops::Troops() {
	//For debugging
	INF::debugFunction("Troops, Troops");

	//Empty
}

std::array<int, 5> Troops::getAllOneTroopArray(INF::TroopCondition troopCondition, INF::TroopTypes type) {
	//For debugging
	INF::debugFunction("Troops, getAllOneTroopArray");

	return allTroopConditions.at(troopCondition.at(type));
}

int Troops::getAllOneTroopInt(INF::TroopCondition troopCondition, INF::TroopTypes type) {
	i5array tempArray = getAllOneTroopArray(troopCondition, type);
	INF::debugFunction("Troops, getAllOneTroopInt");

	int total = 0;
	for (int x : tempArray) {
		total += x;
	}

	return total;
}

i5array Troops::getGenericTroops(TroopCondition troopCondition) {
	i5array troopTotals = { 0,0,0,0,0 };

	for (int x = 0; x < 5; x++) {
		TroopTypes troopType = (TroopTypes)x;
		troopTotals.at(x) = Troops::getAllOneTroopInt(troopCondition, troopType);
	}

	return troopTotals;
}


//--------Troop Functions--------
//Return a troop by index or all troops-- done by type
std::array<int, 5> Troops::getTroop(INF::TroopCondition type, int troopIndex, Quantity amount) {
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
void Troops::mutateTroop(INF::TroopCondition troopCondition, TroopTypes troopType, std::array<int,5> amount, Quantity quant, INF::MutateDirection direction, int troopTier) {
	//For debugging
	INF::debugFunction("Troops, mutateTroop");

	std::array<i5array, 5> *troopConditionArray = allTroopConditions.at(troopCondition);
	i5array* troopTiers = troopConditionArray->at(troopType);

	int modifier = -1;

	if (direction == INCREASE) {
		modifier = 1;
	}
	
	switch (quant) {
		case SINGLE: {
			troopTiers->at(troopTier) += amount[0] * modifier;
			break;
		}
		case ALL: {
			for (int x = 0; x < 5; x++) {
				troopTiers->at(x) += amount.at(x);
			}
			break;
		}
	}

	return;
}

