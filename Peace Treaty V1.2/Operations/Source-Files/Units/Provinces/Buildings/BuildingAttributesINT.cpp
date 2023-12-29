#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER

using namespace PROV;

const int Provinces::getCapacity(BUILD::BuildingsEnum name) const { 
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getCapacity");
	BuildingsBASE& currentBuilding = buildings.buildingsVector.at(name);  
	ResourceBuildingsBASE* resourceBuilding = static_cast<ResourceBuildingsBASE*>(&currentBuilding);  

	int amount = resourceBuilding->getCapacityAmount();
	delete resourceBuilding;

	return amount;
}

/*Use returnArray or returnInt for arrayArg*/
i5array& Provinces::getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) { 
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getResourceProduction");

	i5array arrayCopy = {}, returnArray = {};

	if (amount == SINGLE) {
		BuildingsBASE& buildingRef = getBuilding(name); 
		ResourceBuildingsBASE* resourceBuilding = static_cast<ResourceBuildingsBASE*>(&buildingRef); 
		returnArray[0] = arrayCopy[name] * resourceBuilding->getProductionRate();
		delete resourceBuilding;
	} else {
		for (int x = 0; x < 5; x++) {
			ResourceBuildingsBASE* building = static_cast<ResourceBuildingsBASE*>(&buildings.get(BuildingsEnum(x)));
			returnArray[0] = arrayCopy[x] * building->getProductionRate(); 
			delete building;
		}
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
void Provinces::mutateLevel(BuildingsEnum name, MutateDirection direction, int amount) {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "mutateLevel");
	if (direction == DECREASE) { amount *= -1; }
	buildings.buildingsVector.at(name).get().increaseLevel(amount);
}

/*Return the amount of troops trained this turn - troopsTrainedThisTurn*/
constINT Provinces::getTroopsTrainedThisTurn() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getTroopsTrainedThisTurn");
	Barracks* building = static_cast<Barracks*>(&buildings.get(BARRACKS)); 
	int amount = building->getTroopsTrainedThisTurn();
	delete building;
	return amount;
}

void Provinces::printBuildingStats()
{
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "printBuildingStats");

	i5array productionArray = getResourceProduction(BUILD::CHURCH, INF::ALL);
	std::cout << "\033[;34m";

	std::cout << "Building stats of this province: " << std::endl;
	for (int x = 0; x < 10; x++) {
		std::cout << "- " << BUILD::BuildingStrings.at(x) << "(" << BUILD::BuildingStrings.at(x).at(0) << "): \n";
		std::cout << "		Level: " << buildings.get(x).getLevel() << "\n";
		if (x < 5) {
			ResourceBuildingsBASE* resourceBuilding = static_cast<ResourceBuildingsBASE*>(&buildings.get(x));
			std::cout << "		" << INF::RESOURCE_NAMES.at(x) << " production rate: " << resourceBuilding->getProductionRate(); 
			delete resourceBuilding;
		}
	}
	for (int x = 0; x < 5; x++)
	{
		std::cout << "- " << INF::RESOURCE_BUILDING_NAMES[x] << " (" << INF::RESOURCE_BUILDING_NAMES[x].at(0) << ") " << std::endl;
		std::cout << "    Level: " << buildings.get(x).getLevel() << std::endl;
		std::cout << "    " << INF::RESOURCE_NAMES[x] << " production rate : " << productionArray[x] << std::endl;
	}
	//Add implementation
	std::cout << "Barracks (B) " << std::endl;
	std::cout << "    Level: " << buildings.buildingsVector.at(BARRACKS).get().getLevel() << std::endl;
	std::cout << "    Max training capacity: " << getCapacity(BARRACKS) << "\n\n\033[;0m";


}

//Returns average of all BuildingAttributesINT.cpp", "rounded down to nearest int
constINT Provinces::getProvinceLevel() {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getProvinceLevel");

	int unitLevel = 0;
	for (int x = 0; x < 10; x++) { unitLevel += buildings.get(x).getLevel(); }
	
	return unitLevel /= 10;;
}

void Provinces::resetTroopsTrainedThisTurn() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "resetTroopsTrainedThisTurn");
	BuildingsBASE* building = &buildings.get(BARRACKS);

	Barracks* barracks = static_cast<Barracks*>(building);  
	delete building;

	barracks->resetTroopsTrainedThisTurn();
	delete barracks;
}

void Provinces::addTroopsTrainedThisTurn(int amount) {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "addTroopsTrainedThisTurn");

	Barracks* barracks = static_cast<Barracks*>(&buildings.get(BARRACKS)); 

	barracks->addTroopsTrainedThisTurn(amount);
	delete barracks;
}

//Do something in Buildings here
void Provinces::initiailizeCapitalBuildings() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "initializeCapitalBuildings");

	i5array resourceBuildingsLevels, otherBuildingsLevels;
	resourceBuildingsLevels = getTypeLevels(RESOURCE);
	otherBuildingsLevels = getTypeLevels(OTHER);

	for (int x = 0; x < 10; x++) {
		buildings.get(x).increaseLevel(1);
	}
}

void Provinces::printListOfBuildings() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "printListOfBuildings");
	for (int x = 0; x < 10; x++) {
		std::cout << x << ") " << BUILD::BuildingStrings.at(x) << ", level: " << buildings.get(x).getLevel();
	}
}

BuildingsBASE& Provinces::getBuilding(BUILD::BuildingsEnum name) {
	return buildings.get(name);
}

BuildingsBASE& Provinces::getBuilding(int num) {
	return buildings.get(num);
}


i5array Provinces::getTypeLevels(BUILD::BuildingType type) {
	i5array resourceLevels = {}, otherLevels = {};
	for (int index = 0; index < 5; index++) { 
		resourceLevels.at(index) = buildings.get(index).getLevel();
		/*Added explicitness below to get rid of Int - arithn error
		Error: A sub-expression may overflow before being assigned to a wider type*/
		int otherLevelsIndex = index + 5; 
		otherLevels.at(index) = buildings.get(otherLevelsIndex).getLevel();
	}

	if (type == RESOURCE) {
		return resourceLevels;
	}

	return otherLevels;
}