#ifndef BUILDINGSBASE_H
#define BUILDINGSBASE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\FilePaths.h";

#include INF_H

//Have to implement workers/buildiner/civillians functionality
class BuildingsBASE {
public:
	BuildingsBASE(INF::d5array baseUpgradeRatesArg);

	void increaseLevel(int amount);
	int getLevel();

	INF::i5array getUpgradeCosts();
	INF::i5array updateProductionRates(int level);

	void mutateWorkersNum(int amount, INF::MutateDirection direction);
	int getWorkersNum();

private:
	int level;
	INF::d5array baseUpgradeRates;
	int workersNum;
};
#endif