#ifndef CHURCH_H
#define CHURCH_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\Buildings\ResourceBuildings\ResourceBuildingsBASE.h"

class Church : public ResourceBuildingsBase {
public:
	Church();
private:
	INF::i5array baseProductionRates;
};

#endif