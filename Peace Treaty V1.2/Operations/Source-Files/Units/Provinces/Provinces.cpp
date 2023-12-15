#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER 
#include INPUT_HEADER

using namespace PROV;

//Don't use default constructor, just just this with -1 as a parameter
Provinces::Provinces(int overallIndexArg) {
	//For debugging
	INF::debugFunction("Provinces, Provinces (1 Param)");

	overallIndex = overallIndexArg;
	//Initialize building levels
	initializeEmptyBuildings();
	resourcesPresent = INF::INITIAL_VALUES;
	participantIndex = 0;

	isACapital = false;
	newAccuracy = -1;
	resourcesPresent = INF::mutateArray(resourcesPresent, INF::INITIAL_VALUES, INCREASE);

	unitLevel = 1;
	commandersSortType = ALPHABETICAL;
}

std::array<AllUnits::troopConditionArray, 3> Provinces::getTroopsLists() {
	std::array<troopConditionArray, 3> returnArray = { troopsPresent, troopsInjured, troopsLost };
	return returnArray;
}

std::array<int, 7> Provinces::getListsInt() {
	std::array<int, 7> returnArray = {
		combatPower,
		totalTroops,
		foodConsumption,
		participantIndex,
		unitLevel,
		troopsTrainedThisTurn,
		overallIndex
	};
	return returnArray;
}

void Provinces::setCommandersSortStatus(SortType sort) {
	if (sort == commandersSortType) { 
		return; 
	}

	commandersSortType = sort; 
	commandersVector = sortVector(sort, commandersVector);
}

INF::SortType Provinces::getCommandersSortStatus() {
	return commandersSortType;
}

//Province stuff
void Provinces::updateProvinceResources()
{
	//For debugging
	INF::debugFunction("Provinces, updateProvinceResources");

	i5array resourcesProduced = getResourceProduction(FARM, ALL); 
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
void Provinces::removeCommander(commSPTR newCommander)
{
	//For debugging
	INF::debugFunction("Provinces, removeCommander");

	commandersMap.erase(newCommander->getUnitName());
	commandersVector.erase(getCommanderIndex(newCommander));
}

void Provinces::addCommander(commSPTR newCommander)
{
	//For debugging
	INF::debugFunction("Provinces, addCommander");
	commandersMap[newCommander->getUnitName()] = newCommander;
}



const int& Provinces::getTotalCP()
{
	//For debugging
	INF::debugFunction("Provinces, getTotalCP");

	int totalCP = 0;
	totalCP += getCP();

	for (int index = 0; index < commandersVector.size(); index++) {
		totalCP += commandersVector.at(index)->getCP();
	}
	return totalCP;
}

INF::i5array Provinces::getTotalResources()
{
	//For debugging
	INF::debugFunction("Provinces, getTotalResources");

	INF::i5array totalResources = resourcesPresent;
	Commanders::commMAP::iterator it;
	for (it = commandersMap.begin(); it != commandersMap.end(); it++)
		for (int y = 0; y < 5; y++)
			totalResources[y] += it->second->getResource(y);
	
	return totalResources;
}

//Convert unordered_map to vector for easy understanding
COMM::commSPTRList Provinces::getAllCommanders()
{
	//For debugging
	INF::debugFunction("Provinces, getAllCommanders");

	commSPTRList commandersList;
	Commanders::commMAP::iterator it;
	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		commandersList.push_back(it->second);
	}
	return commandersList;
}

COMM::commSPTR Provinces::getCommander(std::string name) { 
	//For debugging
	INF::debugFunction("Provinces, getCommander");	
	return commandersMap[name];
}

bool Provinces::subtractCheckResources(i5array resourcesArray) {
	//For debugging
	INF::debugFunction("Provinces, subtractCheckResources");

	//returns false if resources dip into negatives
	this->modifyResources(resourcesArray, DECREASE);
	for (int x : this->resourcesPresent) {
		if (x < 0) { return false; }
	}
	
	return true;
}

void Provinces::printCommanders()
{
	//For debugging
	INF::debugFunction("Provinces, printCommanders");

	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		std::cout << "- " << it->second->getUnitName();
	}
}

bool Provinces::hasCommander(std::string name)
{
	//For debugging
	INF::debugFunction("Provinces, hasCommander");
	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
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

std::array<i5array, 7> Provinces::getLists() {
	//For debugging
	INF::debugFunction("Provinces, getLists");

	std::array<i5array, 7> tempOverallArray;
	for (int row = 0; row < 7; row++) {
		i5array tempRowArray = *Lists[row];

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

std::array< ipair, 2> Provinces::getListCoords() {
	//For debugging
	INF::debugFunction("Provinces, getListCoords");

	return { systemCoords, userCoords };
}








void Provinces::setKingdomName(std::string name) { 
	//For debugging
	INF::debugFunction("Provinces, setKingdomName");

	kingdomName = name;
}

const int& Provinces::getCommandersNum() {
	//For debugging
	INF::debugFunction("Provinces, getCommandersNum");

	return (int)commandersVector.size(); 
}

bool Provinces::isCapital() {
	//For debugging
	INF::debugFunction("Provinces, isCapital");

	return isACapital;
}

void Provinces::createReport(int scouterLevelArg, int targetLevelArg) {
	//For debugging
	INF::debugFunction("Provinces, createReport");

	std::array<i5array, 7> ListsArg;
	std::array<int, 7> listIntArg;
	std::array<bool, 3> listBoolArg;

	for (int row = 0; row < 7; row++) {
		i5array tempArray = *Lists[row];
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
		getCoords(CoordsBASE::SYSTEM));
	int turn = newReport.getReportTurn();
	std::pair<int, ProvinceReport> sendReport(turn, newReport);
	int index = 0;//Determine how to find this
	scoutReports[index].push_back(sendReport);
}

std::string Provinces::getKingdomName() {
	return kingdomName;
}

int Provinces::getCommanderIndex(commSPTR commander) {
	for (int index = 0; index < commandersVector.size(); index++) {
		if (commander == commandersVector.at(index)) {
			return index;
		}
	}

	return -1;
}

std::array<i5array, 4> Provinces::getGeneralLists() {
	std::array<i5array, 4> returnArray = {
		getTypeLevels(RESOURCE),
		getTypeLevels(OTHER),
		resourcesPresent,
		initialStats
	};

	return returnArray;
}

