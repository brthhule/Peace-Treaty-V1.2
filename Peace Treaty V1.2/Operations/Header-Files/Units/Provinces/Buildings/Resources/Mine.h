#ifndef MINE_H
#define MINE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include RESOURCE_BUILDINGS_BASE_HEADER

class Mine : public ResourceBuildingsBASE {
public:
	Mine();
private:
	INF::i5array baseProductionRates;
};

#endif