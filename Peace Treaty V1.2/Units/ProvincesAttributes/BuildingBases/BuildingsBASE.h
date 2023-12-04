#ifndef BUILDINGSBASE_H
#define BUILDINGSBASE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\INF.h"

class BuildingsBASE {
public:
	BuildingsBASE(INF::d5array baseUpgradeRatesArg);

	void increaseLevel(int amount);
	int getLevel();

	INF::d5array getUpgradeCosts();
private:
	int level;
	INF::d5array baseUpgradeRates;

};
#endif