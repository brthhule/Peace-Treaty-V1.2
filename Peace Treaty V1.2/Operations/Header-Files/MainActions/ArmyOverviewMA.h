//ArmyOverviewMA.h
//Implemented by: Participants

#ifndef ARMYOVERVIEWMA_H
#define ARMYOVERVIEWMA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INF_HEADER
#include INPUT_HEADER

class ArmyOverviewMA
	USES_  
		INF_ 
		INPUT_
{
public:
	ArmyOverviewMA(){}
	~ArmyOverviewMA(){}

	virtual void
		printCosts(i5array, int phrase) = 0;

	virtual void armyOverviewMain() = 0;
	virtual void
		trainCommanders() = 0,
		proceedWithTraining(std::array <int,5> trainCosts) = 0,
		upgradeCommander() = 0,
		viewArmyOverview() = 0,
		deployCommanderMF() = 0;
};

#endif