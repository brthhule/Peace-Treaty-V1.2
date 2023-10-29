#include "AllUnits.h"

//----Constructors----
//One param overloaded Constructor
AllUnits::AllUnits(int participantIndexArg) {
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
	AllUnits(-1);
};




int AllUnits::getCP() {
	combatPower = 0;
	for (int x = 0; x < 5; x++) {
		combatPower += troopsPresent[x] * CV::TROOPS_CP[x];
	}
	return combatPower;
}

int AllUnits::getParticipantIndex() {
	return participantIndex;
}

void AllUnits::printResources() {
	std::cout << "Resources currently present in this " << type << ": \n";
	addColor(BLUE);
	printResources(resourcesPresent);
	addColor(RESET);
}

std::string AllUnits::getUnitName() {
	return unitName;
}
void AllUnits::changeUnitName(std::string name) {
	unitName = name;
}

//Mutator Functions
int AllUnits::getFoodConsumption() {
	return foodConsumption;
}
int AllUnits::getResource(int resourceIndex) {
	return resourcesPresent[resourceIndex];
}
void AllUnits::modifySpecificResource(int index, int amount, bool isAdd) {
	if (isAdd)
		resourcesPresent[index] += amount;
	else
		resourcesPresent[index] -= amount;
}

void AllUnits::modifyResources(std::array<int, 5> resourcesArray, bool isAdd) {
	OF::modifyArray(resourcesPresent, resourcesArray, isAdd);
}

int AllUnits::getLevel() {
	return unitLevel;
}

std::array<int, 5> AllUnits::getAllResources() {
	return resourcesPresent;
}

void AllUnits::changeParticipantIndex(int number) {
	participantIndex = number;
}

void AllUnits::printResources(std::array<int, 5> resourcesArray) {
	OF::debugFunction("OtherFunctions, printResources");
	for (int x = 0; x < 5; x++)
		std::cout << "- " << CV::RESOURCE_NAMES[x] << ": " << resourcesArray[x] << std::endl;

	std::cout << std::endl;
}