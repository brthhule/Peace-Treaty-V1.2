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

	i5array getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) = 0;
	int getCapacity(BUILD::BuildingsEnum name) = 0;

	//Returns an array of Resource/Other buildings levels
	i5array getTypeLevels(BUILD::BuildingType type);

	void mutateLevel(
		BUILD::BuildingType type, 
		int name, INF::i5array amount, 
		INF::Quantity quant, 
		INF::MutateDirection direction) = 0;

	int getTroopsTrainedThisTurn() = 0;
	int getProvinceLevel() = 0;
	
	//Void Accessors
	void printBuildingStats() = 0;
	void displayListOfBuildings() = 0;
	//Other modifiers
	void addTroopsTrainedThisTurn(int amount) = 0;
	void resetTroopsTrainedThisTurn() = 0;
	void initiailizeCapitalBuildings() = 0;
	void initializeEmptyBuildings() = 0;

	std::shared_ptr<BuildingsBASE> getBuilding(BUILD::BuildingsEnum name) = 0;

protected:
	int troopsTrainedThisTurn;
	//foodConsumption; variable, in AllUnits

	//Keep track of building levels
	i5array resourceBuildingsLevels;
	i5array otherBuildingsLevels;

	std::array<BuildingsBASE, 10> buildings;

	//Returns building levels for all Resource or Other type buildings
	std::array<int, 5> getTypeLevels(BUILD::BuildingType type) = 0;
private:
	static i5array capacityAmounts;
	static i5array resourceProduction;
};
#endif
