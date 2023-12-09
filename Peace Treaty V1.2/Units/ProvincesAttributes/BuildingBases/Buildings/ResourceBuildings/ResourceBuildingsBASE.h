#ifndef RESOURCEBUILDINGSBASE_H
#define RESOURCEBUILDINGSBASE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include INF_HEADER
#include BUILDINGS_BASE_HEADER

class ResourceBuildingsBASE : public BuildingsBASE{
public:
	//Potentiall add upgrade rate-- different buildings increase their production amounts at different rates
	ResourceBuildingsBASE(INF::d5array upgradeRates);

	void updateProductionRate(int level);
	int getProudctionRate();
	int getCapacityAmount();
private:
	INF::i5array productionRate;
	INF::i5array capacityAmount; // add implementation
	//i5array Provinces::capacityAmounts = { 10,10,10,10,10 };
};

#endif