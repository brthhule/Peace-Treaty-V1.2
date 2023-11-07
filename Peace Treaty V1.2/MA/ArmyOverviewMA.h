#ifndef ARMYOVERVIEWMA_H
#define ARMYOVERVIEWMA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


#include "../Units/Database.h"

#include "../Units/Participants.h"
#include "../Misc/OF.h"
#include "../Input.h"

extern Database db;

class ArmyOverviewMA
{
public:
	virtual void 
		printCosts(std::vector<int>costs, std::string type) = 0,
		armyDeploymentMF() = 0,
		trainCommanders() = 0,
		proceedWithTraining(std::array <int,5> trainCosts) = 0,
		upgradeCommandersOne() = 0,
		upgradeCommandersTwo() = 0,
		viewArmyOverview() = 0,
		deployCommanderMF() = 0;
};

#endif