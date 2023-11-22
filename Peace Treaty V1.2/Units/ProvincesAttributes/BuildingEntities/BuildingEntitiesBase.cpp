#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingEntities\BuildingEntitiesBase.cpp"



BuildingEntitiesBase::BuildingEntitiesBase(INF::i5array baseUpgradeRatesArg) {
	level = 0; 
	baseUpgradeRates = baseUpgradeRatesArg;
}

void BuildingEntitiesBase::increaseLevel(int amount) {
	level += amount;
}

int BuildingEntitiesBase::getLevel() {
	return level;
}

INF::i5array getUpgradeCosts() {
	INF::i5array upgradeCosts = {};

	for (int index = 0; index < 5; index++) {
		upgradeCosts.at(index) = getLevel() * baseUpgradeRates.at(index);
	}
}