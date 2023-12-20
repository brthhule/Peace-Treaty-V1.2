#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PRIME_UNITS_HEADER 

using namespace UNIT;

//----Constructors----
//One param overloaded Constructor
PrimeUnits::PrimeUnits(int participantIndexArg) { 
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, PrimeUnits (1 Param)");

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
	};
}

//Default Constructor
PrimeUnits::PrimeUnits() {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, PrimeUnits (0 Param)");

	PrimeUnits(-1);
};


void PrimeUnits::printTroopsPresent() {
	constArrayReference troopsPresent = this->getGenericTroops(REGULAR);
	for (int x = 0; x < 5; x++) {
		std::cout << TROOP_NAMES.at(x) << ": " << troopsPresent.at(x) << std::endl;
	}
}

constINT PrimeUnits::getCP() {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, getCP");

	combatPower = 0;
	for (int x = 0; x < 5; x++) {
		combatPower += troopsPresent[x] * INF::Troops_CP[x];
	}
	return combatPower;
}

constINT PrimeUnits::getParticipantIndex() {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, getParticipantIndex");

	return participantIndex;
}

void PrimeUnits::printResources() { 
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, printResources");

	std::cout << "Resources currently present in this " << type << ": \n";
	INF::addColor(INF::BLUE);
	INF::printResources(resourcesPresent);
	INF::addColor(INF::RESET);
}

const std::string& PrimeUnits::getName() { return unitName; }
void PrimeUnits::setName(std::string name) { unitName = name; }

//Mutator Functions
constINT PrimeUnits::getFoodConsumption() { return foodConsumption;}
constINT PrimeUnits::getResource(int resourceIndex) { 
	return resourcesPresent[resourceIndex];
}

void PrimeUnits::mutateResource(ResourceType resource, constINT amount,
	MutateDirection direction) {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, mutateResources");
	int modifier = 1;
	if (direction == DECREASE) { modifier = -1; }
	resourcesPresent.at(resource) + (amount * modifier);
}

void PrimeUnits::mutateAllResources(constArrayReference resourcesArray,
	INF::MutateDirection direction) {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, mdofiyResources");


	resourcesPresent = INF::mutateArray(resourcesPresent, resourcesArray, direction);
}

constINT PrimeUnits::getLevel() {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, getLevel");

	return unitLevel;
}

constArrayReference PrimeUnits::getAllResources() {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, getAllResources");
	return resourcesPresent;
}

const std::string PrimeUnits::getCoords(CoordsType type) {
	return CoordsBASE::getCoordsString(type); 
}

void PrimeUnits::setParticipantIndex(int number) {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, setParticipantIndex");

	participantIndex = number;
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

