#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include BUILDINGS_BASE_HEADER

BuildingsBASE::BuildingsBASE(INF::d5array baseUpgradeRatesArg) {
	level = 0; 
	baseUpgradeRates = baseUpgradeRatesArg;
}

void BuildingsBASE::increaseLevel(int amount) {
	level += amount;

	for (int index = 0; index < 5; index++) { 
		upgradeCosts.at(index) = level * baseUpgradeRates.at(index); 
	}
}

constINT BuildingsBASE::getLevel() { 
	return &level; 
}

constArrayReference BuildingsBASE::getUpgradeCosts() {
	return &upgradeCosts;
}


void BuildingsBASE::mutateWorkersNum(int amount, INF::MutateDirection direction) {
	int sign = -1;
	if (direction) {
		sign = 1;
	}

	workersNum += amount * sign;
}

constINT BuildingsBASE::getWorkersNum() {
	return workersNum;
}