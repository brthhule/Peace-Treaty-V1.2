#ifndef MINE_H
#define MINE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\Buildings\ResourceBuildings\ResourceBuildingsBASE.h"

class Mine : public ResourceBuildingsBase {
public:
	Mine();
private:
	INF::i5array baseProductionRates;
};

#endif