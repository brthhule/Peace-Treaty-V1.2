#ifndef RESOURCE_BUILDINGS
#define RESOURCE_BUILDINGS

#include "..\..\..\..\..\Support\Paths.h"
#include BUILDINGS_BASE_HEADER

class ResourceBuildings : BuildingsBASE {
public:
	static enum ResourceBuildingType {
		FOOD, WOOD, STONE, ORE, MANA
	};

	ResourceBuildings();
	ResourceBuildings(ResourceBuildingType type);

	int getProductionRate();

	int getMaximumCapacity();

	int getCapacity();

	void mutateLevel(int amount, INF::MutateDirection direction);

private:
	ResourceBuildingType type;
	int productionRate;
	int capacity;
	int maximumCapacity;

};

#endif