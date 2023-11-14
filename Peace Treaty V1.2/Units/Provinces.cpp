#include "Provinces.h"
#include "../Units/Misc/Input.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

//Empty constructor, used for temp provinces
Provinces::Provinces() {
	//For debugging
	CV::debugFunction("Provinces, Provinces (0 Param)");

	//Empty
	
	//Defaults
	isACapital = false;
	newAccuracy = -1;
	overallIndex = -1;
}
Provinces::Provinces(int overallIndexArg)
{
	//For debugging
	CV::debugFunction("Provinces, Provinces (1 Param)");

	setOverallIndex(overallIndexArg);
	//Initialize building levels
	initializeEmptyBuildings();
	resourcesPresent = CV::INITIAL_VALUES;
	participantIndex = -1;

	CV::modifyArray(resourcesPresent, CV::INITIAL_VALUES, true);

	unitLevel = 1;
}

std::pair<int, int> Provinces::translateToSystemCoords(std::pair<int, int> userCoordsArg) {
	//For debugging
	CV::debugFunction("Provinces, translateToSystemCoords");

	return Coords::translateToSystemCoords(userCoordsArg);
}


//Province stats


//Province stuff
void Provinces::updateProvinceResources()
{
	//For debugging
	CV::debugFunction("Provinces, updateProvinceResources");

	std::array<int, 5> resourcesProduced = getResourceProduction(CHURCH, ALL);
	resourcesPresent = CV::modifyArray(resourcesPresent, resourcesProduced, true);
}

//Other
void Provinces::makeCapital(int participantIndexArg)
{
	//For debugging
	CV::debugFunction("Provinces, makeCapital");

	changeParticipantIndex(participantIndexArg);
	isACapital = true;
}

void Provinces::initializeCapitalStats() {
	//For debugging
	CV::debugFunction("Provinces, initializeCapitalStats");

	initiailizeCapitalBuildings();
}



//Commander Stuff
void Provinces::removeCommander(CommanderProfile *newCommander)
{
	//For debugging
	CV::debugFunction("Provinces, removeCommander");

	commanders.erase(newCommander->getUnitName());
}

void Provinces::addCommander(CommanderProfile* newCommander)
{
	//For debugging
	CV::debugFunction("Provinces, addCommander");
  commanders[newCommander->getUnitName()] = newCommander;
}



int Provinces::getTotalCP()
{
	//For debugging
	CV::debugFunction("Provinces, getTotalCP");

	int totalCP = 0;
	totalCP += getCP();
	for (it = commanders.begin(); it != commanders.end(); it++)
		totalCP += it->second->getCP();
	return totalCP;
}

std::array<int,5> Provinces::getTotalResources()
{
	//For debugging
	CV::debugFunction("Provinces, getTotalResources");

	std::array<int,5> totalResources = resourcesPresent;
  std::unordered_map<std::string, CommanderProfile*>::iterator it;
	for (it = commanders.begin(); it != commanders.end(); it++)
		for (int y = 0; y < 5; y++)
			totalResources[y] += it->second->getResource(y);
	
	return totalResources;
}

//Convert unordered_map to vector for easy understanding
std::vector <CommanderProfile*> Provinces::getAllCommanders()
{
	//For debugging
	CV::debugFunction("Provinces, getAllCommanders");

		std::vector<CommanderProfile*> commandersList;
		std::unordered_map<std::string, CommanderProfile*>::iterator it;
		for (it = commanders.begin(); it != commanders.end(); it++)
			commandersList.push_back(it->second);
		return commandersList;
}

CommanderProfile* Provinces::getCommander(std::string name)
{
	//For debugging
	CV::debugFunction("Provinces, getCommander");	

		return commanders[name];
}

bool Provinces::subtractCheckResources(std::array<int, 5> resourcesArray)
{
	//For debugging
	CV::debugFunction("Provinces, subtractCheckResources");

	//returns false if resources dip into negatives
	modifyResources(resourcesArray, false);
	for (int x: resourcesPresent)
		if (x < 0)
			return false;
	return true;
}

