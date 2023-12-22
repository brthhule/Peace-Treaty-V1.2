#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include COMMANDERS_HEADER

using namespace COMM;
using namespace TROOP;

tiersArray& Commanders::getAllTiersOfTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes type) {
	//For debugging
	DEBUG_FUNCTION("TroopsINT.cpp", "getAllTiersOfTroop");
	tiersArray *condition = &troopConditions.at(troopCondition).at(type);

	return *condition;
}

int Commanders::getSumOfTiersOfTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes type) {
	DEBUG_FUNCTION("Troops.cpp", "getSumOfTiersOfTroop");
	tiersArray tempArray = getAllTiersOfTroop(troopCondition, type);

	int total = 0;
	for (int index = 0; index < 5; index++) {
		oneTier foo = tempArray.at(index);
		total += foo.size();
	}

	return total;
}

i5array Commanders::getGenericTroops(TroopCondition troopCondition) {
	i5array troopTotals = { 0,0,0,0,0 };

	for (int x = 0; x < 5; x++) {
		TROOP::TroopTypes troopType = (TROOP::TroopTypes)x;
		troopTotals.at(x) = getSumOfTiersOfTroop(troopCondition, troopType);
	}

	return troopTotals;
}

//----Mutators----
//Change troops of type index at this unit by amount
void Commanders::mutateTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes troopType, troopsArray amountArrays, Quantity quant, INF::MutateDirection direction, int troopTier) {
	//For debugging
	DEBUG_FUNCTION("Troops.cpp", "mutateTroop");

	std::shared_ptr<troopsArray> troopArray = std::make_shared<troopsArray>(troopConditions.at(troopCondition));
	tiersArray* troopTiers = &troopArray->at(troopType);

	int modifier = -1;

	if (direction == INCREASE) {
		modifier = 1;
	}

	switch (quant) {
		//Change one tier of specific troop type
		case SINGLE: {
			if (direction == INCREASE) {
				troopTiers->at(troopTier).push_back(amountArrays.at(troopType).at(troopTier).at(0));
			}
			
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
}

std::array<COMM::troopConditionArray, 3> &Commanders::getAllTroopConditions() {
	return allTroopConditions;
}

void Commanders::printTroopsPresent() {
	std::cout << "Troops present: \n";
	for (int troopType = 0; troopType < 5; troopType++) {
		std::cout << TROOP::TROOP_NAMES.at(troopType) << ": " << getSumOfTiersOfTroop(REGULAR, TroopTypes(troopType));
	}
}