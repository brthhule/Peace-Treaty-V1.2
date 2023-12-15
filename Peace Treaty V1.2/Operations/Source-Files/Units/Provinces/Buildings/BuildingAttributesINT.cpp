#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER

using namespace PROV;

int Provinces::getCapacity(BUILD::BuildingsEnum name) { 
	//For debugging
	INF::debugFunction("Buildings, getCapacity");
	std::shared_ptr<BuildingsBASE> currentBuilding = getBuilding(name);
	std::shared_ptr<ResourceBuildingsBASE> resourceBuilding = std::dynamic_pointer_cast<ResourceBuildingsBASE>(currentBuilding);
	return resourceBuilding->getCapacityAmount();
}

/*Use returnArray or returnInt for arrayArg*/
i5array Provinces::getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) { 
	//For debugging
	INF::debugFunction("Buildings, getResourceProduction");

	i5array arrayCopy, returnArray; 
	std::shared_ptr<BuildingsBASE> building = getBuilding(name);  
	std::shared_ptr<ResourceBuildingsBASE> resourceBuilding = std::dynamic_pointer_cast<ResourceBuildingsBASE> (building);


	switch (amount) { 
		case SINGLE:
			returnArray[0] = arrayCopy[name] * resourceBuilding->getProudctionRate();
			delete resourceBuilding;
			break;
		case ALL:
			for (int x = 0; x < 5; x++) {
				ResourceBuildingsBASE building = (ResourceBuildingsBASE)buildings.at(x); 
				returnArray[0] = arrayCopy[x] * building.getProudctionRate(); 
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
void Provinces::mutateLevel(BuildingsEnum name, MutateDirection direction, int amount) {
	//For debugging
	INF::debugFunction("Buildings, mutateLevel");
	if (direction == DECREASE) {
		amount *= -1;
	}
	buildings.at(name).increaseLevel(amount);
}

/*Return the amount of troops trained this turn - troopsTrainedThisTurn*/
const int& Provinces::getTroopsTrainedThisTurn() {
	//For debugging
	INF::debugFunction("Buildings, getTroopsTrainedThisTurn");
	Barracks building = static_cast<Barracks>(buildings.at(BARRACKS));
	return building.getTroopsTrainedThisTurn;
}

void Provinces::printBuildingStats()
{
	//For debugging
	INF::debugFunction("Provinces, printBuildingStats");

	i5array productionArray = getResourceProduction(BUILD::CHURCH, INF::ALL);
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
int Provinces::getProvinceLevel() {
	//For debugging
	INF::debugFunction("Provinces, getProvinceLevel");

	int unitLevel = 0;

	for (BuildingsBASE build : buildings) {
		unitLevel += build.getLevel();
	}
	
	return unitLevel /= 10;;
}

void Provinces::resetTroopsTrainedThisTurn() {
	//For debugging
	INF::debugFunction("Buildings, resetTroopsTrainedThisTurn");

	troopsTrainedThisTurn = 0;
}

void Provinces::addTroopsTrainedThisTurn(int amount) {
	//For debugging
	INF::debugFunction("Buildings, addTroopsTrainedThisTurn");

	troopsTrainedThisTurn += amount;
}

//Do something in Buildings here
void Provinces::initiailizeCapitalBuildings() {
	//For debugging
	INF::debugFunction("Buildings, initializeCapitalBuildings");

	i5array resourceBuildingsLevels, otherBuildingsLevels;
	resourceBuildingsLevels = getTypeLevels(RESOURCE);
	otherBuildingsLevels = getTypeLevels(OTHER);

	for (BuildingsBASE building : buildings) {
		building.increaseLevel(1);
	}
}

void Provinces::displayListOfBuildings() {
	//For debugging
	INF::debugFunction("Buildings, displayListOfBuildings");
	for (int x = 0; x < 10; x++) {
		std::cout << x << ") " << BUILD::BuildingStrings.at(x) << ", level: " << buildings.at(x).getLevel();
	}
}

std::shared_ptr<BuildingsBASE> Provinces::getBuilding(BUILD::BuildingsEnum name) {
	return std::make_shared(buildings.at(type));
}

const BuildingsBASE& Provinces::getBuildingConst(BUILD::BuildingsEnum name) {
	return &buildings.at(name);
}


const std::array<int&,5> Provinces::getTypeLevels(BUILD::BuildingType type) {
	std::array<int&, 5> resourceLevels, otherLevels;
	for (int index = 0; index < 5; index++) { 
		resourceLevels = buildings.at(index).getLevel(); 
		otherLevels = buildings.at(index + 5).getLevel(); 
	}

	if (type == RESOURCE) {
		return resourceLevels;
	}

	return otherLevels;
}