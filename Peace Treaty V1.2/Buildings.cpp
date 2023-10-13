#include "Buildings.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
Buildings::Buildings() {
	for (int x : otherBuildingsLevels) {
		x = 0;
	}
}

template<typename T>
T Buildings::getBuildingLevel(Build::BuildingType type, int index, CV::Quantity quant, T returnType) {
	switch (quant) {
	case SINGLE:
		return levels[type][index];
	case ALL:
		return *levels[type];
	}
}

template <typename T>
T Buildings::getCapacity(Build::BuildingType type, int name, CV::Quantity amount, T returnType) {
	switch (amount) {
	case SINGLE:
		return levels[type][name];
		break;
	case ALL:
		std::array<int, 5> tempArray;
		for (int x = 0; x < 5; x++) {
			tempArray[x] = levels[type] * capacityAmounts[x];
		}
		return tempArray;
	}
}

template<typename T>
T Buildings::getResourceProduction(Build::ResourceBuildings name, CV::Quantity amount, T returnType) {
	switch (amount){
	case SINGLE:
		return resourceBuildingsLevels[name] * resourceProduction[name];
	case ALL:
		std::array<int, 5> amounts;
		for (int x = 0; x < 5; x++) {
			amounts[0] = resourceBuildingsLevels[x] * resourceProduction[x];
		}
		return amounts;
		return 
	}
}

template<typename T>
T Buildings::mutateLevel(Build::BuildingType type, int name, T amount, CV::Quantity quant, CV::MutateDirection directiom) {
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
	std::cout << "    Max training capacity: " << getCapacity(OTHER, BARRACKS, SINGLE, returnInt) << "\n\n\033[;0m";


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



