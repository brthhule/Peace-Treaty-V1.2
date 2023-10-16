#include "Buildings.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
Buildings::Buildings() {
	for (int x : otherBuildingsLevels) {
		x = 0;
	}
}


//Use struct/class here to pass to template, maybe don't use template??? Use returnArray or returnInt for arrayArg
template<typename T>
std::array<int, 5> Buildings::getBuildingLevel(Build::BuildingType type, int index, CV::Quantity quant, std::array<T, 5> arrayArg) {
	switch (quant) {
	case SINGLE:
		arrayArg[0] = levels[type][index];
		return arrayArg;
	case ALL:
		return *levels[type];
	}
}

/*Use returnArray or returnInt for arrayArg*/
template <typename T>
std::array<int, 5> Buildings::getCapacity(Build::BuildingType type, int name, CV::Quantity amount, std::array<T, 5> arrayArg) {

	switch (amount) {
	case SINGLE:
		arrayArg[0] = levels[type][name];
		break;
	case ALL:
		for (int x = 0; x < 5; x++) {
			arrayArg[x] = (int)levels[type] * (int)capacityAmounts[x];
		}
	}
	return arrayArg;
}

/*Use returnArray or returnInt for arrayArg*/
template<typename T>
std::array<int, 5> Buildings::getResourceProduction(Build::ResourceBuildings name, CV::Quantity amount, std::array<T, 5> arrayArg) {

	switch (amount) {
	case SINGLE:
		arrayArg[0] = resourceBuildingsLevels[name] * resourceProduction[name];
		break;
	case ALL:
		for (int x = 0; x < 5; x++) {
			arrayArg[0] = resourceBuildingsLevels[x] * resourceProduction[x];
		}
		break;
	}
	
	return arrayArg;
}

/*Purpose: Changes the level of a building. 
*type: determines whether the building is a resource or other building. 
*
*name: is the name of the building withing the resource/other building array. 
*
*quant: is whether or not only 1 level or all levels of a type of building is being mutated. 
*
*direction: determines whether the process is addition or subtraction.*/
template<typename T>
T Buildings::mutateLevel(Build::BuildingType type, int name, T amount, CV::Quantity quant, CV::MutateDirection direction) {
	switch (quant) {
	case SINGLE:
		switch (direction) {
		case INCREASE:
			levels[type][name] += amount;
			break;
		case DECREASE:
			levels[type][name] -= amount;
			break;
		}
		break;
	case ALL:
		switch (direction) {
		case INCREASE:
			levels[type] = OF::modifyArray(levels[type], amount, true);
			break;
		case DECREASE:
			levels[type] = OF::modifyArray(levels[type], amount, false);
			break;
		}
		break;
	}
}

/*Return the amount of troops trained this turn - troopsTrainedThisTurn*/
int Buildings::getTroopsTrainedThisTurn() {
	return troopsTrainedThisTurn;
}

void Buildings::printBuildingStats()
{
	OF::debugFunction("Provinces, printBuildingStats");
	std::array<int, 5> productionArray = getResourceProduction(Build::CHURCH, CV::ALL, returnArray);
	std::cout << "\033[;34m";

	std::cout << "Building stats of this province: " << std::endl;
	for (int x = 0; x < 5; x++)
	{
		std::cout << "- " << CV::RESOURCE_BUILDING_NAMES[x] << " (" << CV::RESOURCE_BUILDING_NAMES[x].at(0) << ") " << std::endl;
		std::cout << "    Level: " << resourceBuildingsLevels[x] << std::endl;
		std::cout << "    " << CV::RESOURCE_NAMES[x] << " production rate : " << productionArray[x] << std::endl;
	}
	//Add implementation
	std::cout << "Barracks (B) " << std::endl;
	std::cout << "    Level: " << otherBuildingsLevels[0] << std::endl;
	std::cout << "    Max training capacity: " << getCapacity(OTHER, BARRACKS, SINGLE, returnInt)[0] << "\n\n\033[;0m";


}

//Returns average of all buildings, rounded down to nearest int
int Buildings::getProvinceLevel() {
	OF::debugFunction("Provinces, findProvinceLevel");
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
	troopsTrainedThisTurn = 0;
}

void Buildings::addTroopsTrainedThisTurn(int amount)
{
	troopsTrainedThisTurn += amount;
}

void Buildings::initiailizeCapitalBuildings() {
	for (int& x : resourceBuildingsLevels) {
		x = 1;
	}
	for (int& x : otherBuildingsLevels) {
		x = 1;
	}
}

void Buildings::initializeEmptyBuildings() {
	for (int& x : resourceBuildingsLevels) {
		x = 0;
	}
	for (int& x : otherBuildingsLevels) {
		x = 0;
	}
}

void Buildings::displayListOfBuildings() {
	std::cout << "List of buildings: ";
	for (int x = 1; x <= 5; x++) {
		std::cout << x << ") " << CV::RESOURCE_BUILDING_NAMES[x] << "\n";
	}
	for (int x = 6; x < 10; x++) {
		std::cout << x << ") " << CV::OTHER_BUILDING_NAMES[x] << "\n";
	}
}

