//BuildingsBASE.h
//Base Class
//Extended by Buildings units (Farm, Mill, Barracks, etc)

/*Notes:
- Have to implement workers/buildiner/civillians functionality
*/

#ifndef BUILDINGSBASE_H
#define BUILDINGSBASE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"

#include INF_HEADER


class BuildingsBASE {
public:
	//----Constructors---------------------------------------------------------
	BuildingsBASE();
	BuildingsBASE(INF::d5array baseUpgradeRatesArg);
	//BuildingsBASE(const BuildingsBASE& original);
	~BuildingsBASE(){}

	//----Getters--------------------------------------------------------------
	INF::constINT getLevel() const;
	INF::constINT getWorkersNum() const;
	INF::constArrayRef getUpgradeCosts();

	//----Mutators-------------------------------------------------------------
	void increaseLevel(int amount);
	void mutateWorkersNum(int amount, INF::MutateDirection direction);

protected: 
	void mutateLevel(int amount, INF::MutateDirection direction);
	int level;

private:
	INF::d5array baseUpgradeRates;
	int workersNum;
	INF::i5array upgradeCosts;
};
#endif