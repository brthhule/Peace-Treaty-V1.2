#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER 

#include <functional>

using namespace PART;
using namespace COORD;
using namespace COMM;

void Participants::armyOverviewSelectAction() { 
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "armyOverviewSelectAction()");

	char action = Input::getOptionPrompt(ARMY_DEPLOYMENT).at(0);

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
		std::cout << "No commanders available, can not upgrade\n"; 
		enterAnything(1); 
		return nullptr;
	}

	COMM::commSPTR commander = this->pickCommander(); 

	if (commander.get() == nullptr) {
		std::cout << "Cancelling upgrade...\n"; 
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

	constArrayReference costsArray = commander.get()->getUpgradeCosts();

	std::cout << "The following are the Commander upgrade costs: \n";
	INF::printResources(costsArray);
	std::cout << "The following are the resources currently in your capital: \n";
	getCapitalProvince()->printResources();
	char proceedWithUpgradeQuestion =
		Input::getInputText("\nProceed with upgrade? ", { "Y", "N" }).at(0);

	if (proceedWithUpgradeQuestion == 'N') {
		std::cout << "Cancelling upgrade...\n";
		INF::enterAnything(1);
		return;
	}

	bool resourcesPositive = getCapitalProvince()->subtractCheckResources(costsArray);

	if (resourcesPositive == true) {
		commander.get()->addLevel();
		std::cout << "Upgrade successful; Commander " + commander.get()->getName() + "is now level " << commander.get()->getLevel() << std::endl; 
	} else {
		//Add subtracted resources back to province resources
		std::cout << "Upgrade failed. " << std::endl;
	}

	INF::enterAnything(1);
	return;
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
	
	std::cout << "Commander " + commander->getName() +" selected... \n" +
		"The coordinates of this Commander: ";
	commander->printCoords(COORD::USER); 
	std::cout << "\n\n";
	commander->printCommanderStats();

}

void Participants::trainCommanderPrompt() {
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "trainCommanderPrompt()");

	std::cout << "You have " << this->getCommandersNum() << "/" << TROOP::maxCommanders << " total army commanders. \n";
	if (getCommandersNum() < maxCommanders) {
		std::cout << "At maximum army commander amount. Training failed, returning to menu \n";
		return;
	}
	
	if (Input::getInputText("Proceed with training (Y/N)", { "Y", "N" }).at(0) == 'N') {
		INF::enterAnything(1);
		return;
	}

	i5array trainCosts = getTrainCosts(); 
	proceedWithTraining(trainCosts);

	INF::enterAnything(1);
}

void Participants::proceedWithTraining(constArrayReference trainCosts) {
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "proceedWithTraining(constArrayReference)");

	bool trainingSuccess = getCapitalProvince()->subtractCheckResources(trainCosts);

	if (trainingSuccess == false) {
		std::cout << "Commander training failed (Not enough resources)... \n\n";
		return;
	}

	addCommander();

	println("Commander training successful ");
	std::cout << "Current commanders: " << this->getCommandersNum() << std::endl;
	return;
}

void Participants::deployCommanderPrompt() {
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "deployComanderPrompt(0)");

	commSPTR commander = pickCommander();
	if (commander == nullptr) { return; }

	commander->printCommanderStats();

	std::cout << "Deploy commander " + commander->getName() + "? (Y/N) ";
	char confirmDeploy = Input::getInputText("Replacement", { "Y", "N" }).at(0);

	if (confirmDeploy == 'N') {
		std::cout << "Returning to the previous page...\n";
		return;
	}

	if (commander->hasMoved() == false) { 
		this->moveUnitOne(commander);
		return;
	} 

	std::cout << "This unit has already moved... please pick another unit \n";
	deployCommanderPrompt(); 
	INF::enterAnything(1);
}
 
void Participants::addCommander() {  
	DEBUG_FUNCTION("ArmyOverviewMA.cpp", "addCommander()");

	commSPTR commander = std::make_shared<Commanders>(new Commanders(1, getNewName(), participantIndex));
	commander->setParticipantIndex(participantIndex); 
	commandersVector.push_back(std::make_shared<Commanders>(*commander)); 
	commandersMap[commander->getName()] = std::make_shared<Commanders>(*commander);
	getCapitalProvince()->addCommander(*commander);
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