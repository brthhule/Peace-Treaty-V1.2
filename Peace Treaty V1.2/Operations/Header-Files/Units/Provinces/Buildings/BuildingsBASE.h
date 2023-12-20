//BuildingsBASE.h
//Base Class
//Extended by Buildings units (Farm, Mill, Barracks, etc)

/*Notes:
- Have to implement workers/buildiner/civillians functionality
*/

#ifndef BUILDINGSBASE_H
#define BUILDINGSBASE_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INF_HEADER

using namespace INF;

class BuildingsBASE {
public:
	//----Constructors---------------------------------------------------------
	BuildingsBASE(){}
	BuildingsBASE(INF::d5array baseUpgradeRatesArg);
	~BuildingsBASE(){}

	//----Getters--------------------------------------------------------------
	constINT getLevel();
	constINT getWorkersNum();
	constArrayReference getUpgradeCosts(); 

	//----Mutators-------------------------------------------------------------
	void increaseLevel(int amount);
	void mutateWorkersNum(int amount, INF::MutateDirection direction);

	INF::i5array updateProductionRates(int level);

private:
	int level;
	INF::d5array baseUpgradeRates;
	int workersNum;
	i5array upgradeCosts;
};
#endif