#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include PROVINCES_HEADER
#include INPUT_HEADER

//Empty constructor, used for temp provinces
Provinces::Provinces() {
	//For debugging
	INF::debugFunction("Provinces, Provinces (0 Param)");

	Provinces(-1);
}

Provinces::Provinces(int overallIndexArg)
{
	//For debugging
	INF::debugFunction("Provinces, Provinces (1 Param)");

	overallIndex = overallIndexArg;
	//Initialize building levels
	initializeEmptyBuildings();
	resourcesPresent = INF::INITIAL_VALUES;
	participantIndex = 0;

	isACapital = false;
	newAccuracy = -1;
	INF::mutateArray(resourcesPresent, INF::INITIAL_VALUES, INCREASE);

	unitLevel = 1;

	Lists = {
		&resourceBuildingsLevels,
		&otherBuildingsLevels,
		&resourcesPresent,
		&troopsPresent,
		&troopsInjured,
		&troopsLost,
		&initialStats };
	troopsLists = {
		&troopsPresent,
		&troopsInjured,
		&troopsLost
	};
	listInt = {
		&combatPower,
		&totalTroops,
		&foodConsumption,
		&participantIndex,
		&unitLevel,
		&troopsTrainedThisTurn,
		&overallIndex
	};
}



//Province stuff
void Provinces::updateProvinceResources()
{
	//For debugging
	INF::debugFunction("Provinces, updateProvinceResources");

	i5array resourcesProduced = getResourceProduction(NULL, ALL);
	resourcesPresent = INF::mutateArray(resourcesPresent, resourcesProduced, INCREASE);
}

//Other
void Provinces::makeCapital(int participantIndexArg)
{
	//For debugging
	INF::debugFunction("Provinces, makeCapital");

	changeParticipantIndex(participantIndexArg);
	isACapital = true;
}

void Provinces::initializeCapitalStats() {
	//For debugging
	INF::debugFunction("Provinces, initializeCapitalStats");

	initiailizeCapitalBuildings();
}

//Commander Stuff
void Provinces::removeCommander(Commanders *newCommander)
{
	//For debugging
	INF::debugFunction("Provinces, removeCommander");

	commanders.erase(newCommander->getUnitName());
}

void Provinces::addCommander(Commanders* newCommander)
{
	//For debugging
	INF::debugFunction("Provinces, addCommander");
  commanders[newCommander->getUnitName()] = newCommander;
}



int Provinces::getTotalCP()
{
	//For debugging
	INF::debugFunction("Provinces, getTotalCP");

	int totalCP = 0;
	totalCP += getCP();
	for (it = commanders.begin(); it != commanders.end(); it++)
		totalCP += it->second->getCP();
	return totalCP;
}

INF::i5array Provinces::getTotalResources()
{
	//For debugging
	INF::debugFunction("Provinces, getTotalResources");

	INF::i5array totalResources = resourcesPresent;
  std::unordered_map<std::string, Commanders*>::iterator it;
	for (it = commanders.begin(); it != commanders.end(); it++)
		for (int y = 0; y < 5; y++)
			totalResources[y] += it->second->getResource(y);
	
	return totalResources;
}

//Convert unordered_map to vector for easy understanding
std::vector <Commanders*> Provinces::getAllCommanders()
{
	//For debugging
	INF::debugFunction("Provinces, getAllCommanders");

		std::vector<Commanders*> commandersList;
		std::unordered_map<std::string, Commanders*>::iterator it;
		for (it = commanders.begin(); it != commanders.end(); it++)
			commandersList.push_back(it->second);
		return commandersList;
}

Commanders* Provinces::getCommander(std::string name)
{
	//For debugging
	INF::debugFunction("Provinces, getCommander");	

		return commanders[name];
}

bool Provinces::subtractCheckResources(std::array<int, 5> resourcesArray)
{
	//For debugging
	INF::debugFunction("Provinces, subtractCheckResources");

	//returns false if resources dip into negatives
	modifyResources(resourcesArray, DECREASE);
	for (int x : resourcesPresent) {
		if (x < 0) { return false; }
	}
	
	return true;
}

void Provinces::printCommanders()
{
	//For debugging
	INF::debugFunction("Provinces, printCommanders");

	for (it = commanders.begin(); it != commanders.end(); it++)
		std::cout << "- " << it->second->getUnitName();
}

bool Provinces::hasCommander(std::string name)
{
	//For debugging
	INF::debugFunction("Provinces, hasCommander");

	for (it = commanders.begin(); it != commanders.end(); it++) {
		if (it->second->getUnitName() == name) {
			return true;
		}
	}
		
			
	return false;
}



//Fix this to differentiate between resource buildings and othe rother buildings; right now, only accounts for resource buildings

void Provinces::setOverallIndex(int index) {
	//For debugging
	INF::debugFunction("Provinces, setOverallIndex");

	overallIndex = index;
}

int Provinces::getOverallIndex() {
	//For debugging
	INF::debugFunction("Provinces, getOverallIndex");

	return overallIndex;
}

std::array<std::array<int, 5>, 7> Provinces::getLists() {
	//For debugging
	INF::debugFunction("Provinces, getLists");

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
	INF::debugFunction("Provinces, getListInt");

	std::array<int, 7> listTemp;
	for (int column = 0; column < 7; column++) {
		listTemp[column] = *listInt[column];
	}
	return listTemp;
}

std::array<bool, 3> Provinces::getListBool()
{
	//For debugging
	INF::debugFunction("Provinces, getListBool");

	std::array<bool, 3> listTemp;
	for (int column = 0; column < 3; column++) {
		listTemp[column] = *listBool[column];
	}
	return listTemp;
}

std::array< std::pair<int, int>, 2> Provinces::getListCoords() {
	//For debugging
	INF::debugFunction("Provinces, getListCoords");

	return { systemCoords, userCoords };
}








void Provinces::setKingdomName(std::string name) { 
	//For debugging
	INF::debugFunction("Provinces, setKingdomName");

	kingdomName = name;
}

int Provinces::getCommandersNum() {
	//For debugging
	INF::debugFunction("Provinces, getCommandersNum");

	return (int)commanders.size();
}

bool Provinces::isCapital() {
	//For debugging
	INF::debugFunction("Provinces, isCapital");

	return isACapital;
}

void Provinces::createReport(int scouterLevelArg, int targetLevelArg) {
	//For debugging
	INF::debugFunction("Provinces, createReport");

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
		getCoords(Coords::SYSTEM));
	int turn = newReport.getReportTurn();
	std::pair<int, ProvinceReport> sendReport(turn, newReport);
	int index = 0;//Determine how to find this
	scoutReports[index].push_back(sendReport);
}

std::string Provinces::getKingdomName() {
	return kingdomName;
}