#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\Buildings\Farm.h"

//Parameters for BuildingBASE are the upgradeRates
Farm::Farm() : BuildingsBASE ({ 1,2,3,4,5 }) {
	//Do nothing
}

INF::i5array Farm::updateProductionRates(int level) {
	for (int x = 0; x < 5; x++) {
		int newNum = level * currentProductionRates.at(x);
		currentProductionRates.at(x) = newNum;
	}
}