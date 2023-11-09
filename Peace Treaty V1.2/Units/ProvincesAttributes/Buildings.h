#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <iostream>
#include <array>

#include "Misc/CV.h"
#include "Misc/OF.h"
#include "Build.h"

#include "../AllUnits.h"

using namespace CV;
using namespace OF;
using namespace Build;

class Buildings{
public:
	Buildings();

	
	/*These are functions*/
	std::array<int, 5> 
		getBuildingLevel(Build::BuildingType type, int index, CV::Quantity quant),
		getResourceProduction(Build::ResourceBuildings name, CV::Quantity amount),
		getCapacity(Build::BuildingType type, int name, CV::Quantity amount);

	void mutateLevel(Build::BuildingType type, int name, std::array<int,5> amount, CV::Quantity quant, CV::MutateDirection direction);

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
	//First is RESOURCE, second is OTHER
	std::pair<std::array<int, 5>*, std::array<int, 5>*> levels = { &resourceBuildingsLevels, &otherBuildingsLevels };

	std::array<int, 5> 
		capacityAmounts = { 10,10,10,10,10 },
		resourceProduction = { 5,4,3,2,1 };
};
#endif
