#ifndef BUILDMAINTERFACE_H
#define BUILDMAINTERFACE_H

#include <iostream>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include BUILD_HEADER

using namespace BUILD;

class MABuildINT
	USES_
		BUILD_ 
{
protected:
	virtual void mainBuildFunction() = 0;
	virtual void selectUpgradeBuilding() = 0;
	virtual void upgradeBuilding(char optionChar) = 0;
	virtual void printBuildingUpgradeCosts(INF::i5array requiredresources, int buildingindex) = 0;
};

#endif