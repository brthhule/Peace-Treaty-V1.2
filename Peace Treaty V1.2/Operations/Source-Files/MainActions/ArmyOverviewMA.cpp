#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER 

using namespace PART;
using namespace COORD;

void Participants::armyOverviewMain() { 
	//For debugging
	INF::debugFunction("ArmyOverview, armyOverviewMain");
	using func = void(Participants::*)();

	println("Welcome to the Army Overview action menu\n");
	switch (Input::getOptionPrompt(ARMY_DEPLOYMENT).at(0)) {
		case 'T':
			trainCommanders();
			break;
		case 'U':
			upgradeCommander();
			break;
		case 'V':
			viewArmyOverview();
			break;
		case 'D': {
			deployCommanderMF();
			break;
		}
		case 'H': {
			INF::showHelp(5);
			break;
		}
		case 'M': {
			return;
		}
	}

	armyOverviewMain();
}

Commanders& Participants::pickCommanderToUpgrade() {
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
	return *commander;
}

void Participants::upgradeCommander() {
	//For debugging
	INF::debugFunction("ArmyOverview, upgradeCommander");

	commSPTR commander = std::make_shared<Commanders>(pickCommanderToUpgrade());
	if (commander = nullptr) { return; }

	i5array costsArray = commander->getUpgradeCosts();

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
		std::cout << "Upgrade successful; Commander " + commander->getUnitName() + "is now level " << commander->getLevel() << std::endl;
	} else {
		//Add subtracted resources back to province resources
		std::cout << "Upgrade failed. " << std::endl;
	}

	INF::enterAnything(1);
	return;
}

//Currently shows one commander information by selection. Need to update to show all commander information
void Participants::viewArmyOverview() {
	//For debugging
	INF::debugFunction("ArmyOverview, viewArmyOverview");

	commSPTR commander = pickCommander();

	//Check that the user wants to proceed
	if (commander == nullptr) {
		INF::enterAnything(1);
		return;
	}
	
	std::cout << "Commander " + commander->getUnitName() +" selected... \n" +
		"The coordinates of this Commander: ";
	commander->printCoords(COORD::USER); 
	std::cout << "\n\n";
	commander->printCommanderStats();

}

void Participants::trainCommanders() {
	//For debugging
	INF::debugFunction("ArmyOverview, trainCommanders");

	std::string yesOrNoString;
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

void Participants::proceedWithTraining(i5array trainCosts) {
	//For debugging
	INF::debugFunction("ArmyOverview, proceedWithTraining");

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

void Participants::deployCommanderMF() {
	//For debugging
	INF::debugFunction("ArmyOverview, deployCommanderMF");

	commSPTR commander = pickCommander();
	if (commander == nullptr) {
		return;
	}

	commander->printCommanderStats();

	std::cout << "Deploy commander " + commander->getUnitName() + "? (Y/N) ";
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
	deployCommanderMF(); 
	INF::enterAnything(1);
}
 
void Participants::addCommander() { 
	//For debugging
	INF::debugFunction("Participants, addCommander");

	commSPTR commander = std::make_shared<Commanders>(new Commanders(1, getNewName()));
	commander->setParticipantIndex(participantIndex); 

	commandersVector.push_back(std::make_shared<Commanders>(*commander)); 
	commandersMap[commander.getUnitName()] = std::make_shared<Commanders>(*commander);
	getCapitalProvince()->addCommander(*commander);
}