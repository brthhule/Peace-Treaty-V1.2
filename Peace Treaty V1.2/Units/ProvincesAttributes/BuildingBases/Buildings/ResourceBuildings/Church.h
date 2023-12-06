#ifndef CHURCH_H
#define CHURCH_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\FilePaths.h"
#include RESOURCE_BUILDINGS_BASE_H

class Church : public ResourceBuildingsBASE {
public:
	Church();
private:
	INF::i5array baseProductionRates;
};

#endif