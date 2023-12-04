#ifndef BUILDINGATTRIBUTES_H
#define BUILDINGATTRIBUTES_H

#include <iostream>
#include <array>

#include "../Misc/INF.h"
#include "../Misc/INF.h"
#include "../ProvincesAttributes/Build.h"
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\BuildingsBASE.h"

#include "../AllUnits.h"

using namespace INF;

using namespace BUILD;

class BuildingAttributesINT{
public:	
	/*These are functions*/
	i5array getBuildingLevel(BUILD::BuildingsEnum type, int index, INF::Quantity quant);
	i5array getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount);
	i5array getCapacity(BUILD::BuildingType type, int name, INF::Quantity amount);

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
