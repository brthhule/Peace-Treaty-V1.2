#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER

using namespace PROV;

void Provinces::printBuildingUpgradeCosts(i5array requiredResources, int buildingIndex) {
	//For debugging
	INF::debugFunction("Provinces, printInformation");

	std::cout << "---------- Start printing information----------\n\n\033[34m";
	std::cout << INF::RESOURCE_BUILDING_NAMES[buildingIndex] << " selected \n";


	println("The following is the cost of the upgrade: ");
	for (int x = 0; x < 5; x++) {
		std::cout << INF::RESOURCE_NAMES.at(x) << ": " << requiredResources.at(x)
			<< std::endl;
	}
	println("\nThe following are how many resources are in this province: ");
	this->printResources();
	std::cout << "----------End printing informatio----------" << std::endl;
}

void Provinces::mainBuildFunction() {
	//For debugging
	INF::debugFunction("Provinces, playerBuildFunction");

	INF::clearScreen();
	std::cout <<
		"---------- Start printing province information ----------";
	INF::addColor(BLUE);
	std::cout << "Province of kingdom " + getKingdomName();
	std::cout << "Coordinates: " << getUserCoordsString() << "\n\n";
	INF::addColor(RESET);

	this->printResources();
	printBuildingStats();
	println("---------- End printing province information ----------\n");

	char upgradeBuilding = ' ';
	char repeatPlayerBuildFunction = 'Y';

	upgradeBuilding = Input::getOptionPrompt(PLAYER_BUILD_FUNCTION).at(0);
	if (upgradeBuilding == 'U') {
		selectUpgradeBuilding();
		//Recursion
		mainBuildFunction();
		std::cout << "\n";
	} else {
		//Break condition
		std::cout << "Returning to previous menu... " << std::endl;
		INF::clearScreen();
	}
}

void Provinces::selectUpgradeBuilding() {
	//For debugging
	INF::debugFunction("Provinces, upgradeBuildings");

	std::vector<std::string> buildingLetterList = { "H" };
	for (int x = 1; x <= 10; x++) {
		buildingLetterList.push_back(std::to_string(x));
	}

	printListOfBuildings();
	std::string message1 = "Enter the number of the building you want to upgrade " + 
		"(enter 'H' for help) : ";
	char option = Input::getInputText(message1, buildingLetterList).at(0);

	if (option != 'H') {
		upgradeBuildings2(option);
	} else {
		INF::showHelp(12);
	}

	char upgradeAgain = Input::getInputText("Upgrade another building (Y/N): ", { "Y", "N" }).at(0);
	if (upgradeAgain == 'Y') {
		upgradeBuildings();
	}
	std::cout << "Returning to Build Infrastructure action menu. " << std::endl;
}


void Provinces::upgradeBuilding(char optionChar) {
	//For debugging
	INF::debugFunction("Provinces, upgradeBuildings2");
	std::string optionString = "" + optionChar;
	int index = std::stoi(optionString);	

	//Multiplies level by base line rate
	BuildingsBASE *building = &this->buildings.at(index);
	i5array requiredResources = building->getUpgradeCosts();

	printBuildingUpgradeCosts(requiredResources, index);
	std::string message = "Proceed with upgrade? (Y/N): ";
	char upgradeProceed = Input::getInputText(message, { "Y", "N" }).at(0);

	if (upgradeProceed != 'Y') { return;}

	bool upgradeSuccess = this->subtractCheckResources(requiredResources);

	if (upgradeSuccess == false) {
		modifyResources(requiredResources, true);
		println("Upgrade failed. Not enough resources. ");
		return;
	}

	println("Upgrade successful.\n");
	building->increaseLevel();
	return;
}

