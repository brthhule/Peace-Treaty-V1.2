//ArmyOverviewMA.h
//Implemented by: Participants

#ifndef ARMYOVERVIEWMA_H
#define ARMYOVERVIEWMA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"

#include INF_HEADER
#include INPUT_HEADER

class ArmyOverviewMA
{
protected:
	virtual void 
		printCosts(std::vector<int>costs, std::string type) = 0,
		armyDeploymentMF() = 0,
		trainCommanders() = 0,
		proceedWithTraining(std::array <int,5> trainCosts) = 0,
		upgradeCommander() = 0,
		viewArmyOverview() = 0,
		deployCommanderMF() = 0;
};

#endif