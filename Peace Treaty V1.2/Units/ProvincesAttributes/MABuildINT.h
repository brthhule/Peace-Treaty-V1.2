#ifndef BUILDMAINTERFACE_H
#define BUILDMAINTERFACE_H

#include <iostream>
#include "BUILD.h"

using namespace BUILD;

class MABuildINT
{
protected:
	virtual void mainBuildFunction() = 0;
	virtual void selectUpgradeBuilding() = 0;
	virtual void upgradeBuilding(char optionChar) = 0;
	virtual void printBuildingUpgradeCosts(INF::i5array requiredresources, int buildingindex) = 0;
};

#endif