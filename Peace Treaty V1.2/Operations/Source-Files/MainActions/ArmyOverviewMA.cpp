#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER 

#include <functional>

using namespace COORD;
using namespace COMM;
using namespace INF;

void Participants::armyOverviewSelectAction() { 
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "armyOverviewSelectAction()");

	char action = Input::getOptionPrompt(Input::ARMY_DEPLOYMENT).at(0);

	switch (action) {
		case 'T':
			trainCommanderPrompt();
			break;
		case 'U':
			upgradeCommander();
			break;
		case 'V':
			viewCommanderStats();
			break;
		case 'D':
			deployCommanderPrompt();
			break;
		case 'N':
			BASE::nothing();
			break;
		case 'A':
			armyOverviewSelectActionShowHelp();
			break;
	}

	if (action != 'M') { armyOverviewSelectAction(); }
	return;
}

commSPTR Participants::pickCommanderToUpgrade() {  
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "pickCommanderToUpgrade()");
	if (getCommandersNum() == 0) { 
		LOG::PRINT("No commanders available, can not upgrade\n"); 
		enterAnything(1);  
		return nullptr;
	}

	COMM::commSPTR commander = this->pickCommander(); 

	if (commander.get() == nullptr) {
		LOG::PRINT("Cancelling upgrade...\n");
		enterAnything(1); 
		return nullptr;
	}

	//This should return the reference that commander holds
	return commander;
}

void Participants::upgradeCommander() { 
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "upgradeCommander()");

	commSPTR commander = pickCommanderToUpgrade();

	if (commander == nullptr) { return; }

	constArrayRef costsArray = commander.get()->getUpgradeCosts(); 

	LOG::PRINT("The following are the Commander upgrade costs: \n");
	INF::printResources(costsArray);
	LOG::PRINT("The following are the resources currently in your capital: \n");

	getCapitalProvince()->printResources();
	char proceedWithUpgradeQuestion =
		Input::getInputText("\nProceed with upgrade? ", { "Y", "N" }).at(0);

	if (proceedWithUpgradeQuestion == 'N') {
		LOG::PRINT("Cancelling upgrade...\n"); 
		INF::enterAnything(1);
		return;
	}

	bool resourcesPositive = getCapitalProvince()->subtractCheckResources(costsArray);

	if (resourcesPositive == true) {
		commander.get()->addLevel();
		LOG::PRINT("Upgrade successful; Commander "s + commander.get()->getName() + "is now level "s + commander.get()->getLevel() + "\n";);
	} else {
		//Add subtracted resources back to province resources
		LOG::PRINT("Upgrade failed...\n");
	}

	INF::enterAnything(1);
	return;
}


void Participants::addCommander() {
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "addCommander()");

	Commanders newCommander(1, getNewName(), participantIndex);
	capitalProvince->addCommander(newCommander);

	commSPTR commander = std::make_shared<Commanders>(capitalProvince->getCommander(newCommander.getName()));

	commander->setParticipantIndex(participantIndex);
	commandersVector.push_back(std::make_shared<Commanders>(*commander));
	commandersMap[commander->getName()] = std::make_shared<Commanders>(*commander);
}

//Currently shows one commander information by selection. Need to update to show all commander information
void Participants::viewCommanderStats() {
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "viewCommanderStats()");

	commSPTR commander = pickCommander();

	//Check that the user wants to proceed
	if (commander == nullptr) {
		INF::enterAnything(1);
		return;
	}
	
	LOG::PRINT("Commander "s + commander->getName() +" selected... \n"s +
		"The coordinates of this Commander: ");

	commander->printCoords(COORD::USER); 
	LOG::PRINT("\n\n");
	commander->printCommanderStats();

}

void Participants::trainCommanderPrompt() {
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "trainCommanderPrompt()");

	LOG::PRINT("You have "s + this->getCommandersNum() + "/"s + TROOP::maxCommanders + " total army commanders.\n");
	if (getCommandersNum() < TROOP::maxCommanders) {
		LOG::PRINT("At maximum army commander amount.Training failed, returning to menu \n");
		return;
	}
	
	if (Input::getInputText("Proceed with training (Y/N)", { "Y", "N" }).at(0) == 'N') {
		INF::enterAnything(1);
		return;
	}

	i5array trainCosts = getTrainCosts(); 
	proceedWithTraining(trainCosts);

	INF::enterAnything(1);
	return;
}

void Participants::proceedWithTraining(constArrayRef trainCosts) { 
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "proceedWithTraining(constArrayRef)");

	bool trainingSuccess = getCapitalProvince()->subtractCheckResources(trainCosts);

	if (trainingSuccess == false) {
		LOG::ERROR("Commander training failed(Not enough resources)... \n\n");
		return;
	}

	addCommander();

	LOG::PRINT("Commander training successful\n");
	LOG::PRINT("Current commanders: "s + this->getCommandersNum() + "\n");

	return;
}

void Participants::deployCommanderPrompt() {
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "deployComanderPrompt(0)");

	commSPTR commander = pickCommander();
	if (commander == nullptr) { return; }

	commander->printCommanderStats();

	LOG::PRINT("Deploy commander "s + commander->getName() + "? (Y/N) ");
	char confirmDeploy = Input::getInputText("Replacement", { "Y", "N" }).at(0);

	if (confirmDeploy == 'N') {
		LOG::PRINT("Returning to the previous page... \n");
		return;
	}

	if (commander->hasMoved() == false) { 
		this->moveUnitOne(commander);
		return;
	} 

	LOG::ERROR("This unit has already moved... please pick another unit\n");
	deployCommanderPrompt(); 
	INF::enterAnything(1);
}


void Participants::armyOverviewSelectActionShowHelp() {
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "armyOverviewSelectActionShowHelp()");
	INF::showHelp(5);
}

/*Its type is “int (*)(char,float)” if an ordinary function
Its type is “int (Fred::*)(char,float)” if a non-static member function of class Fred*/

	/*
	typedef void (Participants::*Actions)(void);
	typedef std::unordered_map<char, Actions> ActionFunctions;
	ActionFunctions actionsMap;

	actionsMap['T'] = &trainCommanderPrompt;
	actionsMap['U'] = &upgradeCommander;
	actionsMap['V'] = &viewCommanderStats;
	actionsMap['D'] = &deployCommanderPrompt;
	actionsMap['N'] = &nothingArmyOverview;
	actionsMap['A'] = &armyOverviewSelectActionShowHelp;*/