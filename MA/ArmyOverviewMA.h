#ifndef ARMYOVERVIEWMA_H
#define ARMYOVERVIEWMA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Mobility.h"

#include "../Misc/showText.h"
#include "../Units/Participants.h"
#include "../Misc/OtherFunctions.h"

extern std::vector<Participants> participantsList;

extern int currentParticipantIndex;
extern int maxAmountOfCommanders;

#define UNIT_SIZE 5

class ArmyOverviewMA
{
public:
	//constructor
	ArmyOverviewMA(Participants *newP);

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