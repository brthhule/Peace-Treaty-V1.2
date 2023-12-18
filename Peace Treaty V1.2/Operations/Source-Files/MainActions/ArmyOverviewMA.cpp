#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER 

using namespace PART;

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

void Participants::upgradeCommander() {
	//For debugging
	INF::debugFunction("ArmyOverview, upgradeCommander");

	if (getCommandersNum() == 0) {
		std::cout << "No commanders available, can not upgrade\n";
		enterAnything(1);
		return;
	}

	COMM::commSPTR commander = this->pickCommander();

	if (commander == nullptr) {
		std::cout << "Cancelling upgrade...\n";
		enterAnything(1);
		return;
	}

	i5array costsArray = commander->getUpgradeCosts();
	printCosts(costsArray, "commander upgrade");

	char proceedWithUpgradeQuestion =
		Input::getInputText("\nProceed with upgrade? ", { "Y", "N" }).at(0);

	if (proceedWithUpgradeQuestion == 'N') {
		std::cout << "Cancelling upgrade...\n";
		INF::enterAnything(1);
		return;
	}

	/*Subtracts the necessary resources from capital province. If resources left over are all positive (there were enough resources), return true. If any resources are negative, return false*/

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
	commander->printCoords(CoordsBASE::USER);
	std::cout << "\n\n";
	commander->printCommanderStats();

}

void Participants::trainCommanders() {
	//For debugging
	INF::debugFunction("ArmyOverview, trainCommanders");

	std::string yesOrNoString;
	std::cout << "You have " << this->getCommandersNum() << "/" << INF::maxCommanders << " total army commanders. \n";
	std::cout << "Do you want to train a commander? (Y/N) ";

	i5array trainCosts = getTrainCosts();

	if (Input::getInputText("Proceed with training", { "Y", "N" }).at(0) == 'N') {
		INF::enterAnything(1);
		return;
	}

	/*if amount of commanders is less than max (not at max capacity)*/
	if (this->getCommandersNum() < INF::maxCommanders) {
		proceedWithTraining(trainCosts);
	} else {
		std::cout << "At maximum army commander amount. Training failed, returning to menu \n";
	}

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

void Participants::printCosts(constI5array costs, int phrase) {
	std::string line;
	if (phrase == 1) {
		line = "Commander upgrade"
	}
	//For debugging
	INF::debugFunction("ArmyOverview, printCosts");

	std::cout << "The following are the " << line << " costs: \n";
	for (int x = 0; x < 5; x++) {
		std::cout << INF::RESOURCE_NAMES[x] << ": " << costs[x];
	}

	std::cout << "The following are the resources currently in your capital: \n";
	getCapitalProvince()->printResources();
}

