#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingBases\Buildings\ResourceBuildings\ResourceBuildingsBASE.h"

ResourceBuildingsBase::ResourceBuildingsBase(INF::i5array productionRates, INF::d5array upgradeRates) : BuildingsBASE(upgradeRates){
	this->productionRates = productionRates;
}