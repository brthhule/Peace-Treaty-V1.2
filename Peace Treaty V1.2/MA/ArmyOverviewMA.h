#ifndef ARMYOVERVIEWMA_H
#define ARMYOVERVIEWMA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Mobility.h"
#include "../Units/Database.h"

#include "../Units/Participants.h"
#include "../Misc/OF.h"
#include "../Input.h"

extern Database db;

class ArmyOverviewMA
{
public:
	//constructor
	ArmyOverviewMA();

	void 
		printCosts(std::vector<int>costs, std::string type),
		armyDeploymentMF(),
		trainCommanders(),
		proceedWithTraining(std::array <int,5> trainCosts),
		upgradeCommandersOne(),
		upgradeCommandersTwo(),
		viewArmyOverview(),
		deployCommanderMF();
	
private:
	Participants *participant;
	int commandersNum;
	
	std::string commanderName;
};

#endif