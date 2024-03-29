#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER 
#include INPUT_HEADER

using namespace PROV;
using namespace COORD; 
using namespace COMM;
using namespace INF;
using namespace BUILD;


BuildingsClass::BuildingsClass() : farm(), mill(), quarry(), mine(), church(), barracks(), infirmary(), library(), residences(), wall() {
	/*buildingsArray = {
		
		std::make_shared<BuildingsBASE>(farm), 
		std::make_shared<BuildingsBASE>(mill), 
		std::make_shared<BuildingsBASE>(quarry), 
		std::make_shared<BuildingsBASE>(mine), 
		std::make_shared<BuildingsBASE>(church), 
		std::make_shared<BuildingsBASE>(barracks), 
		std::make_shared<BuildingsBASE>(infirmary), 
		std::make_shared<BuildingsBASE>(library), 
		std::make_shared<BuildingsBASE>(residences), 
		std::make_shared<BuildingsBASE>(wall) 
	};*/

	buildingsVector = { farm, mill, quarry, mine, church, barracks, infirmary, library, residences, wall };
	/*
	buildingsVector.at(0).get() = farm;
	buildingsVector.at(0).get() = mill;
	buildingsVector.at(0).get() = quarry;
	buildingsVector.at(0).get() = mine;
	buildingsVector.at(0).get() = church;
	buildingsVector.at(0).get() = barracks;
	buildingsVector.at(0).get() = infirmary;
	buildingsVector.at(0).get() = library;
	buildingsVector.at(0).get() = residences;
	buildingsVector.at(0).get() = wall;*/
}

BuildingsBASE& BuildingsClass::get(BUILD::BuildingsEnum name) {
	return buildingsVector.at(name).get();
}
BuildingsBASE& BuildingsClass::get(int num) {
	return buildingsVector.at(num).get();
}

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
	for (Commanders commander : commandersVector) {
		units.push_back(std::make_shared<Commanders>(commander));
	}
	units = sortVector(sort, units);
	commandersVector.clear();
	for (unitSPTR unit : units) {
		commandersVector.push_back(*std::dynamic_pointer_cast<Commanders>(unit)); 
	}
}

INF::SortType Provinces::getCommandersSortStatus() const {
	return commandersSortType;
}

//Province stuff
void Provinces::updateProvinceResources() {
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
void Provinces::removeCommander(commSPTR removeCommander)
{
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "removeCommander");

	commandersMap.erase(removeCommander->getName());

	int lastIndex = (int) commandersVector.size() - 1; 
	int removeIndex = removeCommander->getIndexInProvince(); 

	//switch places between the Commander being removed and the last Commander (prevents other commanders from shifting after removal)
	commandersVector.emplace(commandersVector.begin() + removeIndex, std::move(commandersVector.at(lastIndex)));
	commandersVector.erase(commandersVector.begin() + lastIndex);
}

void Provinces::addCommander(Commanders commanderCopy)  
{
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "addCommander");
	commandersVector.push_back(commanderCopy);

	commSPTR commander = std::make_shared<Commanders>(commandersVector.at(commandersVector.size() - 1));
	commandersMap[commander->getName()] = commander; 
	commander->setCoords(getPairCoords());
}



int Provinces::getTotalCP() const {
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getTotalCP");

	int totalCP = 0;
	totalCP += getCombatPower();

	for (int index = 0; index < (int) commandersVector.size(); index++) {
		totalCP += commandersVector.at(index).getCombatPower();
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

const Commanders& Provinces::getCommander(std::string name) const { 
	//For debugging
	DEBUG_FUNCTION("Provinces.cpp", "getCommander");	
	return *commandersMap.at(name);
}

const Commanders& Provinces::getCommander(int index) const {
	return commandersVector.at(index);
}

bool Provinces::subtractCheckResources(constArrayRef resourcesArray) {
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

int Provinces::getCommandersNum() const {
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
		if (commander->getName() == commandersVector.at(index).getName()) {
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

constINT Provinces::getLevel() const {
	return level;
}

std::array<i5array, 7> Provinces::getLists() {
	std::array<i5array, 7> temp = {};
	return temp;
}

void Provinces::calculateCombatPower() {

}

void Provinces::calculateFoodConsumption() {

}