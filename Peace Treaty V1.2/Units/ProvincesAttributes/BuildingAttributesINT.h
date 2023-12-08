#ifndef BUILDINGATTRIBUTESINT_H
#define BUILDINGATTRIBUTESINT_H

#include <iostream>
#include <array>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include BUILDING_ATTRIBUTES_INT_HEADER
#include INF_HEADER
#include BUILD_HEADER
#include BUILDINGS_BASE_HEADER
#include ALL_UNITS_HEADER

using namespace INF;
using namespace BUILD;

//Methods and variables in Provinces that relate to Buildings
class BuildingAttributesINT{
public:	
	/*These are functions*/

	i5array getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount);
	int getCapacity(BUILD::BuildingsEnum name);

	void mutateLevel(
		BUILD::BuildingType type, 
		int name, INF::i5array amount, 
		INF::Quantity quant, 
		INF::MutateDirection direction);

	int getTroopsTrainedThisTurn();
	int getProvinceLevel();
	
	//Void Accessors
	void printBuildingStats();
	void displayListOfBuildings();
	//Other modifiers
	void addTroopsTrainedThisTurn(int amount);
	void resetTroopsTrainedThisTurn();
	void initiailizeCapitalBuildings();
	void initializeEmptyBuildings();

	std::shared_ptr<BuildingsBASE> getBuilding(BUILD::BuildingsEnum type);

protected:
	int troopsTrainedThisTurn;
	//foodConsumption; variable, in AllUnits

	//Keep track of building levels
	i5array resourceBuildingsLevels;
	i5array otherBuildingsLevels;

	std::array<BuildingsBASE, 10> buildings;
private:
	//First is RESOURCE, second is OTHER
	std::pair<i5array*, i5array*> levels;

	static i5array capacityAmounts;
	static i5array resourceProduction;
};
#endif
