#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER

using namespace PROV;
using namespace INF;
using namespace BUILD;

const int Provinces::getCapacity(BUILD::BuildingsEnum name) { 
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getCapacity");
	BuildingsBASE& building_ref = *buildingsVector->at(name);
	ResourceBuildingsBASE &resourceBuilding = static_cast<ResourceBuildingsBASE&>(building_ref);

	return resourceBuilding.getCapacityAmount();
}

int Provinces::getResourceBuildingProduction(int buildingNumber) {
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getResourceProduction");

	BuildingsBASE& building_ref = *buildingsVector->at(buildingNumber);

	ResourceBuildingsBASE& resourceBuilding = static_cast<ResourceBuildingsBASE&>(building_ref);
	return resourceBuilding.getProductionRate();
}

/*Use returnArray or returnInt for arrayArg*/
i5array Provinces::getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) {  
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getResourceProduction");

	i5array returnArray = {};

	for (int x = 0; x < 5; x++) { returnArray[x] = getResourceBuildingProduction(x); }
	if (amount == SINGLE) { returnArray[0] = getResourceBuildingProduction(name); }

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
	buildingsVector->at(name)->increaseLevel(amount);
}

/*Return the amount of troops trained this turn - troopsTrainedThisTurn*/
const int Provinces::getTroopsTrainedThisTurn() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "getTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *buildingsVector->at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	int amount = barracks.getTroopsTrainedThisTurn();
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
const int Provinces::getProvinceLevel() {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getProvinceLevel");

	int unitLevel = 0;
	for (int x = 0; x < 10; x++) { unitLevel += buildingsVector->at(x)->getLevel(); }  
	
	return unitLevel /= 10;;
}

void Provinces::resetTroopsTrainedThisTurn() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "resetTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *buildingsVector->at(BARRACKS); 
	Barracks& barracks = static_cast<Barracks&>(building_ref); 
	barracks.resetTroopsTrainedThisTurn(); 
}

void Provinces::addTroopsTrainedThisTurn(int amount) {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "addTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *buildingsVector->at(BARRACKS); 
	Barracks& barracks = static_cast<Barracks&>(building_ref); 
	barracks.addTroopsTrainedThisTurn(amount);    
}

//Do something in Buildings here
void Provinces::initiailizeCapitalBuildings() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "initializeCapitalBuildings");

	i5array resourceBuildingsLevels, otherBuildingsLevels;
	resourceBuildingsLevels = getTypeLevels(RESOURCE);
	otherBuildingsLevels = getTypeLevels(OTHER);

	for (int x = 0; x < 10; x++) {
		buildingsVector->at(x)->increaseLevel(1);
	}
}
 
void Provinces::printListOfBuildings() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "printListOfBuildings");
	for (int x = 0; x < 10; x++) {
		std::cout << x << ") " << BUILD::BuildingStrings.at(x) << ", level: " << buildingsVector->at(x)->getLevel();   
	}
}

i5array Provinces::getTypeLevels(BUILD::BuildingType type) {
	i5array resourceLevels = {}, otherLevels = {};
	for (int index = 0; index < 5; index++) { 
		resourceLevels.at(index) = buildingsVector->at(index)->getLevel();
		/*Added explicitness below to get rid of Int - arithn error
		Error: A sub-expression may overflow before being assigned to a wider type*/
		int otherLevelsIndex = index + 5; 
		otherLevels.at(index) = buildingsVector->at(otherLevelsIndex)->getLevel(); 
	}

	if (type == RESOURCE) {
		return resourceLevels;
	}

	return otherLevels;
}

BuildingsBASE& Provinces::getBuilding(BUILD::BuildingsEnum name) {
	return *buildingsVector->at(name);
}

BuildingsBASE& Provinces::getBuilding(int num) {
	return *buildingsVector->at(num);
}