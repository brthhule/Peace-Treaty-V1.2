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
#include COMMANDERS_HEADER

class ArmyOverviewMA
	USES_  
		INF_ 
		INPUT_
{
public:
	//----Constructors---------------------------------------------------------
	ArmyOverviewMA(){}
	~ArmyOverviewMA(){}

	//----Methods--------------------------------------------------------------
	/** armyOverviewMain
			Main method for ArmyOverviewMA

			@param void
			@return void
	*/
	virtual void armyOverviewMain() = 0;
	virtual void trainCommanders() = 0;
	virtual void proceedWithTraining(constI5array trainCosts) = 0;
	virtual void upgradeCommander() = 0;
	virtual Commanders& pickCommanderToUpgrade() = 0;  
	virtual void viewArmyOverview() = 0;
	virtual void deployCommanderMF() = 0;
	virtual void addCommander() = 0;
};

#endif