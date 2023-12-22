#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include COMMANDERS_HEADER

using namespace COMM;
using namespace TROOP;

/*Constructors*/
Commanders::Commanders() : PrimeUnits (-1) {
	//For debugging
	DEBUG_FUNCTION("Commanders", "Commanders ()");

	Commanders(1, "Unnamed", -1);
}

Commanders::Commanders(int level, std::string name, int participantIndex) : PrimeUnits(participantIndex){
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "Commanders (1 Param)");

	level = level;
	moved = false;


	maxTroops = level * 10;
	totalMaxResources = 0;
	setName(name);
}
/*Destructor*/
Commanders::~Commanders() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "~Commanders");
}

/////////////////////Display///////////
void Commanders::printCommanderStats() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "printCommanderStats");

	// print out stats
	INF::addColor(INF::BLUE);
	//Add implementation

	std::cout << statsOne.at(0) << std::endl;
	this->printResources();

	std::cout << statsOne.at(0) << std::endl;
	this->printTroopsPresent();

	//Continue implementing here
	INF::addColor(INF::RESET);
}

////////////Accessors//////////////////
constINT Commanders::getCommanderStat(int index) {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "getCommanderStat");

	//placeholder
	return -1;
	//return *commanderArmyStats[index];
}

constArrayReference Commanders::getUpgradeCosts() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "getUpgradeCosts");

	i5array costsArray;
	costsArray.fill(0);


	for (int x = 0; x < 5; x++) {
		costsArray[x] = costToUpgrade.at(x) * level;
	}
		
	return costsArray;
}



void Commanders::calculateCommanderScoutLog(){
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "calculateCommanderScoutLog");

	//Implement this
}

void Commanders::addLevel() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "addLevel");
	level++;
}

bool Commanders::hasMoved() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "hasMoved");

	return moved;
}

void Commanders::resetCommanderMoved() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "resetCommanderHasMoved");

	moved = false;
}

const std::string& Commanders::getCommanderNameLevel() {
	return "Name: " + getName() + ", Level: " + std::to_string(getLevel());
}

constINT Commanders::getCombatPower() {
	return combatPower;
}

void Commanders::calculateFoodConsumption() {
	foodConsumption = 0;
	for (int troopType = 0; troopType < 5; troopType++) { 
		foodConsumption += getSumOfTiersOfTroop(REGULAR, TroopTypes(troopType)); 
	}
}

constINT Commanders::getFoodConsumption() {
	return foodConsumption;
}

constINT Commanders::getLevel() {
	return level;
}

const Commanders& makeConst(Commanders& commander) {
	return commander;
}