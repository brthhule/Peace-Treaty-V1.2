#ifndef BUILDINGATTRIBUTESINT_H
#define BUILDINGATTRIBUTESINT_H

#include <iostream>
#include <array>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include BUILDING_ATTRIBUTES_INT_HEADER
#include INF_HEADER
#include BUILD_HEADER
#include BUILDINGS_BASE_HEADER
#include ALL_UNITS_HEADER

using namespace INF;
using namespace BUILD;

//Methods and variables in Provinces that relate to Buildings
virtual class BuildingAttributesINT{
public:	
	/*These are functions*/
	virtual i5array getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) = 0;
	virtual int getCapacity(BUILD::BuildingsEnum name) = 0;

	//Returns an array of Resource/Other buildings levels
	virtual const std::array<int&, 5> getTypeLevels(BUILD::BuildingType type) = 0;

	virtual void mutateLevel(
		BUILD::BuildingType type, 
		int name, INF::i5array amount, 
		INF::Quantity quant, 
		INF::MutateDirection direction) = 0;

	virtual int getTroopsTrainedThisTurn() = 0;
	virtual int getProvinceLevel() = 0;
	
	//Void Accessors
	virtual void printBuildingStats() = 0;
	virtual void displayListOfBuildings() = 0;
	//Other modifiers
	virtual void addTroopsTrainedThisTurn(int amount) = 0;
	virtual void resetTroopsTrainedThisTurn() = 0;
	virtual void initiailizeCapitalBuildings() = 0;
	virtual void initializeEmptyBuildings() = 0;

	virtual std::shared_ptr<BuildingsBASE> getBuilding(BUILD::BuildingsEnum name) = 0;

protected:
	int troopsTrainedThisTurn;
	//foodConsumption; variable, in AllUnits

	//Keep track of building levels
	i5array resourceBuildingsLevels;
	i5array otherBuildingsLevels;

	std::array<BuildingsBASE, 10> buildings;

	//Returns building levels for all Resource or Other type buildings
private:
	static i5array capacityAmounts;
	static i5array resourceProduction;
};
#endif
