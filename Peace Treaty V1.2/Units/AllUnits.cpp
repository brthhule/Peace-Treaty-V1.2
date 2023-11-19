#include "AllUnits.h"

//----Constructors----
//One param overloaded Constructor
AllUnits::AllUnits(int participantIndexArg) {
	//For debugging
	INF::debugFunction("AllUnits, AllUnits (1 Param)");

	switch (participantIndexArg) {
		case -1:
			canSelectThisUnit = false;
			break;
		default:
			canSelectThisUnit = true;
			for (int x = 0; x < 5; x++) {
				resourcesPresent[x] = initialStats[x];
				troopsPresent[x] = 0;
				troopsInjured[x] = 0;
			}
			break;
	}

	participantIndex = participantIndexArg;
	foodConsumption = 0;
	unitLevel = 0;
	combatPower = 0;
	totalTroops = 0;
	resourcesPresent = { 0,0,0,0,0 };
	initialStats = { 5,4,3,2,1 };
	allTroopConditions = { 
		&troopsPresent,
		&troopsInjured,
		&troopsLost 
	}
}

//Default Constructor
AllUnits::AllUnits() {
	//For debugging
	INF::debugFunction("AllUnits, AllUnits (0 Param)");

	AllUnits(-1);
};


void AllUnits::printTroopsPresent() {
	i5array troopsPresent = this->getGenericTroops(REGULAR);
	for (int x = 0; x < 5; x++) {
		std::cout << TROOP_NAMES.at(x) << ": " << troopsPresent.at(x) << std::endl;
	}
}

int AllUnits::getCP() {
	//For debugging
	INF::debugFunction("AllUnits, getCP");

	combatPower = 0;
	for (int x = 0; x < 5; x++) {
		combatPower += troopsPresent[x] * INF::TROOPS_CP[x];
	}
	return combatPower;
}

int AllUnits::getParticipantIndex() {
	//For debugging
	INF::debugFunction("AllUnits, getParticipantIndex");

	return participantIndex;
}

void AllUnits::printResources() {
	//For debugging
	INF::debugFunction("AllUnits, printResources");

	std::cout << "Resources currently present in this " << type << ": \n";
	INF::addColor(INF::BLUE);
	printResources(resourcesPresent);
	INF::addColor(INF::RESET);
}

std::string AllUnits::getUnitName() {
	//For debugging
	INF::debugFunction("AllUnits, getUnitName");

	return unitName;
}
void AllUnits::changeUnitName(std::string name) {
	//For debugging
	INF::debugFunction("AllUnits, changeUnitName");

	unitName = name;
}

//Mutator Functions
int AllUnits::getFoodConsumption() {
	//For debugging
	INF::debugFunction("AllUnits, getFoodConsumption");

	return foodConsumption;
}
int AllUnits::getResource(int resourceIndex) {
	//For debugging
	INF::debugFunction("AllUnits, getResource");

	return resourcesPresent[resourceIndex];
}
void AllUnits::modifySpecificResource(int index, int amount, bool isAdd) {
	//For debugging
	INF::debugFunction("AllUnits, modifySpecificResources");

	if (isAdd)
		resourcesPresent[index] += amount;
	else
		resourcesPresent[index] -= amount;
}

void AllUnits::modifyResources(std::array<int, 5> resourcesArray, bool isAdd) {
	//For debugging
	INF::debugFunction("AllUnits, mdofiyResources");

	INF::modifyArray(resourcesPresent, resourcesArray, isAdd);
}

int AllUnits::getLevel() {
	//For debugging
	INF::debugFunction("AllUnits, getLevel");

	return unitLevel;
}

std::array<int, 5> AllUnits::getAllResources() {
	//For debugging
	INF::debugFunction("AllUnits, getAllResources");

	return resourcesPresent;
}

void AllUnits::changeParticipantIndex(int number) {
	//For debugging
	INF::debugFunction("AllUnits, changeParticipantIndex");

	participantIndex = number;
}

void AllUnits::printResources(std::array<int, 5> resourcesArray) {
	//For debugging
	INF::debugFunction("AllUnits, printResources");

	for (int x = 0; x < 5; x++) {
		std::cout << "- " << INF::RESOURCE_NAMES.at(x) << ": " << resourcesArray.at(x) << std::endl;
	}
		

	std::cout << std::endl;
}


std::array<int, 5> AllUnits::getAllOneTroopArray(INF::TroopCondition troopCondition, INF::TroopTypes type) {
	//For debugging
	INF::debugFunction("Troops, getAllOneTroopArray");

	return allTroopConditions.at(troopCondition.at(type));
}

int AllUnits::getAllOneTroopInt(INF::TroopCondition troopCondition, INF::TroopTypes type) {
	i5array tempArray = getAllOneTroopArray(troopCondition, type);
	INF::debugFunction("Troops, getAllOneTroopInt");

	int total = 0;
	for (int x : tempArray) {
		total += x;
	}

	return total;
}

i5array AllUnits::getGenericTroops(TroopCondition troopCondition) {
	i5array troopTotals = { 0,0,0,0,0 };

	for (int x = 0; x < 5; x++) {
		TroopTypes troopType = (TroopTypes)x;
		troopTotals.at(x) = Troops::getAllOneTroopInt(troopCondition, troopType);
	}

	return troopTotals;
}


//--------Troop Functions--------
//Return a troop by index or all troops-- done by type
std::array<int, 5> AllUnits::getTroop(INF::TroopCondition type, int troopIndex, Quantity amount) {
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
void AllUnits::mutateTroop(INF::TroopCondition troopCondition, TroopTypes troopType, std::array<int, 5> amount, Quantity quant, INF::MutateDirection direction, int troopTier) {
	//For debugging
	INF::debugFunction("Troops, mutateTroop");

	std::array<i5array, 5>* troopConditionArray = allTroopConditions.at(troopCondition);
	i5array* troopTiers = troopConditionArray->at(troopType);

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

void AllUnits::setBattleFormation(std::array<) {
	std::cout << "Welcome to the Battle Formation menu.\n";
	std::cout << "Please select a battle formation option: ";
	std::cout << ""
}