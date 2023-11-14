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
}

//Default Constructor
AllUnits::AllUnits() {
	//For debugging
	INF::debugFunction("AllUnits, AllUnits (0 Param)");

	AllUnits(-1);
};




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

	for (int x = 0; x < 5; x++)
		std::cout << "- " << INF::RESOURCE_NAMES[x] << ": " << resourcesArray[x] << std::endl;

	std::cout << std::endl;
}