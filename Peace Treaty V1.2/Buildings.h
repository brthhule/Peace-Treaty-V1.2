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
	T getBuildingLevel(Build::BuildingType type, int index, CV::Quantity quant, T returnType);
	
	template<typename T>
	T getResourceProduction(Build::ResourceBuildings name, CV::Quantity amount, T returnType);

	template<typename T>
	T getCapacity(Build::BuildingType type, int name, CV::Quantity amount, T returnType);

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
		addTroopsTrainedThisTurn(int amount),
		initiailizeCapitalBuildings(),
		initializeEmptyBuildings();

protected:
	static std::array<int, 5> returnArray;
	static int returnInt;

	int troopsTrainedThisTurn;//variable
	// foodConsumption;//variable, in AllUnits

	
	std::array<int, 5>
		//Keep track of building levels
		resourceBuildingsLevels,
		otherBuildingsLevels,

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

	const std::array<std::array<int, 5>, 10> upgradeRates =
	{
		farmUR, millUR, quarryUR, mineUR, churchUR, barracksUR, infirmaryUR, libraryUR, wallUR, residencesUR
	};

private:
	std::array<std::array<int, 5>*, 2> levels = { &resourceBuildingsLevels, &otherBuildingsLevels };

	std::array<int, 5> 
		capacityAmounts = { 10,10,10,10,10 },
		resourceProduction = { 5,4,3,2,1 };
};
#endif
