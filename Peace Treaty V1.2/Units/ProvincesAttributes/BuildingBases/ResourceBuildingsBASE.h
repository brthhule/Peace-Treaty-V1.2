#ifndef RESOURCEBUILDINGSBASE_H
#define RESOURCEBUILDINGSBASE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\INF.h"

class ResourceBuildingsBase {
public:
	ResourceBuildingsBase();

private:
	INF::i5array productionRates();
	INF::i5array capacityAmounts; // add implementation
	//i5array Provinces::capacityAmounts = { 10,10,10,10,10 };
};

#endif