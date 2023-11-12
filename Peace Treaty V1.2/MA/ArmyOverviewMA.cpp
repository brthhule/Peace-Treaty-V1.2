#include "../Units/Participants.h"

void Participants::armyDeploymentMF() {
	//For debugging
	OF::debugFunction("ArmyOverview, armyDeploymentMF");
	using func = void(Participants::*)();

	println("Welcome to the Army Deployment action menun\n");
	switch (Input::getOptionPrompt(ARMY_DEPLOYMENT).at(0)) {
		case 'T':
			trainCommanders();
			break;
		case 'U':
			upgradeCommandersOne();
			break;
		case 'V':
			viewArmyOverview();
			break;
		case 'D': {
			deployCommanderMF();
			break;
		}
		case 'H': {
			OF::showHelp(5);
			break;
		}
		case 'M': {
			return;
		}
	}
	armyDeploymentMF();
}

/*fix this-- finish making it*/
void Participants::upgradeCommandersOne() {
	//For debugging
	OF::debugFunction("ArmyOverview, upgradeCommandersOne");

	if (commandersNum() > 0)
	{
		if (this->selectCommander() != "-1")
			upgradeCommandersTwo();
	} else
		std::cout << "No commanders available, can not upgrade\n";

	OF::enterAnything();
}

void Participants::upgradeCommandersTwo() {
	//For debugging
	OF::debugFunction("ArmyOverview, upgradeCommandersTwo");

	STRING commanderName;//Implement this stuff
	ARRAY costsArray = getCommander(commanderName)->getUpgradeCosts();

	getCommander(commanderName)->printCosts(costsArray);

	char proceedWithUpgradeQuestion =
		Input::getInputText("\nProceed with upgrade? ", { "Y", "N" }).at(0);
	if (proceedWithUpgradeQuestion == 'Y') {

		std::array<int, 5> commanderCosts = costsArray;
		bool commanderUpgradeIsSuccess = getCapitalProvince()->subtractCheckResources(commanderCosts);

		if (commanderUpgradeIsSuccess == true) {
			getCommander(commanderName)->addLevel();
			std::cout << "Upgrade successful; Commander " + commanderName + "is now level " << getCommander(commanderName)->getLevel() << std::endl;
		} else {
			getCapitalProvince()->modifyResources(commanderCosts, true);
			std::cout << "Upgrade failed. " << std::endl;
		}
	}
}

void Participants::viewArmyOverview() {
	//For debugging
	OF::debugFunction("ArmyOverview, viewArmyOverview");

	std::string commanderName = selectCommander();

	//Check that the user wants to proceed
	if (commanderName != "-1") {
		std::cout << "Commander " + commanderName + " selected... \n" +
			"The coordinates of this Commander: ";
		getCommander(commanderName)->printUserCoords();
		std::cout << "\n\n";
		getCommander(commanderName)->printCommanderStats();
	}
	OF::enterAnything();
}

void Participants::trainCommanders() {
	//For debugging
	OF::debugFunction("ArmyOverview, trainCommanders");

	std::string yesOrNoString;
	std::cout << "You have " << this->commandersNum() << "/" << CV::maxCommanders << " total army commanders. \n";
	std::cout << "Do you want to train a commander? (Y/N) ";

	ARRAY trainCosts = getTrainCosts();

	if (Input::getInputText("Proceed with training", { "Y", "N" }).at(0) == 'Y') {
		/*if amount of commanders is less than max (not at max capacity)*/
		if (this->commandersNum() < CV::maxCommanders) {
			proceedWithTraining(trainCosts);
		} else {
			std::cout << "At maximum army commander amount. Training failed, returning to menu \n";
		}

	} else {
		OF::enterAnything();
	}

}

void Participants::proceedWithTraining(std::array<int, 5> trainCosts) {
	//For debugging
	OF::debugFunction("ArmyOverview, proceedWithTraining");

	bool trainingSuccess = getCapitalProvince()->subtractCheckResources(trainCosts);

	if (trainingSuccess == true) {
		addCommander();

		println("Commander training successful ");
		std::cout << "Current commanders: " << this->commandersNum() << std::endl;
	} else {
		std::cout << "Commander training failed (Not enough resources)... \n\n";
		getCapitalProvince()->modifyResources(trainCosts, true);
	}
}

void Participants::deployCommanderMF() {
	//For debugging
	OF::debugFunction("ArmyOverview, deployCommanderMF");

	std::string commanderName = selectCommander();
	if (commanderName == "-1") {
		return;
	}
	;

	CommanderProfile* commander = getCommander(commanderName);

	commander->printCommanderStats();

	std::cout << "Deploy commander " + commanderName + "? (Y/N) ";
	char confirmDeploy = Input::getInputText("Replacement", { "Y", "N" }).at(0);

	if (confirmDeploy == 'Y')
	{
		if (commander->hasMovedQuestion() == false) {
			this->moveUnitOne(getCommander(commanderName));
		} else {
			std::cout << "This unit has already moved... please pick another unit \n";
			deployCommanderMF();
		}

		OF::enterAnything();
	}
}

void Participants::printCosts(std::vector<int> costs, std::string type) {
	//For debugging
	OF::debugFunction("ArmyOverview, printCosts");

	std::cout << "The following are the " << type << " costs: \n";
	for (int x = 0; x < 5; x++) {
		std::cout << CV::RESOURCE_NAMES[x] << ": " << costs[x];
	}

	std::cout << "The following are the resources currently in your capital: \n";
	getCapitalProvince()->printResources();
}

