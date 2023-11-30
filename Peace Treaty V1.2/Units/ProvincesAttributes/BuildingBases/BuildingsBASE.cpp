#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\BuildingsBASE.h"

BuildingsBASE::BuildingsBASE(INF::i5array baseUpgradeRatesArg) {
	level = 0; 
	baseUpgradeRates = baseUpgradeRatesArg;
}

void BuildingsBASE::increaseLevel(int amount) {
	level += amount;
}

int BuildingsBASE::getLevel() {
	return level;
}

INF::i5array BuildingsBase::getUpgradeCosts() {
	INF::i5array upgradeCosts = {};

	for (int index = 0; index < 5; index++) {
		upgradeCosts.at(index) = getLevel() * baseUpgradeRates.at(index);
	}

	return upgradeCosts;
}