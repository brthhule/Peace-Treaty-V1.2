#ifndef BUILDMAINTERFACE_H
#define BUILDMAINTERFACE_H

#include <iostream>
#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INF_HEADER

class BuildMA {
public:
	//----Constructors---------------------------------------------------------
	BuildMA(){}
	~BuildMA(){}

	virtual void upgradeBuildingPrompt() = 0;
	virtual void selectBuildingToUpgrade() = 0;
	virtual void upgradeBuilding(int buildingNumber) = 0;
	virtual void printBuildingUpgradeCosts(INF::i5array requiredResources, int buildingindex) = 0;
};

#endif