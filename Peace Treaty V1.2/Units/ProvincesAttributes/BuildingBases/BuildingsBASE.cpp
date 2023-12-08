#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\BuildingsBASE.h"

BuildingsBASE::BuildingsBASE(INF::d5array baseUpgradeRatesArg) {
	level = 0; 
	baseUpgradeRates = baseUpgradeRatesArg;
}

void BuildingsBASE::increaseLevel(int amount) {
	level += amount;
}

int BuildingsBASE::getLevel() {
	return level;
}

INF::i5array BuildingsBASE::getUpgradeCosts() {
	INF::d5array upgradeCosts = {};

	for (int index = 0; index < 5; index++) {
		upgradeCosts.at(index) = level * baseUpgradeRates.at(index);
	}

	return upgradeCosts;
}


void BuildingsBASE::mutateWorkersNum(int amount, INF::MutateDirection direction) {
	int sign = -1;
	if (direction) {
		sign = 1;
	}

	workersNum += amount * sign;
}

int BuildingsBASE::getWorkersNum() {
	return workersNum;
}