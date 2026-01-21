#include "..\..\..\..\..\Support\Paths.h"

#include BUILDINGS_HEADER
#include BUILD_HEADER
#include INF_HEADER


using namespace BUILD;

#include <string>
#include <memory>

using namespace std::literals::string_literals;
using namespace INF;

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


 int Buildings::getCapacity(BUILD::BuildingsEnum name) {
	DEBUG_FUNCTION("Buildings.cpp", "getCapacity");
	DEBUG_FUNCTION_END;

	return getResourceBuilding(name)->getCapacity();
}

int Buildings::getResourceBuildingProduction(int buildingNumber) {
	DEBUG_FUNCTION("Buildings.cpp", "getResourceProduction");

	ResourceBuildings* building;
	building = getResourceBuilding((BuildingsEnum)buildingNumber); 
	DEBUG_FUNCTION_END;
	return building->getProductionRate();   
}

/*Use returnArray or returnInt for arrayArg*/
INF::i5array Buildings::getResourceProduction(BUILD::BuildingsEnum building, INF::Quantity amount) {
	DEBUG_FUNCTION("Buildings.cpp", "getResourceProduction");

	i5array returnArray = {};
	for (int x = 0; x < 5; x++) { 
		returnArray[x] = getResourceBuildingProduction(x); 
	}

	if (amount == SINGLE) { 
		returnArray[0] = getResourceBuildingProduction(building);  
	}
	DEBUG_FUNCTION_END;
	return returnArray;
}


void Buildings::mutateLevel(BuildingsEnum name, MutateDirection direction, int amount) {
	DEBUG_FUNCTION("Buildings.cpp", "mutateLevel");
	if (name < 5) {
		ResourceBuildings* building = &resourceBuildings.at(name);  
		building->mutateLevel(amount, direction); 
	}

	if (direction == DECREASE) { amount *= -1; }
	DEBUG_FUNCTION_END;
	allBuildings.at(name)->increaseLevel(amount); 
}

/*Return the amount of troops trained this turn - troopsTrainedThisTurn*/
int Buildings::getTroopsTrainedThisTurn() {
	DEBUG_FUNCTION("Buildings.cpp", "getTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *allBuildings.at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	DEBUG_FUNCTION_END;
	return barracks.getTroopsTrainedThisTurn(); 
}

void Buildings::printBuildingStats() {
	DEBUG_FUNCTION("Buildings.cpp", "printBuildingStats");

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
	DEBUG_FUNCTION_END;

}

//Returns average of all Buildings.cpp", "rounded down to nearest int
int Buildings::getProvinceLevel() {
	//For debugging
	DEBUG_FUNCTION("Buildings.cpp", "getProvinceLevel");

	int unitLevel = 0;
	for (int x = 0; x < 10; x++) { unitLevel += allBuildings.at(x)->getLevel(); }
	DEBUG_FUNCTION_END;
	return unitLevel /= 10;;
}

void Buildings::resetTroopsTrainedThisTurn() {
	//For debugging
	DEBUG_FUNCTION("Buildings.cpp", "resetTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *allBuildings.at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	barracks.resetTroopsTrainedThisTurn();
	DEBUG_FUNCTION_END;
}

void Buildings::addTroopsTrainedThisTurn(int amount) {
	//For debugging
	DEBUG_FUNCTION("Buildings.cpp", "addTroopsTrainedThisTurn");
	BuildingsBASE& building_ref = *allBuildings.at(BARRACKS);
	Barracks& barracks = static_cast<Barracks&>(building_ref);
	barracks.addTroopsTrainedThisTurn(amount);
	DEBUG_FUNCTION_END;
}

//Do something in Buildings here
void Buildings::initiailizeCapitalBuildings() {
	//For debugging
	DEBUG_FUNCTION("Buildings.cpp", "initializeCapitalBuildings");

	i5array resourceBuildingsLevels, otherBuildingsLevels;
	resourceBuildingsLevels = getTypeLevels(RESOURCE);
	otherBuildingsLevels = getTypeLevels(OTHER);

	for (int x = 0; x < 10; x++) {
		allBuildings.at(x)->increaseLevel(1); 
	}
	DEBUG_FUNCTION_END;
}

void Buildings::printListOfBuildings() {
	//For debugging
	DEBUG_FUNCTION("Buildings.cpp", "printListOfBuildings");
	for (int x = 0; x < 10; x++) {
		std::cout << x << ") " << BUILD::BuildingStrings.at(x) << ", level: " << allBuildings.at(x)->getLevel(); 
	}
	DEBUG_FUNCTION_END;
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