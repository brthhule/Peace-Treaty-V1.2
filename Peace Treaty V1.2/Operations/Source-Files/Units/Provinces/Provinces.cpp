#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER 
#include INPUT_HEADER

using namespace PROV;
using namespace COORD; 

//Use participantIndex = -1 for empty provinces
Provinces::Provinces(int mapIndex, int participantIndex) : PrimeUnits(participantIndex) {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "Provinces (int)");

	this->mapIndex = mapIndex;
	//Initialize building levels
	resourcesPresent = INF::INITIAL_VALUES;

	isACapital = false;
	newAccuracy = -1;
	resourcesPresent = INF::mutateArray(resourcesPresent, INF::INITIAL_VALUES, INCREASE);

	level = 1;
	commandersSortType = ALPHABETICAL;

	//Buildings should be created when their province is created, figure out how to do that
	/*Barracks barracks();
	buildings.at(0) = barracks;*/

	buildings = { 
		std::make_unique<BuildingsBASE>(farm), 
		std::make_unique<BuildingsBASE>(mill), 
		std::make_unique<BuildingsBASE>(quarry), 
		std::make_unique<BuildingsBASE>(mine), 
		std::make_unique<BuildingsBASE>(church),  
		std::make_unique<BuildingsBASE>(barracks), 
		std::make_unique<BuildingsBASE>(infirmary),  
		std::make_unique<BuildingsBASE>(library), 
		std::make_unique<BuildingsBASE>(residences), 
		std::make_unique<BuildingsBASE>(wall) 
	};
}

constINT Provinces::getCombatPower() const { return combatPower; }

constINT Provinces::getFoodConsumption() const { return foodConsumption; }

std::array<int, 7> Provinces::getListInt() {
	std::array<int, 7> returnArray = {
		combatPower,
		totalTroops,
		foodConsumption,
		participantIndex,
		level,
		getTroopsTrainedThisTurn(),
		mapIndex
	};
	return returnArray;
}

std::array<bool, 2> Provinces::getListBool() {
	return { canSelectThisUnit, isACapital };
}

void Provinces::setCommandersSortStatus(SortType sort) {
	if (sort == commandersSortType) { return; }

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

INF::SortType Provinces::getCommandersSortStatus() const {
	return commandersSortType;
}

//Province stuff
void Provinces::updateProvinceResources()
{
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "updateProvinceResources");

	//Farm is just a placeholder, it is overridden by the ALL param
	i5array resourcesProduced = getResourceProduction(BuildingsEnum::FARM, ALL);  
	resourcesPresent = INF::mutateArray(resourcesPresent, resourcesProduced, INCREASE);
}

//Other
void Provinces::makeCapital(int participantIndexArg)
{
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "makeCapital");

	setParticipantIndex(participantIndexArg);
	isACapital = true;
}

void Provinces::initializeCapitalStats() {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "initializeCapitalStats");

	initiailizeCapitalBuildings();
}

//Commander Stuff
void Provinces::removeCommander(commSPTR newCommander)
{
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "removeCommander");

	commandersMap.erase(newCommander->getName());
	commandersVector.erase(commandersVector.begin() + getCommanderIndex(newCommander));
}

void Provinces::addCommander(Commanders &commanderReference)
{
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "addCommander");
	commSPTR commander = std::make_shared<Commanders>(commanderReference);
	commandersMap[commander->getName()] = commander; 

	commander->setCoords(getPairCoords());
}



constINT Provinces::getTotalCP() const {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getTotalCP");

	int totalCP = 0;
	totalCP += getCombatPower();

	for (int index = 0; index < (int) commandersVector.size(); index++) {
		totalCP += commandersVector.at(index)->getCombatPower();
	}
	return totalCP;
}



//Convert unordered_map to vector for easy understanding
COMM::commSPTRList Provinces::getAllCommanders() const {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getAllCommanders");

	commSPTRList commandersList;

	for (std::pair<std::string, commSPTR> pair : commandersMap) {
		commandersList.push_back(pair.second);
	}
	return commandersList;
}

COMM::commSPTR Provinces::getCommander(std::string name) const { 
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getCommander");	
	return commandersMap.at(name);
}

bool Provinces::subtractCheckResources(constArrayReference resourcesArray) {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "subtractCheckResources");

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
	DEBUG_FUNCTION("Provinces.cpp", "printCommanders");

	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		std::cout << "- " << it->second->getName();
	}
}

bool Provinces::hasCommander(std::string name)
{
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "hasCommander");
	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		if (it->second->getName() == name) {
			return true;
		}
	}
		
			
	return false;
}



//Fix this to differentiate between resource buildings and othe rother buildings; right now, only accounts for resource buildings
constINT Provinces::getMapIndex() const { return mapIndex; }


std::array< ipair, 2> Provinces::getListCoords() {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getListCoords");

	return { CoordsBASE::systemCoords, CoordsBASE::userCoords };
}

void Provinces::setKingdomName(std::string name) { 
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "setKingdomName");

	kingdomName = name;
}

constINT Provinces::getCommandersNum() const {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getCommandersNum");

	return (int)commandersVector.size(); 
}

bool Provinces::isCapital() const {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "isCapital");
	return isACapital;
}

void Provinces::createReport(int scouterLevelArg, int targetLevelArg) {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "createReport");

	std::array<i5array, 7> ListsArg{};
	std::array<int, 7> listIntArg{};
	std::array<bool, 3> listBoolArg{};


	//Add implementation
	ProvinceReport newReport(
		scouterLevelArg, 
		targetLevelArg, 
		ListsArg, 
		listIntArg, 
		listBoolArg, 
		CoordsBASE::getCoords(COORD::SYSTEM)); 

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

Commanders& Provinces::getProvinceCommander() const {
	return *provinceCommander;
}