#include "Provinces.h"
#include "../Input.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;


Provinces::Provinces(int overallIndexArg)
{
	OF::debugFunction("Provinces, Provinces (3)");

	setOverallIndex(overallIndexArg);
	//Initialize building levels
	initializeEmptyBuildings();
	resourcesPresent = CV::INITIAL_VALUES;
	participantIndex = -1;

	OF::modifyArray(resourcesPresent, CV::INITIAL_VALUES, true);

	scoutReportTurn = -1;
	scoutReportLogLevel = -1;

	unitLevel = 1;
	deleteProvince = false;
}


//Province stats


//Province stuff
void Provinces::updateProvinceResources()
{
	OF::debugFunction("Provinces, updateProvinceResources");
	std::array<int, 5> resourcesProduced = getResourceProduction(CHURCH, ALL, returnArray);
	resourcesPresent = OF::modifyArray(resourcesPresent, resourcesProduced, true);
}

//Other
void Provinces::makeCapital(int participantIndexArg)
{
	OF::debugFunction("Provinces, initializeCapital");
	changeParticipantIndex(participantIndexArg);
	isACapital = true;
}

void Provinces::initializeCapitalStats() {
	initiailizeCapitalBuildings();
}



//Commander Stuff
void Provinces::removeCommander(CommanderProfile *newCommander)
{
	OF::debugFunction("Provinces, removeCommander");
	commanders.erase(newCommander->getUnitName());
}

void Provinces::addCommander(CommanderProfile* newCommander)
{
	OF::debugFunction("Provinces, addCommander");
  commanders[newCommander->getUnitName()] = newCommander;
}







bool Provinces::deleteStatus()
{
	OF::debugFunction("Provinces, deleteStatus");
  return deleteProvince;
}

int Provinces::getTotalCP()
{
	OF::debugFunction("Provinces, getTotalCP");
	int totalCP = 0;
	totalCP += getCP();
	for (it = commanders.begin(); it != commanders.end(); it++)
		totalCP += it->second->getCP();
	return totalCP;
}

std::array<int,5> Provinces::getTotalResources()
{
	OF::debugFunction("Provinces, getTotalResources");
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
	OF::debugFunction("Provinces, getAllCommanders");
		std::vector<CommanderProfile*> commandersList;
		std::unordered_map<std::string, CommanderProfile*>::iterator it;
		for (it = commanders.begin(); it != commanders.end(); it++)
			commandersList.push_back(it->second);
		return commandersList;
}

CommanderProfile* Provinces::getCommander(std::string name)
{
	OF::debugFunction("Provinces, getCommander");	
		return commanders[name];
}

bool Provinces::subtractCheckResources(std::array<int, 5> resourcesArray)
{
	OF::debugFunction("Provinces, subtractCheckResources");
	//returns false if resources dip into negatives
	modifyResources(resourcesArray, false);
	for (int x: resourcesPresent)
		if (x < 0)
			return false;
	return true;
}


void Provinces::completeProvinceScoutReport(int accuracy, Provinces* targetProvince, int scoutTurn)
{
	OF::debugFunction("Provinces, completeProvinceScoutReport");
	Provinces* t = targetProvince;
	/*Higher accuracy = more accurate scout log-- default is 50% accuracy (if
  there are 10 food resources in a province,
  the margin is 50%-- 5-15 units. 100 accuracy is the most accurate, 0 accuracy
  is the least accurate*/
	newAccuracy = (double)accuracy / 100;
	newAccuracy = (1 - newAccuracy)/2;//The most it will ever be off by is 50%
	std::array<int, 5> tempArray;
	//AllUnits info
	unitName = t->getUnitName();
	resourcesPresent = t->getAllResources();

	troopsPresent = t->getTroop(REGULAR, -1, tempArray);
	troopsInjured = t->getTroop(INJURED, -1, tempArray);
	troopsLost = t->getTroop(LOST, -1, tempArray);

	//totalTroops = t->getTotalTroops();
	//foodConsumption = t->getFoodConsumption();
	std::pair<int, int> systemCoords = getSystemCoords();
	participantIndex = t->getParticipantIndex();
	unitLevel = t->getLevel();
	unitName = t->getUnitName();
	CP = getEstimate((int) newAccuracy, t->getCP());

	/*maxGarrison = t->getMaxGarrison();
	maxInfirmaryCapacity = t->getMaxInfirmaryCapacity();
	resourceBuildingsLevels = t->getResourceBuildingLevels();
	resourceBuildingsProduction = t->getResourceBuildignsProduction();
	otherBuildingsLevels = t->getOtherBuildingsLevels();
	barracksCapacity = t->getBarracksCapacity();
	maxResources = t->getMaxResources();*/
	
	turn = scoutTurn;
	accuracy = accuracy;


}

int Provinces::getEstimate(int newAccuracy, int quantity)
{
	OF::debugFunction("Provinces, getEstimate");
	int margin = (int) (newAccuracy * quantity);
	int lowerBound = quantity - margin;
	int upperBound = quantity + margin;
	int scoutEstimate = rand() % lowerBound + upperBound;
	return scoutEstimate;
}


void Provinces::printCommanders()
{
	OF::debugFunction("Provinces, printCommanders");
	for (it = commanders.begin(); it != commanders.end(); it++)
		std::cout << "- " << it->second->getUnitName();
}

bool Provinces::hasCommander(std::string name)
{
	OF::debugFunction("Provinces, hasCommander");
	for (it = commanders.begin(); it != commanders.end(); it++)
		if (it->second->getUnitName() == name)
			return true;
	return false;
}

void Provinces::addTroopsTrainedThisTurn(int amount)
{
}



