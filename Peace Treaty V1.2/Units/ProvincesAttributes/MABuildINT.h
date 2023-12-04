#ifndef BUILDMAINTERFACE_H
#define BUILDMAINTERFACE_H

#include <iostream>
#include "BUILD.h"

using namespace BUILD;

class MABuildINT
{
protected:
	virtual void playerBuildFunction() = 0;
	virtual void upgradeBuildings() = 0;
	virtual void upgradeBuildings2(char optionChar) = 0;
	virtual void printInformation(INF::d5array requiredresources, int buildingindex) = 0;
};

#endif