#include "Buildings.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
Buildings::Buildings() {
	//For debugging
	INF::debugFunction("Buildings, OtherBuildingsToString");

	for (int x : otherBuildingsLevels) {
		x = 0;
	}

	otherBuildingsLevels = INF::i5array{};
	resourceBuildingsLevels = INF::i5array{};
}


//Use struct/class here to pass to template, maybe don't use template??? Use returnArray or returnInt for arrayArg
std::array<int, 5> Buildings::getBuildingLevel(Build::BuildingType type, int index, INF::Quantity quant) {
	//For debugging
	INF::debugFunction("Buildings, getBuildingLevel");

	std::array<int, 5> arrayCopy, returnArray;
	arrayCopy = *levels.first;
	if (type) {
		arrayCopy = *levels.second;
	}

	switch (quant) {
		case SINGLE:
			returnArray[0] = arrayCopy[index];
			break;
		case ALL:
			returnArray = arrayCopy;
	}
	return returnArray;
}

/*Use returnArray or returnInt for arrayArg*/
std::array<int, 5> Buildings::getCapacity(Build::BuildingType type, int name, INF::Quantity amount) {
	//For debugging
	INF::debugFunction("Buildings, getCapacity");

	std::array<int, 5> arrayCopy, returnArray;
	arrayCopy = *levels.first;
	if (type) {
		arrayCopy = *levels.second;
	}

	switch (amount) {
		case SINGLE:
			returnArray[0] = arrayCopy[name];
			break;
		case ALL:
			for (int x = 0; x < 5; x++) {
				returnArray[x] = arrayCopy[x] * (int)capacityAmounts[x];
			}
	}
	return returnArray;
}

/*Use returnArray or returnInt for arrayArg*/
std::array<int, 5> Buildings::getResourceProduction(Build::ResourceBuildings name, INF::Quantity amount) {
	//For debugging
	INF::debugFunction("Buildings, getResourceProduction");

	std::array<int, 5> arrayCopy, returnArray;
	arrayCopy = *levels.first;


	switch (amount) {
		case SINGLE:
			returnArray[0] = arrayCopy[name] * resourceProduction[name];
			break;
		case ALL:
			for (int x = 0; x < 5; x++) {
				returnArray[0] = arrayCopy[x] * resourceProduction[x];
			}
			break;
	}

	return returnArray;
}

/*Purpose: Changes the level of a building.
*type: determines whether the building is a resource or other building.
*
*name: is the name of the building withing the resource/other building array.
*
*quant: is whether or not only 1 level or all levels of a type of building is being mutated.
*
*direction: determines whether the process is addition or subtraction.*/
void Buildings::mutateLevel(Build::BuildingType type, int name, std::array<int, 5> amount, INF::Quantity quant, INF::MutateDirection direction) {
	//For debugging
	INF::debugFunction("Buildings, mutateLevel");

	std::array<int, 5> arrayCopy = *levels.first;
	if (type) {
		arrayCopy = *levels.second;
	}

	switch (quant) {
		case SINGLE:
			switch (direction) {
				case INCREASE:
					arrayCopy[name] += amount[0];
					break;
				case DECREASE:
					arrayCopy[name] -= amount[0];
					break;
			}
			break;
		case ALL:
			switch (direction) {
				case INCREASE:
					arrayCopy = INF::modifyArray(arrayCopy, amount, true);
					break;
				case DECREASE:
					arrayCopy = INF::modifyArray(arrayCopy, amount, false);
					break;
			}
			break;
	}

	if (type) {
		*levels.second = arrayCopy;
		return;
	}
	*levels.first = arrayCopy;
	return;
}

/*Return the amount of troops trained this turn - troopsTrainedThisTurn*/
int Buildings::getTroopsTrainedThisTurn() {
	//For debugging
	INF::debugFunction("Buildings, getTroopsTrainedThisTurn");

	return troopsTrainedThisTurn;
}

void Buildings::printBuildingStats()
{
	//For debugging
	INF::debugFunction("Provinces, printBuildingStats");

	std::array<int, 5> productionArray = getResourceProduction(Build::CHURCH, INF::ALL);
	std::cout << "\033[;34m";

	std::cout << "Building stats of this province: " << std::endl;
	for (int x = 0; x < 5; x++)
	{
		std::cout << "- " << INF::RESOURCE_BUILDING_NAMES[x] << " (" << INF::RESOURCE_BUILDING_NAMES[x].at(0) << ") " << std::endl;
		std::cout << "    Level: " << resourceBuildingsLevels[x] << std::endl;
		std::cout << "    " << INF::RESOURCE_NAMES[x] << " production rate : " << productionArray[x] << std::endl;
	}
	//Add implementation
	std::cout << "Barracks (B) " << std::endl;
	std::cout << "    Level: " << otherBuildingsLevels[0] << std::endl;
	std::cout << "    Max training capacity: " << getCapacity(OTHER, BARRACKS, SINGLE)[0] << "\n\n\033[;0m";


}

//Returns average of all buildings, rounded down to nearest int
int Buildings::getProvinceLevel() {
	//For debugging
	INF::debugFunction("Provinces, getProvinceLevel");

	int unitLevel = 0;

	for (int x : resourceBuildingsLevels)
		unitLevel += resourceBuildingsLevels[x];
	for (int x : otherBuildingsLevels)
		unitLevel += x;

	unitLevel /= (int)resourceBuildingsLevels.size() + (int)otherBuildingsLevels.size();
	return unitLevel;

}

void Buildings::resetTroopsTrainedThisTurn()

{
	//For debugging
	INF::debugFunction("Buildings, resetTroopsTrainedThisTurn");

	troopsTrainedThisTurn = 0;
}

void Buildings::addTroopsTrainedThisTurn(int amount)
{
	//For debugging
	INF::debugFunction("Buildings, addTroopsTrainedThisTurn");

	troopsTrainedThisTurn += amount;
}

void Buildings::initiailizeCapitalBuildings() {
	//For debugging
	INF::debugFunction("Buildings, initializeCapitalBuildings");

	for (int& x : resourceBuildingsLevels) {
		x = 1;
	}
	for (int& x : otherBuildingsLevels) {
		x = 1;
	}
}

void Buildings::initializeEmptyBuildings() {
	//For debugging
	INF::debugFunction("Buildings, initializeEmptyBuildings");

	for (int& x : resourceBuildingsLevels) {
		x = 0;
	}
	for (int& x : otherBuildingsLevels) {
		x = 0;
	}
}

void Buildings::displayListOfBuildings() {
	//For debugging
	INF::debugFunction("Buildings, displayListOfBuildings");

	std::cout << "List of buildings: ";
	for (int x = 1; x <= 5; x++) {
		std::cout << x << ") " << INF::RESOURCE_BUILDING_NAMES[x] << "\n";
	}
	for (int x = 6; x < 10; x++) {
		std::cout << x << ") " << INF::OTHER_BUILDING_NAMES[x] << "\n";
	}
}