void Provinces::playerBuildFunction() {
	OF::clearScreen();
	std::cout<<
		"---------- Start printing province information ----------";
	CV::addColor(BLUE);
	std::cout << "Province of kingdom " + getKingdomName();
	std::cout << "Coordinates: " << getUserCoords << "\n\n";
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
		OF::clearScreen();
	}
}

void Provinces::upgradeBuildings() {
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
		OF::showHelp(12);
	}

	char upgradeAgain = Input::getInputText("Upgrade another building (Y/N): ", { "Y", "N" }).at(0);
	if (upgradeAgain == 'Y') {
		upgradeBuildings();
	}
	std::cout << "Returning to Build Infrastructure action menu. " << std::endl;
}

void Provinces::upgradeBuildings2(char optionChar) {
	int option = optionChar - '0';
	Build::BuildingType type = Build::BuildingType(option >= 6);
	if (type) {
		upgradeBuildings3(&otherBuildingsLevels, Build::OtherBuildings(option));
		return;
	}

	upgradeBuildings3(&resourceBuildingsLevels, Build::ResourceBuildings(option));

}


template<typename T>
T Provinces::upgradeBuildings3(std::array<int, 5>* arrayArg, T name) {
	printInformation(buildingNumber, requiredResources, buildingLetterList);
	char upgradeProceed = Input::getInputText("Proceed with upgrade? (Y/N) ", { "Y", "N" }).at(0);

	if (upgradeProceed == 'Y') {
		bool upgradeSuccess = this->subtractCheckResources(requiredResources);

		if (upgradeSuccess == false) {
			modifyResources(requiredResources, true);
			println("Upgrade failed. Not enough resources. ");
		}
		else {
			println("Upgrade successful.\n");
			this->mutateLevel(buildingNumber, 1);
		}
	}
}

void Provinces::printInformation(int buildingNumber, std::array<int, 5> requiredResources, std::vector<std::string> buildingLetterList) {
	std::cout << "---------- Start printing information----------\n\n\033[34m";
	println(CV::RESOURCE_BUILDING_NAMES[buildingNumber] + " selected \n");
	println("The following is the cost of the upgrade: ");
	for (int x = 0; x < 5; x++) {
		requiredResources[x] = (int)requiredResourcesBuildings[buildingNumber][x] * this->getBuildingLevel(x);
		std::cout << CV::RESOURCE_NAMES[x] << ": " << requiredResources[x]
			<< std::endl;
	}
	println("\nThe following are how many resources are in this province: ");
	this->printResources();
	std::cout << "----------End printing informatio----------" << std::endl;
}


//Fix this to differentiate between resource buildings and othe rother buildings; right now, only accounts for resource buildings

void Provinces::setOverallIndex(int index) {
	overallIndex = index;
}

int Provinces::getOverallIndex() {
	return overallIndex;
}

std::array<std::array<int, 5>, 7> Provinces::getLists() {
	std::array<std::array<int, 5>, 7> tempOverallArray;
	for (int row = 0; row < 7; row++) {
		std::array<int, 5> tempRowArray = *Lists[row];

		for (int column = 0; column < 5; column++) {
			tempOverallArray[row][column] = tempRowArray[column];
		}
	}
}
std::array<int, 7> Provinces::getListInt()
{
	std::array<int, 7> listTemp;
	for (int column = 0; column < 7; column++) {
		listTemp[column] = *listInt[column];
	}
}

std::array<bool, 3> Provinces::getListBool()
{
	std::array<bool, 3> listTemp;
	for (int column = 0; column < 3; column++) {
		listTemp[column] = *listBool[column];
	}
}

std::array< std::pair<int, int>, 2> Provinces::getListCoords() {
	return { systemCoords, userCoords };
}






Report::Report(int scouterLevelArg, int targetLevelArg, Provinces &province) {
	scouterLevel = scouterLevelArg;
	targetLevel = targetLevelArg;
	computeAccuracy();
	Lists = province.getLists();
	listInt = province.getListInt();
	listBool = province.getListBool();
	listCoords = province.getListCoords();
	commandersPtr = province.getAllCommanders();
	getCommanders();
	attuneValues();
}

void Report::getCommanders() {
	for (int x = 0; x < commandersPtr.size(); x++) {
		commanders.push_back(*commandersPtr.at(x));
	}
}

void Report::computeAccuracy() {
	int bigger = 0;
	int smaller = 0;

	switch (scouterLevel > targetLevel)
	{
	case 0:
		bigger = targetLevel;
		smaller = scouterLevel;
		break;
	case 1:
		bigger = scouterLevel;
		smaller = targetLevel;
		break;
	}

	double divided = double(bigger) / smaller;
	divided = divided * 10;
	//Max accuracy: 95, min: 10
	//Accuracy starts at 50 by default-- same level = 50
	//If scouting a higher level target
	if (scouterLevel < targetLevel)
	{
		divided *= -1;
	}
	accuracy = 50 + int(divided);
	if (accuracy > 95) {
		accuracy = 95;
	}
	else if (accuracy < 5) {
		accuracy = 5;
	}
}

void Report::attuneValues() {
	int newAccuracy = 100 - accuracy;
	int currentValue, mediumValue, upperValue, lowerValue;
	srand(time(NULL));

	for (int row = 0; row < 7; row++) {
		for (int col = 0; col < 5; col++) {
			currentValue = Lists[row][col];
			mediumValue = currentValue * (newAccuracy / 100);
			upperValue = currentValue + mediumValue;
			lowerValue = currentValue - mediumValue;
			Lists[row][col] = rand() % (upperValue - lowerValue) + lowerValue;
		}

		currentValue = listInt[row];
		mediumValue = currentValue * (newAccuracy / 100);
		upperValue = currentValue + mediumValue;
		lowerValue = currentValue - mediumValue;
		Lists[row] = rand() % (upperValue - lowerValue) + lowerValue;
	}
}