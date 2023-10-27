#ifndef BUILDMA_H
#define BUILDMA_H

#include <iostream>
#include "../Build.h"

using namespace Build;

class BuildMA
{
protected:
	//BuildMA() {};
	//~BuildMA() {};
	void virtual
		playerBuildFunction() = 0,
		upgradeBuildings() = 0,
		upgradeBuildings2(char optionChar) = 0,
		printInformation(Build::BuildingType type, std::array<int, 5> requiredresources, int buildingindex) = 0;
};

#endif