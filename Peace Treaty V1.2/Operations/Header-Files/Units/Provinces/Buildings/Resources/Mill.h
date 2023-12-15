#ifndef MILL_H
#define MILL_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\Buildings\ResourceBuildings\ResourceBuildingsBASE.h"


class Mill : public ResourceBuildingsBASE {
public:
	Mill();
private:
	INF::i5array baseProductionRates;
};

#endif