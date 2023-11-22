#ifndef BUILDINGENTITIESBASE_H
#define BUILDINGENTITIESBASE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\INF.h"

class BuildingEntitiesBase {
public:
	BuildingEntitiesBase(INF::i5array baseUpgradeRatesArg);

	void increaseLevel(int amount);
	int getLevel();

	INF::i5array getUpgradeCosts();
private:
	int level;
	INF::i5array baseUpgradeRates;
};
#endif