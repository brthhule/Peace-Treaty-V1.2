#ifndef BUILDINGATTRIBUTESINT_H
#define BUILDINGATTRIBUTESINT_H

#include <iostream>
#include <array>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include INF_HEADER
#include BUILD_HEADER
#include BUILDINGS_BASE_HEADER
#include PRIME_UNITS_HEADER
#include BARRACKS_HEADER

using namespace INF;
using namespace BUILD;

//Methods and variables in Provinces that relate to Buildings
class BuildingAttributesINT{
public:	
	///////////////////////////////////Constructors////////////////////////////
	BuildingAttributesINT(){}
	~BuildingAttributesINT(){}

	///////////////////////////////////Getters/////////////////////////////////
	virtual constArrayReference getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) = 0;
	//Returns an array of Resource/Other buildings levels
	virtual i5array getTypeLevels(BUILD::BuildingType type) = 0;

	
	virtual const int getCapacity(BUILD::BuildingsEnum name) const = 0;
	/** getTroopsTrainedThisTurn__
		returns the amount of troops trained this turn

			@param void
			@return void
	*/
	virtual constINT getTroopsTrainedThisTurn() = 0;
	/** getProvinceLevel__ returns the level of this province by averaging all building levels

			@param void
			@return void
	*/
	virtual constINT getProvinceLevel() = 0;

	virtual BuildingsBASE& getBuilding(BUILD::BuildingsEnum name) = 0;
	virtual BuildingsBASE& getBuilding(int num) = 0;

	///////////////////////////////////Setters/////////////////////////////////
	/** mutateLevel__
			Changes the level of a building

			@param name__
			the name of the building being changed
			@param direction__
			changing the level in an increasing/decreasing direction
			@param amount__
			the amount the level is being changed by, usually 1, always positive
			@return void
	*/
	virtual void mutateLevel(BuildingsEnum name, MutateDirection direction, int amount) = 0; 
	virtual void addTroopsTrainedThisTurn(int amount) = 0;
	virtual void resetTroopsTrainedThisTurn() = 0;
	virtual void initiailizeCapitalBuildings() = 0;

	///////////////////////////////////Printers////////////////////////////////
	virtual void printBuildingStats() = 0;
	virtual void printListOfBuildings() = 0;
};
#endif
