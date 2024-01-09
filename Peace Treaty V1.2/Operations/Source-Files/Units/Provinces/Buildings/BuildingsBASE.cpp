#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include BUILDINGS_BASE_HEADER

using namespace INF;
BuildingsBASE::BuildingsBASE(INF::d5array baseUpgradeRatesArg) {
	level = 0; 
	baseUpgradeRates = baseUpgradeRatesArg;
	workersNum = 0;
	upgradeCosts = {};
	for (int index = 0; index < 5; index++) {
		upgradeCosts.at(index) = (int)baseUpgradeRates.at(index);
	}
}

/*
BuildingsBASE::BuildingsBASE(BuildingsBASE&& original) {
	level = original.level;
	baseUpgradeRates = original.baseUpgradeRates;
	upgradeCosts = original.upgradeCosts;
	workersNum = original.workersNum;
}*/

BuildingsBASE::BuildingsBASE() : BuildingsBASE({0.0, 0.0, 0.0, 0.0, 0.0}) { }

void BuildingsBASE::increaseLevel(int amount) {
	level += amount;

	for (int index = 0; index < 5; index++) { 
		upgradeCosts.at(index) = level * ((int) baseUpgradeRates.at(index)); 
	}
}

constINT BuildingsBASE::getLevel() const { return level; }

constArrayRef BuildingsBASE::getUpgradeCosts() {
	return upgradeCosts;
}


void BuildingsBASE::mutateWorkersNum(int amount, INF::MutateDirection direction) {
	int sign = -1;
	if (direction) { sign = 1;}

	workersNum += amount * sign;
}

constINT BuildingsBASE::getWorkersNum() const {
	return workersNum;
}
