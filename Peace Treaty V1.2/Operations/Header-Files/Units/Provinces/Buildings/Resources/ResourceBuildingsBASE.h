#ifndef RESOURCEBUILDINGSBASE_H
#define RESOURCEBUILDINGSBASE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include INF_HEADER
#include BUILDINGS_BASE_HEADER

class ResourceBuildingsBASE : public BuildingsBASE{
public:
	//Potentiall add upgrade rate-- different buildings increase their production amounts at different rates
	//ResourceBuildingsBASE(ResourceBuildingsBASE&& copy);
	ResourceBuildingsBASE(INF::d5array upgradeRates);

	void updateProductionRate(int level);
	INF::constINT getProductionRate();
	INF::constINT getCapacityAmount();
private:
	int productionRate;
	int capacityAmount; // add implementation
	//i5array Provinces::capacityAmounts = { 10,10,10,10,10 };
};

#endif