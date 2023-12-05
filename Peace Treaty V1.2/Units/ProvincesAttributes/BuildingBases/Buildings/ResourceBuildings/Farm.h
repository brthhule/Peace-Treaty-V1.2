#ifndef FARM_H
#define FARM_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\Buildings\ResourceBuildings\ResourceBuildingsBASE.h"

class Farm : public ResourceBuildingsBASE {
public:
	Farm();
private:
	INF::i5array baseProductionRates;
};

#endif