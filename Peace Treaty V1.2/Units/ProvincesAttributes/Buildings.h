#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <iostream>
#include <array>

#include "../Misc/INF.h"
#include "../Misc/INF.h"
#include "../ProvincesAttributes/Build.h"

#include "../AllUnits.h"

using namespace INF;

using namespace Build;

class Buildings{
public:
	Buildings();

	
	/*These are functions*/
	i5array getBuildingLevel(Build::BuildingType type, int index, INF::Quantity quant);
	i5array getResourceProduction(Build::ResourceBuildings name, INF::Quantity amount);
	i5array getCapacity(Build::BuildingType type, int name, INF::Quantity amount);

	void mutateLevel(
		Build::BuildingType type, 
		int name, std::array<int,5> amount, 
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

	//For upgrades
	static d5array farmUR;
	static d5array millUR;
	static d5array quarryUR;
	static d5array mineUR;
	static d5array churchUR;
	static d5array barracksUR;
	static d5array infirmaryUR;
	static d5array libraryUR;
	static d5array wallUR;
	static d5array residencesUR;

	static std::array<d5array, 10> upgradeRates;

private:
	//First is RESOURCE, second is OTHER
	std::pair<i5array*, i5array*> levels;

	static i5array capacityAmounts;
	static i5array resourceProduction;
};
#endif