void Provinces::printCommanders()
{
	//For debugging
	CV::debugFunction("Provinces, printCommanders");

	for (it = commanders.begin(); it != commanders.end(); it++)
		std::cout << "- " << it->second->getUnitName();
}

bool Provinces::hasCommander(std::string name)
{
	//For debugging
	CV::debugFunction("Provinces, hasCommander");

	for (it = commanders.begin(); it != commanders.end(); it++) {
		if (it->second->getUnitName() == name) {
			return true;
		}
	}
		
			
	return false;
}

void Provinces::playerBuildFunction() {
	//For debugging
	CV::debugFunction("Provinces, playerBuildFunction");

	CV::clearScreen();
	std::cout<<
		"---------- Start printing province information ----------";
	CV::addColor(BLUE);
	std::cout << "Province of kingdom " + getKingdomName();
	std::cout << "Coordinates: " << getUserCoordsString() << "\n\n";
	CV::addColor(RESET);

	this->printResources();
	printBuildingStats();
	println("---------- End printing province information ----------\n");

	char upgradeBuilding = ' ';
	char repeatPlayerBuildFunction = 'Y';

	upgradeBuilding = Input::getOptionPrompt(PLAYER_BUILD_FUNCTION).at(0);
	if (upgradeBuilding == 'U') {
		upgradeBuildings();
		playerBuildFunction();
		std::cout << std::endl;
	}
	else {
		std::cout << "Returning to previous menu... " << std::endl;
		CV::clearScreen();
	}
}

void Provinces::upgradeBuildings() {
	//For debugging
	CV::debugFunction("Provinces, upgradeBuildings");

	std::vector<std::string> buildingLetterList = {"H"};
	for (int x = 1; x <= 10; x++) {
		buildingLetterList.push_back(std::to_string(x));
	}

	displayListOfBuildings();

	char option = Input::getInputText("Enter the number of the building you want to upgrade (enter 'H' for help): ", buildingLetterList).at(0);

	if (option != 'H') {
		upgradeBuildings2(option);
	}
	else {
		CV::showHelp(12);
	}

	char upgradeAgain = Input::getInputText("Upgrade another building (Y/N): ", { "Y", "N" }).at(0);
	if (upgradeAgain == 'Y') {
		upgradeBuildings();
	}
	std::cout << "Returning to Build Infrastructure action menu. " << std::endl;
}

void Provinces::upgradeBuildings2(char optionChar) {
	//For debugging
	CV::debugFunction("Provinces, upgradeBuildings2");

	int option = optionChar - '0';
	Build::BuildingType type = Build::BuildingType(option >= 6);
	//type is other
	if (type) {
		upgradeBuildings3(type, &otherBuildingsLevels, Build::OtherBuildings(option));
		return;
	}

	//Type is resource
	upgradeBuildings3(type, &resourceBuildingsLevels, Build::ResourceBuildings(option));

}

void Provinces::upgradeBuildings3(Build::BuildingType type, std::array<int, 5>* listArg, int name) {
	//For debugging
	CV::debugFunction("Provinces, upgradeBuildings3");

	int index = name;
	//If other type
	if (type)
	{
		index = name + 5;
	}

	//Multiplies level by base line rate
	std::array<int, 5> requiredResources;
	for (int x = 0; x < 5; x++) {
		requiredResources[x] = (int) listArg->at(name) * (int) upgradeRates[0][x];//Fix this later
	}


	int buildingIndex = NULL;//Fix this later
	printInformation(type, requiredResources, buildingIndex);
	char upgradeProceed = Input::getInputText("Proceed with upgrade? (Y/N) ", { "Y", "N" }).at(0);

	if (upgradeProceed == 'Y') {
		bool upgradeSuccess = this->subtractCheckResources(requiredResources);

		if (upgradeSuccess == false) {
			modifyResources(requiredResources, true);
			println("Upgrade failed. Not enough resources. ");
		}
		else {
			println("Upgrade successful.\n");
			//this->mutateLevel(buildingIndex, {1}); fix this later
		}
	}
}

