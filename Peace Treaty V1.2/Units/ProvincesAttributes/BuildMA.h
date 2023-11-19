#ifndef BUILDMA_H
#define BUILDMA_H

#include <iostream>
#include "Build.h"

using namespace Build;

class BuildMA
{
protected:
	virtual void playerBuildFunction() = 0;
	virtual void upgradeBuildings() = 0;
	virtual void upgradeBuildings2(char optionChar) = 0;
	virtual void printInformation(Build::BuildingType type, std::array<int, 5> requiredresources, int buildingindex) = 0;
};

#endif