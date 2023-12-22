#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include COMMANDERS_HEADER

using namespace COMM;
using namespace TROOP;

/*Constructors*/
Commanders::Commanders() {
	//For debugging
	DEBUG_FUNCTION("Commanders", "Commanders ()");

	Commanders(1, "Unnamed");
}

Commanders::Commanders(int level, std::string name) {
	//For debugging
	DEBUG_FUNCTION("Commanders, Commanders (1 Param)");

	unitLevel = level;
	moved = false;


	maxTroops = unitLevel * 10;
	totalMaxResources = 0;
	setName(name);
}
/*Destructor*/
Commanders::~Commanders() {
	//For debugging
	DEBUG_FUNCTION("Commanders, ~Commanders");
}

/////////////////////Display///////////
void Commanders::printCommanderStats() {
	//For debugging
	DEBUG_FUNCTION("Commanders, printCommanderStats");

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
	DEBUG_FUNCTION("Commanders, getCommanderStat");

	//placeholder
	return -1;
	//return *commanderArmyStats[index];
}

INF::i5array Commanders::getUpgradeCosts() {
	//For debugging
	DEBUG_FUNCTION("Commanders, getUpgradeCosts");

	i5array costsArray;
	costsArray.fill(0);


	for (int x = 0; x < 5; x++) {
		costsArray[x] = costToUpgrade.at(x) * unitLevel;
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
	return "Name: " + getName() + ", Level: " + getLevel();
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