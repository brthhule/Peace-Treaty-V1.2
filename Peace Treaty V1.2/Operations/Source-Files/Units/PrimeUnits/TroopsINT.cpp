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

i5array Commanders::getArrayOfSumsOfTiersOfAllTroops(TroopCondition troopCondition) {
	i5array troopTotals = { 0,0,0,0,0 };

	for (int x = 0; x < 5; x++) {
		TROOP::TroopTypes troopType = (TROOP::TroopTypes)x;
		troopTotals.at(x) = getSumOfTiersOfTroop(troopCondition, troopType);
	}

	return troopTotals;
}

//----Mutators----
//Change troops of type index at this unit by amount
void Commanders::mutateTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes troopType, troopsArray amount, Quantity quant, INF::MutateDirection direction, int troopTier) {
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
				troopTiers->at(troopTier).push_back(amount.at(troopType).at(troopTier).at(0));
				break;
			} 

			oneTier* tiers = &troopTiers->at(troopTier);
			tiers->erase(tiers->begin() + (tiers->size() - amount.at(troopType).at(troopTier).size()));
			break;
		}
		//Change all tiers of a specific troop type
		case ALL: {
			if (direction == INCREASE) {
				for (int troopTypeVar = 0; troopTypeVar < 5; troopTypeVar++) {
					for (int tierNum = 0; tierNum < 5; tierNum++) {
						for (int tierSize = 0; tierSize < amount.at(troopType).at(tierNum).size(); tierSize++) {
							troopConditions.at(troopCondition).at(troopTypeVar).at(tierNum).push_back(amount.at(troopTypeVar).at(tierNum).at(tierSize));
						}
					}
				}
				break;
			}
			for (int troopTypeVar = 0; troopTypeVar < 5; troopTypeVar++) {
				for (int tierNum = 0; tierNum < 5; tierNum++) {
					for (int tierSize = 0; tierSize < amount.at(troopType).at(tierNum).size(); tierSize++) {
						troopConditions.at(troopCondition).at(troopTypeVar).at(tierNum).erase(amount.at(troopTypeVar).at(tierNum).begin() + (troopConditions.at(troopCondition).at(troopTypeVar).at(tierNum).size() - amount.at(troopTypeVar).at(tierNum).size()));
					}
				}
			}
			break;
		}
	}

	return;
}

void Commanders::setBattleFormation(troopsArray troopArray) { 
	std::cout << "Welcome to the Battle Formation menu.\n";
	std::string formationType = Input::getInputText("Pleae select a battle formation option (ROW/COLUMN): ", { "ROW", "COLUMN" });
	std::string formationLane = "row";
	if (formationType.at(0) == 'C') { formationLane = "column"; }

	std::unordered_map<TroopTypes, int> things;
	std::array<TroopTypes, 5> formationLanes = {};
	for (int x = 0; x < 5; x++) {
		std::string prompt = "What " + formationLane + " do you want to place " + TROOP::TROOP_NAMES.at(x) + "? ";
		std::string answer = getInputText("", { "1", "2", "3", "4", "5" });
		if (formationLanes.at(std::stoi(answer)) != NULL) {
			std::cout << "This lane is already taken... please try again\n";
			x--;
			continue;
		}

		formationLanes.at(x) == TroopTypes(std::stoi(answer));
	}
	

	//Fill appropriate rows/colummns with their respective amounts ????
}

std::array<troopsArray, 3> &Commanders::getTroopConditions() {
	return troopConditions;
}

void Commanders::printTroopsPresent() {
	std::cout << "Troops present: \n";
	for (int troopType = 0; troopType < 5; troopType++) {
		std::cout << TROOP::TROOP_NAMES.at(troopType) << ": " << getSumOfTiersOfTroop(REGULAR, TroopTypes(troopType));
	}
}