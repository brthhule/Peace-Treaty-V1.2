#ifndef QUARRY_H
#define QUARRY_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include RESOURCE_BUILDINGS_BASE_HEADER

class Quarry : public ResourceBuildingsBASE {
public:
	Quarry();
private:
	INF::i5array baseProductionRates;
};

#endif