#include "Commanders.h"

/*Constructors*/
Commanders::Commanders() {
	//For debugging
	INF::debugFunction("Commanders, Commanders (0 Param)");

	unitLevel = 1;
	hasMoved = false;
	maxTroops = 0;
	totalMaxResources = 0;
	commanderIndex = 0;
	changeUnitName("Unnamed");
	deleteCommander = false;
}
Commanders::Commanders(int level, std::string name) {
	//For debugging
	INF::debugFunction("Commanders, Commanders (1 Param)");

	
	unitLevel = level;


	maxTroops = unitLevel * 10;
	totalMaxResources = 0;
	changeUnitName(name);
}
/*Destructor*/
Commanders::~Commanders() {
	//For debugging
	INF::debugFunction("Commanders, ~Commanders");
}

/*Accessor Functions*/
void Commanders::printCommanderStats() {
	//For debugging
	INF::debugFunction("Commanders, printCommanderStats");

	// print out stats
	INF::addColor(INF::BLUE);
	//Add implementation

	std::cout << MANDescriptions[5] << ": \n";
	INF::addColor(INF::RESET);
}
int Commanders::getCommanderStat(int index) {
	//For debugging
	INF::debugFunction("Commanders, getCommanderStat");

	//placeholder
	return -1;
	//return *commanderArmyStats[index];
}

std::array<int, 5> Commanders::getUpgradeCosts() {
	//For debugging
	INF::debugFunction("Commanders, getUpgradeCosts");

	std::array<int, 5> costsArray;
	for (int& x : costsArray) x = 0;
	for (int x = 0; x < 5; x++)
		costsArray[x] = costToUpgrade[x] * unitLevel;
	return costsArray;
}

void Commanders::printCosts(std::array <int, 5> costs)
{
	//For debugging
	INF::debugFunction("Commanders, printCosts");

	for (int x = 0; x < 5; x++)
		std::cout << INF::RESOURCE_NAMES[x] << " cost: " << costs[x] << std::endl;
	std::cout << std::endl;
}

void Commanders::calculateCommanderScoutLog()
{
	//For debugging
	INF::debugFunction("Commanders, calculateCommanderScoutLog");

	//Implement this
}

void Commanders::addLevel() {
	//For debugging
	INF::debugFunction("Commanders, addLevel");

	unitLevel++;
}

void Commanders::setDelete() {
	//For debugging
	INF::debugFunction("Commanders, setDelete");

	deleteCommander = true;
}

bool Commanders::getDelete() {
	//For debugging
	INF::debugFunction("Commanders, getDelete");

	return deleteCommander;
}

bool Commanders::hasMovedQuestion() {
	//For debugging
	INF::debugFunction("Commanders, hasMovedQuestion");

	return hasMoved;
}

void Commanders::resetCommanderMoved() {
	//For debugging
	INF::debugFunction("Commanders, resetCommanderHasMoved");

	hasMoved = false;
}
