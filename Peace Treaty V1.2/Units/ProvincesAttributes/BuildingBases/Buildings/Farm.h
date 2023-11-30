#ifndef FARM_H
#define FARM_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\BuildingsBASE.h"

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\INF.h"

class Farm : public BuildingsBASE {
public:
	Farm();
	updateProductionRates();
private:
	INF::i5array baseProductionRates;
	INF::i5array currentProductionRates;
};

#endif