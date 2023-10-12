#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <iostream>
#include <array>

#include "Misc/ConstValues.h"
#include "Misc/OF.h"
#include "Build.h"

using namespace CV;
using namespace OF;
using namespace Build;

class Buildings {
public:
	Buildings();

	template<typename T>
	T getBuildingLevel(Build::BuildingType type, int index, CV::Quantity quant, T returnType);
	
	template<typename T>
	T getResourceProduction(Build::ResourceBuildings name, CV::Quantity amount, T returnType);

	template<typename T>
	T getCapacity(Build::BuildingType type, int name, CV::Quantity amount, T returnType);

	template<typename T> 
	T mutateLevel(Build::BuildingType type, int name, T amount, CV::Quantity quant, CV::MutateDirection direction);

	int getTroopsTrainedThisTurn();
	void printBuildingStats();

	int getProvinceLevel();
	void resetTroopsTrainedThisTurn();

	void addTroopsTrainedThisTurn(int amount);

	void initiailizeCapitalBuildings();
	void initializeEmptyBuildings();

	void displayListOfBuildings();

	

private:
	const double requiredResourcesBuildings[6][5] = {
	{1, 0.5, 0.25, 0.125, 0.0625},
	{2, 1, 0.5, 0.25, 0.125},
	{3, 2, 1, 0.5, 0.25},
	{4, 3, 2, 1, 0.5},
	{5, 4, 3, 2, 1},
	{1, 1, 1, 1, 0.2} };

	//Linked to enum resourceBuildings
	std::array<int, 5> resourceBuildingsLevels;
	//Linked to enum OtherBuildings
	std::array<int, 5> otherBuildingsLevels;
	//enum OtherBuildings { BARRACKS, INFIRMARY, LIBRARY, WALL, RESIDENCES };
	std::array<std::array<int, 5>*, 2> levels = { &resourceBuildingsLevels, &otherBuildingsLevels };

	int troopsTrainedThisTurn;//variable
	int foodConsumption;//variable

	std::array<int, 5> capacityAmounts = { 10,10,10,10,10 };
	std::array<int, 5> resourceProduction = { 5,4,3,2,1 };

protected:
	static std::array<int, 5> returnArray;
	static int returnInt;
};
#endif
