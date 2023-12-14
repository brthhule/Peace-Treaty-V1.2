#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include ALL_UNITS_HEADER

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

const int& AllUnits::getCP() {
	//For debugging
	INF::debugFunction("AllUnits, getCP");

	combatPower = 0;
	for (int x = 0; x < 5; x++) {
		combatPower += troopsPresent[x] * INF::Troops_CP[x];
	}
	return combatPower;
}

const int& AllUnits::getParticipantIndex() {
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
const int& AllUnits::getFoodConsumption() {
	//For debugging
	INF::debugFunction("AllUnits, getFoodConsumption");

	return foodConsumption;
}
const int& AllUnits::getResource(int resourceIndex) {
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

void AllUnits::modifyResources(i5array resourcesArray, INF::MutateDirection direction) {
	//For debugging
	INF::debugFunction("AllUnits, mdofiyResources");

	resourcesPresent = INF::mutateArray(resourcesPresent, resourcesArray, direction);
}

const int& AllUnits::getLevel() {
	//For debugging
	INF::debugFunction("AllUnits, getLevel");

	return unitLevel;
}

i5array AllUnits::getAllResources() {
	//For debugging
	INF::debugFunction("AllUnits, getAllResources");

	return resourcesPresent;
}

void AllUnits::changeParticipantIndex(int number) {
	//For debugging
	INF::debugFunction("AllUnits, changeParticipantIndex");

	participantIndex = number;
}

void AllUnits::printResources(i5array resourcesArray) {
	//For debugging
	INF::debugFunction("AllUnits, printResources");

	for (int x = 0; x < 5; x++) {
		std::cout << "- " << INF::RESOURCE_NAMES.at(x) << ": " << resourcesArray.at(x) << std::endl;
	}
		

	std::cout << std::endl;
}


i5array AllUnits::getAllOneTroopArray(INF::TroopCondition troopCondition, Troops::TroopTypes type) {
	//For debugging
	INF::debugFunction("Troops, getAllOneTroopArray");

	return allTroopConditions.at(troopCondition.at(type));
}

int AllUnits::getAllOneTroopInt(INF::TroopCondition troopCondition, Troops::TroopTypes type) {
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
		Troops::TroopTypes troopType = (Troops::TroopTypes)x;
		troopTotals.at(x) = getAllOneTroopInt(troopCondition, troopType);
	}

	return troopTotals;
}

//----Mutators----
//Change troops of type index at this unit by amount
void AllUnits::mutateTroop(INF::TroopCondition troopCondition, Troops::TroopTypes troopType, i5array amount, Quantity quant, INF::MutateDirection direction, int troopTier) {
	//For debugging
	INF::debugFunction("Troops, mutateTroop");

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

void AllUnits::setBattleFormation(troopConditionArray troopArray) {
	std::cout << "Welcome to the Battle Formation menu.\n";
	std::cout << "Please select a battle formation option: ";
	std::cout << ""
}


INF::ipair AllUnits::translateCoords(INF::ipair coords, CoordsType type) {
	return Coords::translateCoords(coords, type);
}

//Quicksort
std::vector<AllUnits::unitSPTR > AllUnits::sortVector(SortType sort, std::vector<AllUnits::unitSPTR > list) {
	if (sort == LEVEL) {
		return levelSort(list);
	}

	/* for casting back later :
	std::shared_ptr<Base> base(new Derived());
	std::shared_ptr<Derived> derived =
		std::dynamic_pointer_cast<Derived> (base);*/
}

//Has been tested with concatVectors, so should work
std::vector<AllUnits::unitSPTR > AllUnits::levelSort(std::vector<AllUnits::unitSPTR > list) {
	if (list.size() <= 1) {
		return list;
	}

	int listSize = list.size();
	unitSPTR  lastElement = list.at(listSize - 1);
	int lastLevel = lastElement->getLevel();

	std::vector<unitSPTR > greater = {};
	std::vector<unitSPTR > lesser = {};
	std::vector<unitSPTR > same = { lastElement };

	for (int index = 0; index < listSize - 1; index++) {
		unitSPTR  currentElement = list.at(index);
		int currentLevel = currentElement->getLevel();
		if (currentLevel < lastLevel) {
			lesser.push_back(currentElement);
		}
		else if (currentLevel > lastLevel) {
			greater.push_back(currentElement);
		}
		else {
			same.push_back(currentElement);
		}
	}

	greater = levelSort(greater); 
	lesser = levelSort(lesser);

	std::vector<std::vector<unitSPTR >> returnList = { lesser, same, greater };
	return concatVectors(returnList);
}