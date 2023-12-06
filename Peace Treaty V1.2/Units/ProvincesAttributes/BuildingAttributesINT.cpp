#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Provinces.h"



Provinces::BuildingAttributesINT() {
	//For debugging
	INF::debugFunction("Buildings, OtherBuildingsToString");
}

/*Use returnArray or returnInt for arrayArg*/
int Provinces::getCapacity(BUILD::BuildingsEnum name) {
	//For debugging
	INF::debugFunction("Buildings, getCapacity");

	Resource
}

/*Use returnArray or returnInt for arrayArg*/
i5array Provinces::getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) {
	//For debugging
	INF::debugFunction("Buildings, getResourceProduction");

	i5array arrayCopy, returnArray;
	BuildingsBASE* building = getBuilding(name);


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
void Provinces::mutateLevel(BUILD::BuildingType type, int name, i5array amount, INF::Quantity quant, INF::MutateDirection direction) {
	//For debugging
	INF::debugFunction("Buildings, mutateLevel");

	i5array arrayCopy = *levels.first;
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
			arrayCopy = INF::mutateArray(arrayCopy, amount, direction);
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
int Provinces::getTroopsTrainedThisTurn() {
	//For debugging
	INF::debugFunction("Buildings, getTroopsTrainedThisTurn");

	return troopsTrainedThisTurn;
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

	for (int x : resourceBuildingsLevels)
		unitLevel += resourceBuildingsLevels[x];
	for (int x : otherBuildingsLevels)
		unitLevel += x;

	unitLevel /= (int)resourceBuildingsLevels.size() + (int)otherBuildingsLevels.size();
	return unitLevel;

}

void Provinces::resetTroopsTrainedThisTurn()

{
	//For debugging
	INF::debugFunction("Buildings, resetTroopsTrainedThisTurn");

	troopsTrainedThisTurn = 0;
}

void Provinces::addTroopsTrainedThisTurn(int amount)
{
	//For debugging
	INF::debugFunction("Buildings, addTroopsTrainedThisTurn");

	troopsTrainedThisTurn += amount;
}

void Provinces::initiailizeCapitalBuildings() {
	//For debugging
	INF::debugFunction("Buildings, initializeCapitalBuildings");

	for (int& x : resourceBuildingsLevels) {
		x = 1;
	}
	for (int& x : otherBuildingsLevels) {
		x = 1;
	}
}

void Provinces::displayListOfBuildings() {
	//For debugging
	INF::debugFunction("Buildings, displayListOfBuildings");
	for (int x = 0; x < 10; x++) {
		std::cout << x << ") " << BUILD::BuildingStrings.at(x) << ", level: " << buildings.at(x).getLevel();
	}
}

std::shared_ptr<BuildingsBASE> Provinces::getBuilding(BUILD::BuildingsEnum type) {
	return buildings.at(type);
}
