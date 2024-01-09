#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER 

using namespace BUILD;
using namespace Input;
using namespace INF;

void Provinces::upgradeBuildingPrompt() {  
	//For debugging
	DEBUG_FUNCTION("Provinces", "playerBuildFunction");

	clearScreen();
	std::cout <<
		"---------- Start printing province information ----------";
	addColor(BLUE);
	std::cout << "Province of kingdom " + getKingdomName();
	std::cout << "Coordinates: " << getCoords(COORD::USER) << "\n\n";  
	addColor(RESET);

	this->printResources();
	printBuildingStats();
	println("---------- End printing province information ----------\n");

	char repeatPlayerBuildFunction = 'Y';

	char upgradeBuilding = Input::getOptionPrompt(Input::PLAYER_BUILD_FUNCTION).at(0);
	if (upgradeBuilding == 'U') {
		selectBuildingToUpgrade();
	} else {
		//Break condition
		std::cout << "Returning to previous menu... " << std::endl;
		clearScreen();
	}
}


void Provinces::printBuildingUpgradeCosts(i5array requiredResources, int buildingIndex) {
	//For debugging
	DEBUG_FUNCTION("Provinces", "printInformation");

	std::cout << "---------- Start printing information----------\n\n\033[34m";
	std::cout << BUILD::RESOURCE_BUILDING_NAMES[buildingIndex] << " selected \n";


	println("The following is the cost of the upgrade: ");
	for (int x = 0; x < 5; x++) {
		std::cout << RESOURCE_NAMES.at(x) << ": " << requiredResources.at(x)
			<< std::endl;
	}
	println("\nThe following are how many resources are in this province: ");
	this->printResources();
	std::cout << "----------End printing informatio----------" << std::endl;
}


void Provinces::selectBuildingToUpgrade() {
	//For debugging
	DEBUG_FUNCTION("Provinces", "upgradeBuildings");

	std::vector<std::string> buildingLetterList = { "H" };
	for (int x = 1; x <= 10; x++) {
		buildingLetterList.push_back(std::to_string(x));
	}

	printListOfBuildings();

	std::string message1 = "Enter the number of the building you want to upgrade (enter 'H' for help) : ";
	std::string buildingNumber = Input::getInputText(message1, buildingLetterList);

	if (buildingNumber.at(0) != 'H') {
		upgradeBuilding(std::stoi(buildingNumber)); 
	} else {
		showHelp(12);
	}

	char upgradeAgain = Input::getInputText("Upgrade another building (Y/N): ", { "Y", "N" }).at(0);
	if (upgradeAgain == 'Y') {
		selectBuildingToUpgrade(); 
	}
	std::cout << "Returning to Build Infrastructure action menu. " << std::endl;
}


void Provinces::upgradeBuilding(int buildingNumber) {
	//For debugging
	DEBUG_FUNCTION("Provinces", "upgradeBuildings2");

	//Multiplies level by base line rate
	std::shared_ptr<BuildingsBASE> building = std::make_shared<BuildingsBASE>(buildings.get(buildingNumber)); 
	constArrayRef requiredResources = building->getUpgradeCosts();

	printBuildingUpgradeCosts(requiredResources, buildingNumber);
	std::string message = "Proceed with upgrade? (Y/N): ";
	char upgradeProceed = Input::getInputText(message, { "Y", "N" }).at(0);

	if (upgradeProceed != 'Y') { return;}

	bool upgradeSuccess = this->subtractCheckResources(requiredResources);

	if (upgradeSuccess == false) {
		mutateAllResources(requiredResources, INCREASE);
		println("Upgrade failed. Not enough resources. ");
		return;
	}

	println("Upgrade successful.\n");
	building->increaseLevel(1);
	return;
}

