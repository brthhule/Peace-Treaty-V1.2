#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include RESOURCE_BUILDINGS_BASE_HEADER

ResourceBuildingsBASE::ResourceBuildingsBASE(INF::d5array upgradeRates) : BuildingsBASE(upgradeRates) {
	productionRate = 0;
	capacityAmount = 0;
}

void ResourceBuildingsBASE::updateProductionRate(int level) {
	productionRate = level;
	capacityAmount = productionRate * 5;
}

constINT ResourceBuildingsBASE::getProductionRate() {
	return productionRate;
}

constINT ResourceBuildingsBASE::getCapacityAmount() {
	return capacityAmount;
}