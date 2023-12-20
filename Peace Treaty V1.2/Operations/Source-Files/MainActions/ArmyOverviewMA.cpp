#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER 

#include <functional>

using namespace PART;
using namespace COORD;

void Participants::armyOverviewSelectAction() { 
	//For debugging
	DEBUG_FUNCTION("ArmyOverview, armyOverviewSelectAction");

	/*Its type is “int (*)(char,float)” if an ordinary function
Its type is “int (Fred::*)(char,float)” if a non-static member function of class Fred*/
	typedef void (Participants::* Actions)(void);
	//typedef void (*Actions)(void); // function pointer type 
	typedef std::unordered_map<char, Actions> ActionFunctions; 
	ActionFunctions actionsMap; 
	actionsMap.emplace('U', &trainCommanderPrompt); 
	actionsMap.emplace('U', &upgradeCommander);
	actionsMap.emplace('U', &viewCommanderStats); 
	actionsMap.emplace('U', &deployCommanderPrompt); 
	actionsMap.emplace('U', &armyOverviewSelectActionShowHelp); 
	actionsMap.emplace('U', &nothing()); 

	char action = Input::getOptionPrompt(ARMY_DEPLOYMENT).at(0);
	actionsMap[action]();    

	if (action != 'M') { armyOverviewSelectAction(); }
	return;
}

commSPTR Participants::pickCommanderToUpgrade() {
	if (getCommandersNum() == 0) { 
		std::cout << "No commanders available, can not upgrade\n"; 
		enterAnything(1); 
		return nullptr;
	}

	COMM::commSPTR commander = this->pickCommander(); 

	if (commander == nullptr) { 
		std::cout << "Cancelling upgrade...\n"; 
		enterAnything(1); 
		return nullptr;
	}

	//This should return the reference that commander holds
	return commander;
}

void Participants::upgradeCommander() {
	//For debugging
	DEBUG_FUNCTION("ArmyOverview, upgradeCommander");

	commSPTR commander = pickCommanderToUpgrade(); 
	if (commander = nullptr) { return; }

	constArrayReference costsArray = commander->getUpgradeCosts();

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
		commander->addLevel();
		std::cout << "Upgrade successful; Commander " + commander->getName() + "is now level " << commander->getLevel() << std::endl;
	} else {
		//Add subtracted resources back to province resources
		std::cout << "Upgrade failed. " << std::endl;
	}

	INF::enterAnything(1);
	return;
}

//Currently shows one commander information by selection. Need to update to show all commander information
void Participants::viewCommanderStats() {
	//For debugging
	DEBUG_FUNCTION("ArmyOverview, viewCommanderStats");

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
	//For debugging
	DEBUG_FUNCTION("ArmyOverview, trainCommanderPrompt");

	std::cout << "You have " << this->getCommandersNum() << "/" << TROOP::maxCommanders << " total army commanders. \n";
	if (getCommandersNum < TROOP::maxCommanders()) {
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

void Participants::proceedWithTraining(const i5array& trainCosts) {
	//For debugging
	DEBUG_FUNCTION("ArmyOverview, proceedWithTraining");

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
	//For debugging
	DEBUG_FUNCTION("ArmyOverview, deployCommanderPrompt");

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
	//For debugging
	DEBUG_FUNCTION("Participants, addCommander");
	commSPTR commander = std::make_shared<Commanders>(new Commanders(1, getNewName()));
	commander->setParticipantIndex(participantIndex); 

	commandersVector.push_back(std::make_shared<Commanders>(*commander)); 
	commandersMap[commander.getName()] = std::make_shared<Commanders>(*commander);
	getCapitalProvince()->addCommander(*commander);
}

void Participants::armyOverviewSelectActionShowHelp() {
	INF::showHelp(5);
}