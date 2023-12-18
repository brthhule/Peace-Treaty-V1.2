#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PRIME_UNITS_HEADER 

using namespace UNIT;

//----Constructors----
//One param overloaded Constructor
PrimeUnits::PrimeUnits(int participantIndexArg) { 
	//For debugging
	INF::debugFunction("PrimeUnits, PrimeUnits (1 Param)");

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
PrimeUnits::PrimeUnits() {
	//For debugging
	INF::debugFunction("PrimeUnits, PrimeUnits (0 Param)");

	PrimeUnits(-1);
};


void PrimeUnits::printTroopsPresent() {
	i5array troopsPresent = this->getGenericTroops(REGULAR);
	for (int x = 0; x < 5; x++) {
		std::cout << TROOP_NAMES.at(x) << ": " << troopsPresent.at(x) << std::endl;
	}
}

constINT PrimeUnits::getCP() {
	//For debugging
	INF::debugFunction("PrimeUnits, getCP");

	combatPower = 0;
	for (int x = 0; x < 5; x++) {
		combatPower += troopsPresent[x] * INF::Troops_CP[x];
	}
	return combatPower;
}

constINT PrimeUnits::getParticipantIndex() {
	//For debugging
	INF::debugFunction("PrimeUnits, getParticipantIndex");

	return participantIndex;
}

void PrimeUnits::printResources() { 
	//For debugging
	INF::debugFunction("PrimeUnits, printResources");

	std::cout << "Resources currently present in this " << type << ": \n";
	INF::addColor(INF::BLUE);
	printResources(resourcesPresent);
	INF::addColor(INF::RESET);
}

std::string PrimeUnits::getUnitName() {
	//For debugging
	INF::debugFunction("PrimeUnits, getUnitName");

	return unitName;
}
void PrimeUnits::setUnitName(std::string name) {
	//For debugging
	INF::debugFunction("PrimeUnits, setUnitName");

	unitName = name;
}

//Mutator Functions
constINT PrimeUnits::getFoodConsumption() {
	//For debugging
	INF::debugFunction("PrimeUnits, getFoodConsumption");

	return foodConsumption;
}
constINT PrimeUnits::getResource(int resourceIndex) {
	//For debugging
	INF::debugFunction("PrimeUnits, getResource");

	return resourcesPresent[resourceIndex];
}
void PrimeUnits::modifySpecificResource(int index, int amount, bool isAdd) {
	//For debugging
	INF::debugFunction("PrimeUnits, modifySpecificResources");

	if (isAdd)
		resourcesPresent[index] += amount;
	else
		resourcesPresent[index] -= amount;
}

void PrimeUnits::mutateAllResources(i5array resourcesArray, INF::MutateDirection direction) {
	//For debugging
	INF::debugFunction("PrimeUnits, mdofiyResources");

	resourcesPresent = INF::mutateArray(resourcesPresent, resourcesArray, direction);
}

constINT PrimeUnits::getLevel() {
	//For debugging
	INF::debugFunction("PrimeUnits, getLevel");

	return unitLevel;
}

constI5array PrimeUnits::getAllResources() {
	//For debugging
	INF::debugFunction("PrimeUnits, getAllResources");
	return resourcesPresent;
}

const std::string PrimeUnits::getCoords(CoordsType type) {
	return CoordsBASE::getCoords(type);
}

void PrimeUnits::setParticipantIndex(int number) {
	//For debugging
	INF::debugFunction("PrimeUnits, setParticipantIndex");

	participantIndex = number;
}




i5array PrimeUnits::getAllOneTroopArray(INF::TroopCondition troopCondition, TroopUnitsBASE::TroopTypes type) {
	//For debugging
	INF::debugFunction("Troops, getAllOneTroopArray");

	return allTroopConditions.at(troopCondition.at(type));
}

int PrimeUnits::getAllOneTroopInt(INF::TroopCondition troopCondition, TroopUnitsBASE::TroopTypes type) {
	i5array tempArray = getAllOneTroopArray(troopCondition, type);
	INF::debugFunction("Troops, getAllOneTroopInt");

	int total = 0;
	for (int x : tempArray) {
		total += x;
	}

	return total;
}

i5array PrimeUnits::getGenericTroops(TroopCondition troopCondition) {
	i5array troopTotals = { 0,0,0,0,0 };

	for (int x = 0; x < 5; x++) {
		TroopUnitsBASE::TroopTypes troopType = (TroopUnitsBASE::TroopTypes)x;
		troopTotals.at(x) = getAllOneTroopInt(troopCondition, troopType);
	}

	return troopTotals;
}

//----Mutators----
//Change troops of type index at this unit by amount
void PrimeUnits::mutateTroop(INF::TroopCondition troopCondition, TroopUnitsBASE::TroopTypes troopType, i5array amount, Quantity quant, INF::MutateDirection direction, int troopTier) {
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

void PrimeUnits::setBattleFormation(troopConditionArray troopArray) {
	std::cout << "Welcome to the Battle Formation menu.\n";
	std::cout << "Please select a battle formation option: ";
	std::cout << "";
}


INF::ipair PrimeUnits::translateCoords(INF::ipair coords, CoordsType type) { 
	return CoordsBASE::translateCoords(coords, type);
}

//Quicksort
unitSPTRList PrimeUnits::sortVector(SortType sort, unitSPTRList list) { 
	if (sort == LEVEL) {
		return levelSort(list);
	}

	/* for casting back later :
	std::shared_ptr<Base> base(new Derived());
	std::shared_ptr<Derived> derived =
		std::dynamic_pointer_cast<Derived> (base);*/
}

//Has been tested with concatVectors, so should work

unitSPTRList PrimeUnits::levelSort(unitSPTRList list) {
	if (list.size() <= 1) {
		return list;
	}

	int listSize = list.size();
	unitSPTR lastElement = list.at(listSize - 1);
	int lastLevel = lastElement->getLevel();

	unitSPTRList greater = {}; 
	unitSPTRList lesser = {}; 
	unitSPTRList same = { lastElement }; 

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

	std::vector<unitSPTRList> returnList = { lesser, same, greater }; 
	return concatVectors(returnList);
}

