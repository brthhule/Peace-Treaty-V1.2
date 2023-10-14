#include "AllUnits.h"

//----Constructors----
//One param overloaded Constructor
AllUnits::AllUnits(int participantIndexArg)
{
	switch (participantIndexArg) {
	case -1:
		canSelectThisUnit = false;
		break;
	default:
		canSelectThisUnit = true;
		for (int x = 0; x < 5; x++)
		{
			resourcesPresent[x] = initialStats[x];
			troopsPresent[x] = 0;
			troopsInjured[x] = 0;
		}
		break;
	}

	participantIndex = participantIndexArg;
	foodConsumption = 0;
	unitLevel = 0;
	CP = 0;
	totalTroops = 0;
}
//Default Constructor
AllUnits::AllUnits() {
	AllUnits(-1);
};


//--------Troop Functions--------
//Return a troop by index or all troops-- done by type. Pass -1 for troopIndex to return all troops of a type
template<typename T>
T AllUnits::getTroop(CV::MutateTroopType type, int troopIndex, T data) {
	std::array<int*, 3> troop = { &troopsPresent[troopIndex], &troopsInjured[troopIndex], &troopsLost[troopIndex] };
	std::array<std::array<int, 5>*, 3> allTroops = { &troopsPresent, &troopsInjured, &troopsLost };
	T *troopPtr;

	if (troopIndex == -1) {
		troopPtr = allTroops[type];
	}
	else {
		troopPtr = troop[type];
	}
	return *troopPtr;
}

//----Mutators----
//Change troops of type index at this unit by amount
template<typename T>
T AllUnits::mutateTroop(CV::MutateTroopType type, int troopIndex, T amount, CV::MutateDirection direction) {
	T* troopPtr;
	std::array<int*, 3> troop = { &troopsPresent[troopIndex], &troopsInjured[troopIndex], &troopsLost[troopIndex] };
	std::array<std::array<int, 5>*, 3> allTroops = { &troopsPresent, &troopsInjured, &troopsLost };

	if constexpr (std::is_same_v<T, int>) {
		troopPtr = troopTypes[type];

		if (direction) {
			troopPtr += amount;
			delete troopPtr;
			return;
		}
		troopPtr -= amount;
		delete troopPtr;
		return;
	}
	else if (constexpr (std::is_same_v < T, std::array<int, 5>)) {
		troopPtr = allTroops[type];
		*troopPtr = OF::modifyArray(*troopsPtr, amounts, direction);
		delete troopPtr;
		return;
	}
}



int AllUnits::getCP() {
	CP = 0;
	for (int x = 0; x < 5; x++) {
		CP += troopsPresent[x] * CV::TROOPS_CP[x];
	}
	return CP;
}

int AllUnits::getParticipantIndex()
{
	return participantIndex;
}

void AllUnits::printResources()
{
	std::cout << "Resources currently present in this " << isCommanderOrProvince << ": \n";
	std::cout << "\033[;34m";
	OF::printResources(resourcesPresent);
	std::cout << "\033[;0m";
}

std::string AllUnits::getUnitName()
{
	return unitName;
}
void AllUnits::changeUnitName(std::string name)
{
	unitName = name;
}

//Mutator Functions
int AllUnits::getFoodConsumption() {
	return foodConsumption;
}
int AllUnits::getResource(int resourceIndex) {
	return resourcesPresent(resourceIndex);
}
void AllUnits::modifySpecificResource(int index, int amount, bool isAdd)
{
	if (isAdd)
		resourcesPresent[index] += amount;
	else
		resourcesPresent[index] -= amount;
}

void AllUnits::modifyResources(std::array<int, 5> resourcesArray, bool isAdd)
{
	OF::modifyArray(resourcesPresent, resourcesArray, isAdd);
}

int AllUnits::getLevel()
{
	return unitLevel;
}

std::array<int, 5> AllUnits::getAllResources()
{
	return resourcesPresent;
}

void AllUnits::changeParticipantIndex(int number) {
	participantIndex = number;
}