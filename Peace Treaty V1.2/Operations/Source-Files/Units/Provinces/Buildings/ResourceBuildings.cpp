#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include RESOURCE_BUILDINGS_HEADER

ResourceBuildings::ResourceBuildings(ResourceBuildingType type) {
	this->type = type;
}

int ResourceBuildings::getProductionRate() {
	return productionRate;
}

int ResourceBuildings::getMaximumCapacity() {
	return maximumCapacity;
}

int ResourceBuildings::getCapacity() {
	return capacity;
}