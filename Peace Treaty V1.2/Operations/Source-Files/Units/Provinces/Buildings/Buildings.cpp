#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include BUILDINGS_HEADER
#include BUILD_HEADER

Buildings::Buildings() {
	m_data[0] = *farm;
	m_data[1] = &mill;
	m_data[2] = &quarry;
	m_data[3] = &mine;
	m_data[4] = &church;
	m_data[5] = &barracks;
	m_data[6] = &infirmary;
	m_data[7] = &library;
	m_data[8] = &residences;
	m_data[9] = &wall;
}

ResourceBuildings* Buildings::getResourceBuilding(BUILD::BuildingsEnum type) {  
	if ((int)type >= 5) {
		LOG::DEBUG("Invalid Building Type");
		throw "Invalid building type";
		return nullptr;
	}
	return (this->resourceBuildings.at(type));
}


#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include Buildings::_HEADER

using namespace PROV;
using namespace INF;
using namespace BUILD;

const int Buildings::getCapacity(BUILD::BuildingsEnum name) {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getCapacity");
	return getResourceBuilding(name)->getCapacity();
}

int Buildings::getResourceBuildingProduction(int buildingNumber) {
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getResourceProduction");

	return getResourceBuilding(name)->getProductionRate(); 
}

/*Use returnArray or returnInt for arrayArg*/
i5array Buildings::getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getResourceProduction");

	i5array returnArray = {};

	for (int x = 0; x < 5; x++) { returnArray[x] = getResourceBuildingProduction(x); }
	if (amount == SINGLE) { returnArray[0] = getResourceBuildingProduction(name); }

	return returnArray;
}


void Buildings::mutateLevel(BuildingsEnum name, MutateDirection direction, int amount) {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "mutateLevel");
	if (name < 5) {
		resourceBuildings.at(name).mutateLevel(amount);
	}
	if (direction == DECREASE) { amount *= -1; }
	buildingsVector->at(name)->increaseLevel(amount);
}

/*Return the amount of troops trained this turn - troopsTrainedThisTurn*/
const int Buildings::getTroopsTrainedThisTurn() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *buildingsVector->at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	int amount = barracks.getTroopsTrainedThisTurn();
	return amount;
}

void Buildings::printBuildingStats() {
	//For debugging
	DEBUG_FUNCTION("Buildings::.cpp", "printBuildingStats");

	i5array productionArray = getResourceProduction(BUILD::CHURCH, INF::ALL);
	std::cout << "\033[;34m";

	std::cout << "Building stats of this province: " << std::endl;
	for (int x = 0; x < 10; x++) {
		std::cout << "- " << BUILD::BuildingStrings.at(x) << "(" << BUILD::BuildingStrings.at(x).at(0) << "): \n";
		std::cout << "		Level: " << buildingsVector->at(x)->getLevel() << "\n";
		if (x < 5) {
			std::cout << "		" << INF::RESOURCE_NAMES.at(x) << " production rate: " << getResourceBuildingProduction(x);
		}
	}
	for (int x = 0; x < 5; x++) {
		std::cout << "- " << BUILD::RESOURCE_BUILDING_NAMES[x] << " (" << BUILD::RESOURCE_BUILDING_NAMES[x].at(0) << ") " << std::endl;
		std::cout << "    Level: " << buildingsVector->at(x)->getLevel() << std::endl;
		std::cout << "    " << INF::RESOURCE_NAMES[x] << " production rate : " << productionArray[x] << std::endl;
	}
	//Add implementation
	std::cout << "Barracks (B) " << std::endl;
	std::cout << "    Level: " << buildingsVector->at(BARRACKS)->getLevel() << std::endl;
	std::cout << "    Max training capacity: " << getCapacity(BARRACKS) << "\n\n\033[;0m";


}

//Returns average of all BuildingAttributesINT.cpp", "rounded down to nearest int
const int Buildings::getProvinceLevel() {
	//For debugging
	DEBUG_FUNCTION("Buildings::.cpp", "getProvinceLevel");

	int unitLevel = 0;
	for (int x = 0; x < 10; x++) { unitLevel += buildingsVector->at(x)->getLevel(); }

	return unitLevel /= 10;;
}

void Buildings::resetTroopsTrainedThisTurn() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "resetTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *buildingsVector->at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	barracks.resetTroopsTrainedThisTurn();
}

void Buildings::addTroopsTrainedThisTurn(int amount) {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "addTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *buildingsVector->at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	barracks.addTroopsTrainedThisTurn(amount);
}

//Do something in Buildings here
void Buildings::initiailizeCapitalBuildings() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "initializeCapitalBuildings");

	i5array resourceBuildingsLevels, otherBuildingsLevels;
	resourceBuildingsLevels = getTypeLevels(RESOURCE);
	otherBuildingsLevels = getTypeLevels(OTHER);

	for (int x = 0; x < 10; x++) {
		buildingsVector->at(x)->increaseLevel(1);
	}
}

void Buildings::printListOfBuildings() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "printListOfBuildings");
	for (int x = 0; x < 10; x++) {
		std::cout << x << ") " << BUILD::BuildingStrings.at(x) << ", level: " << buildingsVector->at(x)->getLevel();
	}
}

i5array Buildings::getTypeLevels(BUILD::BuildingType type) { 
	i5array resourceLevels = {}, otherLevels = {};
	for (int index = 0; index < 5; index++) {
		resourceLevels.at(index) = buildingsVector->at(index)->getLevel();
		otherLevels.at(index) = buildingsVector->at(index + 5)->getLevel();
	}

	if (type == RESOURCE) { return resourceLevels; }
	return otherLevels;
}

BuildingsBASE& Buildings::getBuilding(BUILD::BuildingsEnum name) {
	return *buildingsVector->at(name);
}

BuildingsBASE& Buildings::getBuilding(int num) {
	return *buildingsVector->at(num);
}