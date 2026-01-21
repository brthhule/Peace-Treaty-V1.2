#include "..\..\..\..\Support\Paths.h"
#include PRIME_UNITS_HEADER 

using namespace UNIT;
using namespace INF;
using namespace TROOP;
using namespace COORD;

//----Constructors----
//One param overloaded Constructor
PrimeUnits::PrimeUnits(int participantIndexArg) { 
	//For debugging
	DEBUG_FUNCTION("PrimeUnits.cpp", "PrimeUnits (int)");

	switch (participantIndexArg) {
		case -1:
			canSelectThisUnit = false;
			break;
		default:
			canSelectThisUnit = true;
			for (int x = 0; x < 5; x++) {
				resourcesPresent[x] = initialStats[x];
			}
			break;
	}

	participantIndex = participantIndexArg;
	foodConsumption = 0;
	level = 0;
	combatPower = 0;
	totalTroops = 0;
	resourcesPresent = { 0,0,0,0,0 };
	initialStats = { 5,4,3,2,1 };
	type = COMMANDER;//Fix this???
	DEBUG_FUNCTION_END;
}

PrimeUnits::PrimeUnits(const PrimeUnits& copyUnit) {
	DEBUG_FUNCTION("PrimeUnits.cpp", "PrimeUnits(const PrimeUnits& copyUnit)");
	resourcesPresent = copyUnit.resourcesPresent;
	initialStats = copyUnit.initialStats;

	combatPower = copyUnit.combatPower;
	totalTroops = copyUnit.totalTroops;
	foodConsumption = copyUnit.foodConsumption;
	participantIndex = copyUnit.participantIndex;
	level = copyUnit.level;

	//Coordinates;

	canSelectThisUnit = copyUnit.canSelectThisUnit;
	type = copyUnit.type;
	name = copyUnit.name;
	troops = copyUnit.troops; 
	DEBUG_FUNCTION_END;
}

constINT PrimeUnits::getParticipantIndex() const {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits.cpp", "getParticipantIndex");
	DEBUG_FUNCTION_END;
	return participantIndex;
}

void PrimeUnits::printResources() const { 
	//For debugging
	DEBUG_FUNCTION("PrimeUnits.cpp", "printResources");

	std::cout << "Resources currently present in this " << type << ": \n";
	LOG::addColor(LOG::BLUE);
	INF::printResources(resourcesPresent);
	LOG::addColor(LOG::RESET);
	DEBUG_FUNCTION_END;
}

const std::string& PrimeUnits::getName() const { 
	DEBUG_FUNCTION("PrimeUnits.cpp", "getName()"); 
	DEBUG_FUNCTION_END;
	return name; 
}
void PrimeUnits::setName(std::string name) { 
	DEBUG_FUNCTION("PrimeUnits.cpp", "setName(std::string name)"); 
	this->name = name; 
	DEBUG_FUNCTION_END;
}

//Mutator Functions
constINT PrimeUnits::getFoodConsumption() const {
	DEBUG_FUNCTION("PrimeUnits.cpp", "getFoodConsumption()"); 
	DEBUG_FUNCTION_END;
	return foodConsumption;}
constINT PrimeUnits::getResource(int resourceIndex) { 
	return resourcesPresent[resourceIndex];
}

void PrimeUnits::mutateResource(ResourceType resource, constINT amount,
	INF::MutateDirection direction) {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits.cpp", "mutateResource(ResourceType resource, constINT amount, INF::MutateDirection direction)");
	int modifier = 1;
	if (direction == DECREASE) { modifier = -1; }
	resourcesPresent[resource] += (amount * modifier); 
	DEBUG_FUNCTION_END;
}

void PrimeUnits::mutateAllResources(constArrayRef resourcesArray,
	INF::MutateDirection direction) {
	DEBUG_FUNCTION("PrimeUnits.cpp", "mutateAllResources");


	resourcesPresent = mutateArray(resourcesPresent, resourcesArray, direction);
	DEBUG_FUNCTION_END;
}

constINT PrimeUnits::getLevel() const {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits.cpp", "getLevel");
	DEBUG_FUNCTION_END;
	return level;
}

constArrayRef PrimeUnits::getAllResources() const {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits.cpp", "getAllResources");
	DEBUG_FUNCTION_END;
	return resourcesPresent;
}

const std::string PrimeUnits::getCoords(CoordsType type) const {
	return CoordsBASE::getCoordsString(type); 
}

void PrimeUnits::setParticipantIndex(int number) {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits.cpp", "setParticipantIndex");
	DEBUG_FUNCTION_END;
	participantIndex = number;
}




INF::ipair PrimeUnits::translateCoords(INF::ipair coords, CoordsType type) { 
	return CoordsBASE::translateCoords(coords, type);
}

//Quicksort
unitSPTRList PrimeUnits::sortVector(SortType sort, unitSPTRList list) { 
	DEBUG_FUNCTION("PrimeUnits.cpp", "sortVector(SortType sort, unitSPTRList list)");
	if (sort == LEVEL) {
		DEBUG_FUNCTION_END;
		return levelSort(list);
	}

	DEBUG_FUNCTION_END;
	return {};
	/* for casting back later :
	std::shared_ptr<Base> base(new Derived());
	std::shared_ptr<Derived> derived =
		std::dynamic_pointer_cast<Derived> (base);*/
}

//Has been tested with concatVectors, so should work

unitSPTRList PrimeUnits::levelSort(unitSPTRList list) {
	DEBUG_FUNCTION("PrimeUnits.cpp", "levelSort(unitSPTRList list)");
	if (list.size() <= 1) {
		return list;
	}

	int listSize = (int)list.size();
	unitSPTR lastElement = list.at(listSize - 1);
	int lastLevel = lastElement->getLevel();

	unitSPTRList greater = {};  
	unitSPTRList lesser = {}; 
	unitSPTRList same = { lastElement }; 

	for (int index = 0; index < listSize - 1; index++) {
		unitSPTR currentElement = list.at(index);
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
	DEBUG_FUNCTION_END;
	return concatUnitVectors(returnList); 
	
}



void PrimeUnits::printNameLevel() const {
	std::cout << "Name: " << name << ", Level: " << level;
}

const std::string PrimeUnits::getNameLevel() const {
	return "Name " + name + ", Level: " + std::to_string(level); 
}

UNIT::unitSPTRList UNIT::concatUnitVectors(std::vector<unitSPTRList> list) {
	DEBUG_FUNCTION("PrimeUnits.cpp", "concatUnitVectors(std::vector<unitSPTRList> list)");
	unitSPTRList baseList = list.at(0); 

	for (int index = 1; index < 3; index++) { 
		unitSPTRList currentList = list.at(index);  
		for (unitSPTR element : currentList) {
			baseList.push_back(element);
		}
	}
	return baseList;
	DEBUG_FUNCTION_END;
}