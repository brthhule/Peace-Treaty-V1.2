#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"

#include BUILDINGS_HEADER
#include BUILD_HEADER
#include <string>

using namespace std::literals::string_literals;

Buildings::Buildings() {
	resourceBuildings = {}; 
}

ResourceBuildings* Buildings::getResourceBuilding(BUILD::BuildingsEnum type) {    
	if ((int)type >= 5) {
		LOG::DEBUG("Invalid Building Type");
		throw "Invalid building type";
		return nullptr;
	}
	return &(this->resourceBuildings.at(type));
}


#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
#include BUILDINGS_HEADER

using namespace INF;
using namespace BUILD;

 int Buildings::getCapacity(BUILD::BuildingsEnum name) {
	LOG::DEBUG("BuildingAttributesINT.cpp. getCapacity");

	return getResourceBuilding(name)->getCapacity();
}

int Buildings::getResourceBuildingProduction(int buildingNumber) {
	LOG::DEBUG("BuildingAttributesINT.cpp, getResourceProduction");

	ResourceBuildings* building;
	building = getResourceBuilding((BuildingsEnum)buildingNumber); 
	return building->getProductionRate();   
}

/*Use returnArray or returnInt for arrayArg*/
i5array Buildings::getResourceProduction(BUILD::BuildingsEnum building, INF::Quantity amount) {
	LOG::DEBUG("BuildingAttributesINT.cpp, getResourceProduction");

	i5array returnArray = {};
	for (int x = 0; x < 5; x++) { 
		returnArray[x] = getResourceBuildingProduction(x); 
	}

	if (amount == SINGLE) { 
		returnArray[0] = getResourceBuildingProduction(building);  
	}

	return returnArray;
}


void Buildings::mutateLevel(BuildingsEnum name, MutateDirection direction, int amount) {
	LOG::DEBUG("BuildingAttributesINT.cpp", "mutateLevel");
	if (name < 5) {
		ResourceBuildings* building = &resourceBuildings.at(name);  
		building->mutateLevel(amount, direction); 
	}

	if (direction == DECREASE) { amount *= -1; }

	allBuildings.at(name)->increaseLevel(amount); 
}

/*Return the amount of troops trained this turn - troopsTrainedThisTurn*/
int Buildings::getTroopsTrainedThisTurn() {
	LOG::DEBUG("BuildingAttributesINT.cpp", "getTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *allBuildings.at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	return barracks.getTroopsTrainedThisTurn(); 
}

void Buildings::printBuildingStats() {
	LOG::DEBUG("Buildings.cpp, printBuildingStats"); 

	i5array productionArray = getResourceProduction(BUILD::CHURCH, INF::ALL);

	LOG::PRINT(LOG::getColor(LOG::BLUE) + "Building stats of this province: \n");
	for (int x = 0; x < 10; x++) {
		std::string buildingName = BUILD::BuildingStrings.at(x); 

		LOG::PRINT("- " + buildingName + "(" + buildingName.at(0) + "): \n");
		std::cout << "\tLevel: " << allBuildings.at(x)->getLevel() << "\n";  
		if (x < 5) {
			int rate = getResourceBuildingProduction(x);
			std::string resource = INF::RESOURCE_NAMES[x];
			std::cout << "\t" << resource << " production rate: " << rate << "\n"; 
		}
	}

	for (int x = 0; x < 5; x++) {
		std::string buildingName = BUILD::RESOURCE_BUILDING_NAMES[x];
		std::string resource = INF::RESOURCE_NAMES[x];
		std::string productionRate = std::to_string(productionArray[x]);
		std::string level = std::to_string(allBuildings[x]->getLevel());

		LOG::PRINT("- "s + buildingName + " (" + buildingName + ")\n"s);
		LOG::PRINT("\tLevel: "s + level + "\n"s); 
		LOG::PRINT("\t" + resource + " production rate : " + productionRate + "\n"); 
	}
	//Add implementation
	std::string capacity = std::to_string(getCapacity(BARRACKS));
	std::string level = std::to_string(allBuildings.at(BARRACKS)->getLevel());
	LOG::PRINT("Barracks (B)\n");
	LOG::PRINT("\tLevel: "s + level + "\n"s);
	LOG::PRINT("\tMax training capacity: "s + capacity + "\n\n\033[;0m"s); 


}

//Returns average of all BuildingAttributesINT.cpp", "rounded down to nearest int
int Buildings::getProvinceLevel() {
	//For debugging
	LOG::DEBUG("Buildings::.cpp, getProvinceLevel"); 

	int unitLevel = 0;
	for (int x = 0; x < 10; x++) { unitLevel += allBuildings.at(x)->getLevel(); }

	return unitLevel /= 10;;
}

void Buildings::resetTroopsTrainedThisTurn() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "resetTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *allBuildings.at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	barracks.resetTroopsTrainedThisTurn();
}

void Buildings::addTroopsTrainedThisTurn(int amount) {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "addTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *allBuildings.at(BARRACKS);
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
		allBuildings.at(x)->increaseLevel(1); 
	}
}

void Buildings::printListOfBuildings() {
	//For debugging
	DEBUG_FUNCTION("BuildingAttributesINT.cpp", "printListOfBuildings");
	for (int x = 0; x < 10; x++) {
		std::cout << x << ") " << BUILD::BuildingStrings.at(x) << ", level: " << allBuildings.at(x)->getLevel(); 
	}
}

i5array Buildings::getTypeLevels(BUILD::BuildingType type) { 
	i5array resourceLevels = {}, otherLevels = {};
	for (int index = 0; index < 5; index++) {
		resourceLevels.at(index) = allBuildings.at(index)->getLevel();
		otherLevels.at(index) = allBuildings.at(index + 5)->getLevel();
	}

	if (type == RESOURCE) { return resourceLevels; }
	return otherLevels;
}

BuildingsBASE& Buildings::getBuilding(BUILD::BuildingsEnum name) {
	return *allBuildings.at(name);
}

BuildingsBASE& Buildings::getBuilding(int num) {
	return *allBuildings.at(num);
}