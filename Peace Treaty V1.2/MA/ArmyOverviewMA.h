#ifndef ARMYOVERVIEWMA_H
#define ARMYOVERVIEWMA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Mobility.h"
#include "../Units/Database.h"

#include "../Units/Participants.h"
#include "../Misc/OtherFunctions.h"

extern Database db;


#define UNIT_SIZE 5

class ArmyOverviewMA
{
public:
	//constructor
	ArmyOverviewMA();

	//Accessors
	void printCosts(std::vector<int>costs, std::string type);

	//Other Function stuff
	void armyDeploymentMF();
	void trainCommanders();
	void proceedWithTraining(std::array <int,5> trainCosts);
	void upgradeCommandersOne();
	void upgradeCommandersTwo();
	void viewArmyOverview();
	void deployCommanderMF();
	
private:
	Participants *participant;
	int commandersNum;
	OtherFunctions OF;
	std::string commanderName;
};

#endif