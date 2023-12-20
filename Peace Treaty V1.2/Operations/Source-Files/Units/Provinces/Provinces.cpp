#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER 
#include INPUT_HEADER

using namespace PROV;
using namespace COORD; 

//Don't use default constructor, just just this with -1 as a parameter
Provinces::Provinces(int overallIndexArg) {
	//For debugging
	INF::debugFunction("Provinces, Provinces (1 Param)");

	overallIndex = overallIndexArg;
	//Initialize building levels
	resourcesPresent = INF::INITIAL_VALUES;
	participantIndex = 0;

	isACapital = false;
	newAccuracy = -1;
	resourcesPresent = INF::mutateArray(resourcesPresent, INF::INITIAL_VALUES, INCREASE);

	unitLevel = 1;
	commandersSortType = ALPHABETICAL;

	//Buildings should be created when their province is created, figure out how to do that
	/*Barracks barracks();
	buildings.at(0) = barracks;*/
}



std::array<int, 7> Provinces::getListsInt() {
	std::array<int, 7> returnArray = {
		combatPower,
		totalTroops,
		foodConsumption,
		participantIndex,
		unitLevel,
		getTroopsTrainedThisTurn(),
		overallIndex
	};
	return returnArray;
}

void Provinces::setCommandersSortStatus(SortType sort) {
	if (sort == commandersSortType) { 
		return; 
	}

	commandersSortType = sort; 
	std::vector<unitSPTR> units;
	for (commSPTR commander : commandersVector) {
		units.push_back(commander);
	}
	units = sortVector(sort, units);
	commandersVector.clear();
	for (unitSPTR unit : units) {
		commandersVector.push_back(std::dynamic_pointer_cast<Commanders>(unit));
	}
}

INF::SortType Provinces::getCommandersSortStatus() {
	return commandersSortType;
}

//Province stuff
void Provinces::updateProvinceResources()
{
	//For debugging
	INF::debugFunction("Provinces, updateProvinceResources");

	//Farm is just a placeholder, it is overridden by the ALL param
	i5array resourcesProduced = getResourceProduction(BuildingsEnum::FARM, ALL);  
	resourcesPresent = INF::mutateArray(resourcesPresent, resourcesProduced, INCREASE);
}

//Other
void Provinces::makeCapital(int participantIndexArg)
{
	//For debugging
	INF::debugFunction("Provinces, makeCapital");

	setParticipantIndex(participantIndexArg);
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

	commandersMap.erase(newCommander->getName());
	commandersVector.erase(commandersVector.begin() + getCommanderIndex(newCommander));
}

void Provinces::addCommander(Commanders &commanderReference)
{
	//For debugging
	INF::debugFunction("Provinces, addCommander");
	commSPTR commander = std::make_shared<Commanders>(commanderReference);
	commandersMap[commander->getName()] = commander; 

	commander->setCoords(getPairCoords());
}



constINT Provinces::getTotalCP()
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



//Convert unordered_map to vector for easy understanding
COMM::commSPTRList Provinces::getAllCommanders()
{
	//For debugging
	INF::debugFunction("Provinces, getAllCommanders");

	commSPTRList commandersList;
	COMM::commMAP::iterator it; 
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

bool Provinces::subtractCheckResources(constArrayReference resourcesArray) {
	//For debugging
	INF::debugFunction("Provinces, subtractCheckResources");

	//returns false if resources dip into negatives
	this->mutateAllResources(resourcesArray, DECREASE);
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
		std::cout << "- " << it->second->getName();
	}
}

bool Provinces::hasCommander(std::string name)
{
	//For debugging
	INF::debugFunction("Provinces, hasCommander");
	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		if (it->second->getName() == name) {
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

constINT Provinces::getOverallIndex() {
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

	return { CoordsBASE::systemCoords, CoordsBASE::userCoords };
}

void Provinces::setKingdomName(std::string name) { 
	//For debugging
	INF::debugFunction("Provinces, setKingdomName");

	kingdomName = name;
}

constINT Provinces::getCommandersNum() {
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
		getCoords(COORD::SYSTEM));
	int turn = newReport.getReportTurn();
	std::pair<int, ProvinceReport> sendReport(turn, newReport);
	int index = 0;//Determine how to find this
	scoutReports[index].push_back(sendReport);
}

std::string Provinces::getKingdomName() {
	return kingdomName;
}

int Provinces::getCommanderIndex(commSPTR commander) {
	for (int index = 0; index < (int)commandersVector.size(); index++) {
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

