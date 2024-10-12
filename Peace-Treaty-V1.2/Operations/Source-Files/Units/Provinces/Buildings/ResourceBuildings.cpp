#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include RESOURCE_BUILDINGS_HEADER

ResourceBuildings::ResourceBuildings() {

}

ResourceBuildings::ResourceBuildings(ResourceBuildingType type) {
	this->type = type;
	this->productionRate = 1;
	this->capacity = 0;
	this->maximumCapacity = 2;
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

void ResourceBuildings::mutateLevel(int amount, INF::MutateDirection direction) {
	if (direction == INF::MutateDirection::DECREASE)  {
		amount *= -1;
	}
	this->level += amount;
}
