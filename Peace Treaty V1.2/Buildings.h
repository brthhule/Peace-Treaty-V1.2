#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <iostream>
#include <array>

#include "Misc/ConstValues.h"
#include "Misc/OF.h"
#include "Build.h"
#include "Units/AllUnits.h"

using namespace CV;
using namespace OF;
using namespace Build;

class Buildings{
public:
	Buildings();

	
	template<typename T>
	std::array<int, 5> getBuildingLevel(Build::BuildingType type, int index, CV::Quantity quant, std::array<T, 5> arrayArg);
	
	template<typename T>
	std::array<int, 5> getResourceProduction(Build::ResourceBuildings name, CV::Quantity amount, std::array<T, 5> arrayArg);

	template<typename T>
	std::array<int, 5> getCapacity(Build::BuildingType type, int name, CV::Quantity amount, std::array<T, 5> arrayArg);

	template<typename T> 
	T mutateLevel(Build::BuildingType type, int name, T amount, CV::Quantity quant, CV::MutateDirection direction);

	int 
		getTroopsTrainedThisTurn(),
		getProvinceLevel();
	
	//Void Accessors
	void 
		printBuildingStats(),
		displayListOfBuildings();
	//Other modifiers
	void
		addTroopsTrainedThisTurn(int amount),
		resetTroopsTrainedThisTurn(),
		initiailizeCapitalBuildings(),
		initializeEmptyBuildings();

protected:
	static std::array<int, 5> returnArray;
	static std::array<std::string, 5> returnInt;

	int troopsTrainedThisTurn;//variable
	// foodConsumption;//variable, in AllUnits

	
	std::array<int, 5>
		//Keep track of building levels
		resourceBuildingsLevels,
		otherBuildingsLevels;

	std::array<double, 5>
		//For upgrades
		farmUR = { 1, 0.5, 0.25, 0.125, 0.0625 },
		millUR = { 2, 1, 0.5, 0.25, 0.125 },
		quarryUR = { 3, 2, 1, 0.5, 0.25 },
		mineUR = { 4, 3, 2, 1, 0.5 },
		churchUR = { 5, 4, 3, 2, 1 },
		barracksUR = { 1, 1, 1, 1, 0.2 },
		infirmaryUR = { 1, 1, 1, 1, 0.2 },
		libraryUR = { 1, 1, 1, 1, 0.2 },
		wallUR = { 1, 1, 1, 1, 0.2 },
		residencesUR = {};

	const std::array<std::array<double, 5>, 10> upgradeRates =
	{
		farmUR, 
		millUR,
		quarryUR, 
		mineUR, 
		churchUR, 
		barracksUR,
		infirmaryUR, 
		libraryUR, 
		wallUR, 
		residencesUR
	};

private:
	std::array<std::array<int, 5>*, 2> levels = { &resourceBuildingsLevels, &otherBuildingsLevels };

	std::array<int, 5> 
		capacityAmounts = { 10,10,10,10,10 },
		resourceProduction = { 5,4,3,2,1 };
};
#endif
