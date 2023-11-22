//ArmyOverviewMA.h
//Implemented by: Participants

#ifndef ARMYOVERVIEWMA_H
#define ARMYOVERVIEWMA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "../Units/Misc/INF.h"
#include "../Units/Misc/Input.h"


class ArmyOverviewMA
{
protected:
	virtual void 
		printCosts(std::vector<int>costs, std::string type) = 0,
		armyDeploymentMF() = 0,
		trainCommanders() = 0,
		proceedWithTraining(std::array <int,5> trainCosts) = 0,
		upgradeCommander() = 0,
		upgradeCommander() = 0,
		viewArmyOverview() = 0,
		deployCommanderMF() = 0;
};

#endif