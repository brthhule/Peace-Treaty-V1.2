#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include COMMANDERS_HEADER

using namespace COMM;

i5array Commanders::getAllOneTroopArray(TROOP::TroopCondition troopCondition, TROOP::TroopTypes type) {
	//For debugging
	DEBUG_FUNCTION("Troops, getAllOneTroopArray");

	return allTroopConditions.at(troopCondition.at(type));
}

int Commanders::getAllOneTroopInt(TROOP::TroopCondition troopCondition, TROOP::TroopTypes type) {
	i5array tempArray = getAllOneTroopArray(troopCondition, type);
	DEBUG_FUNCTION("Troops, getAllOneTroopInt");

	int total = 0;
	for (int x : tempArray) {
		total += x;
	}

	return total;
}

i5array Commanders::getGenericTroops(TroopCondition troopCondition) {
	i5array troopTotals = { 0,0,0,0,0 };

	for (int x = 0; x < 5; x++) {
		TROOP::TroopTypes troopType = (TROOP::TroopTypes)x;
		troopTotals.at(x) = getAllOneTroopInt(troopCondition, troopType);
	}

	return troopTotals;
}

//----Mutators----
//Change troops of type index at this unit by amount
void Commanders::mutateTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes troopType, i5array amount, Quantity quant, INF::MutateDirection direction, int troopTier) {
	//For debugging
	DEBUG_FUNCTION("Troops, mutateTroop");

	std::shared_ptr<troopConditionArray> troopArray = allTroopConditions.at(troopCondition);
	i5array* troopTiers = troopArray.get(troopType);

	int modifier = -1;

	if (direction == INCREASE) {
		modifier = 1;
	}

	switch (quant) {
		//Change one tier of specific troop type
		case SINGLE: {
			troopTiers->at(troopTier) += amount[0] * modifier;
			break;
		}
		//Change all tiers of a specific troop type
		case ALL: {
			for (int x = 0; x < 5; x++) {
				troopTiers->at(x) += amount.at(x);
			}
			break;
		}
	}

	return;
}

void Commanders::setBattleFormation(troopConditionArray troopArray) { 
	std::cout << "Welcome to the Battle Formation menu.\n";
	std::cout << "Please select a battle formation option: ";
	std::cout << "";
}

std::array<TROOP::troopConditionArray, 3> Commanders::getTroopsLists() {
	std::array<troopConditionArray, 3> returnArray = { troopsPresent, troopsInjured, troopsLost };
	return returnArray;
}

void Commanders::printTroopsPresent() {
	std::cout << "Troops present: \n";
	for (int troopType = 0; troopType < 5; troopType++) {
		std::cout << TROOP_NAMES << ": " << getAllOneTroopInt(REGULAR, TroopTypes(troopType));
	}
}