void Provinces::printInformation(BuildingType type, std::array<int, 5> requiredResources, int buildingIndex) {
	//For debugging
	CV::debugFunction("Provinces, printInformation");

	std::cout << "---------- Start printing information----------\n\n\033[34m";
	std::cout << CV::RESOURCE_BUILDING_NAMES[buildingIndex] << " selected \n";


	println("The following is the cost of the upgrade: ");
	for (int x = 0; x < 5; x++) {
		std::cout << CV::RESOURCE_NAMES[x] << ": " << requiredResources[x]
			<< std::endl;
	}
	println("\nThe following are how many resources are in this province: ");
	this->printResources();
	std::cout << "----------End printing informatio----------" << std::endl;
}


//Fix this to differentiate between resource buildings and othe rother buildings; right now, only accounts for resource buildings

void Provinces::setOverallIndex(int index) {
	//For debugging
	CV::debugFunction("Provinces, setOverallIndex");

	overallIndex = index;
}

int Provinces::getOverallIndex() {
	//For debugging
	CV::debugFunction("Provinces, getOverallIndex");

	return overallIndex;
}

std::array<std::array<int, 5>, 7> Provinces::getLists() {
	//For debugging
	CV::debugFunction("Provinces, getLists");

	std::array<std::array<int, 5>, 7> tempOverallArray;
	for (int row = 0; row < 7; row++) {
		std::array<int, 5> tempRowArray = *Lists[row];

		for (int column = 0; column < 5; column++) {
			tempOverallArray[row][column] = tempRowArray[column];
		}
	}

	return tempOverallArray;
}
std::array<int, 7> Provinces::getListInt()
{
	//For debugging
	CV::debugFunction("Provinces, getListInt");

	std::array<int, 7> listTemp;
	for (int column = 0; column < 7; column++) {
		listTemp[column] = *listInt[column];
	}
	return listTemp;
}

std::array<bool, 3> Provinces::getListBool()
{
	//For debugging
	CV::debugFunction("Provinces, getListBool");

	std::array<bool, 3> listTemp;
	for (int column = 0; column < 3; column++) {
		listTemp[column] = *listBool[column];
	}
	return listTemp;
}

std::array< std::pair<int, int>, 2> Provinces::getListCoords() {
	//For debugging
	CV::debugFunction("Provinces, getListCoords");

	return { systemCoords, userCoords };
}








void Provinces::setKingdomName(std::string name) { 
	//For debugging
	CV::debugFunction("Provinces, setKingdomName");

	kingdomName = name;
}

int Provinces::commandersNum() {
	//For debugging
	CV::debugFunction("Provinces, commandersNum");

	return (int)commanders.size();
}

bool Provinces::isCapital() {
	//For debugging
	CV::debugFunction("Provinces, isCapital");

	return isACapital;
}

void Provinces::createReport(int scouterLevelArg, int targetLevelArg) {
	//For debugging
	CV::debugFunction("Provinces, createReport");

	std::array<std::array<int, 5>, 7> ListsArg;
	std::array<int, 7> listIntArg;
	std::array<bool, 3> listBoolArg;

	for (int row = 0; row < 7; row++) {
		std::array<int, 5> tempArray = *Lists[row];
		for (int col = 0; col < 5; col++) {
			ListsArg[row][col] = tempArray[col];
		}

		listIntArg[row] = *listInt[row];
	}

	for (int x = 0; x < 3; x++) {
		listBoolArg[x] = *listBool[x];
	}

	ProvinceReport newReport(scouterLevelArg, 
		targetLevelArg, 
		ListsArg, 
		listIntArg, 
		listBoolArg, 
		getSystemCoords());
	int turn = newReport.getReportTurn();
	std::pair<int, ProvinceReport> sendReport(turn, newReport);
	int index = 0;//Determine how to find this
	scoutReports[index].push_back(sendReport);
}