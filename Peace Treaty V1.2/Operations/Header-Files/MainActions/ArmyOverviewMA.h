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

class ArmyOverviewMA { 
public:
	//----Constructors---------------------------------------------------------
	ArmyOverviewMA(){}
	~ArmyOverviewMA(){}

	//----Methods--------------------------------------------------------------
	/** armyOverviewSelectAction
			Main method for ArmyOverviewMA

			@param void
			@return void
	*/
	virtual void armyOverviewSelectAction() = 0;
	virtual void trainCommanderPrompt() = 0;
	virtual void proceedWithTraining(constArrayReference trainCosts) = 0;
	virtual void upgradeCommander() = 0;
	virtual COMM::commSPTR pickCommanderToUpgrade() = 0;   
	virtual void viewCommanderStats() = 0;
	virtual void deployCommanderPrompt() = 0;
	virtual void addCommander() = 0;
	virtual void armyOverviewSelectActionShowHelp() = 0;
	virtual void playerActionShowHelp() = 0;
	virtual void nothingArmyOverview() = 0;
};

#endif