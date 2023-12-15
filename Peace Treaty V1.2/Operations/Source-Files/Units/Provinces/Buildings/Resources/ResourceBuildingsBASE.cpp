#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\Buildings\ResourceBuildings\ResourceBuildingsBASE.h"

ResourceBuildingsBASE::ResourceBuildingsBASE(INF::d5array upgradeRates) : BuildingsBASE(upgradeRates) {
	proudctionRate = 0;
	capacityAmount = 0;
}

void ResourceBuildingsBASE::updateProductionRate(int level) {
	productionRate = level;
	capacityAmount = productionRate * 5;
}

void ResourceBuildingsBASE::getProudctionRate() {
	return productionRate;
}

int ResourceBuildingsBASE::getCapacityAmount() {
	return capacityAmount;
}