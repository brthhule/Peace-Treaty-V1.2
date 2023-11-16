#include "Commanders.h"

/*Constructors*/
Commanders::Commanders() {
	//For debugging
	INF::debugFunction("Commanders, Commanders (0 Param)");

	Commanders(1, "Unnamed");
}

Commanders::Commanders(int level, std::string name) {
	//For debugging
	INF::debugFunction("Commanders, Commanders (1 Param)");

	unitLevel = level;
	moved = false;


	maxTroops = unitLevel * 10;
	totalMaxResources = 0;
	changeUnitName(name);
}
/*Destructor*/
Commanders::~Commanders() {
	//For debugging
	INF::debugFunction("Commanders, ~Commanders");
}

/////////////////////Display///////////
void Commanders::printCommanderStats() {
	//For debugging
	INF::debugFunction("Commanders, printCommanderStats");

	// print out stats
	INF::addColor(INF::BLUE);
	//Add implementation

	std::cout << statsOne.at(0) << std::endl;
	this->printResources();

	std::cout << statsOne.at(0) << std::endl;
	this->printTroopsPresent
	INF::addColor(INF::RESET);
}

////////////Accessors//////////////////
int Commanders::getCommanderStat(int index) {
	//For debugging
	INF::debugFunction("Commanders, getCommanderStat");

	//placeholder
	return -1;
	//return *commanderArmyStats[index];
}

INF::i5array Commanders::getUpgradeCosts() {
	//For debugging
	INF::debugFunction("Commanders, getUpgradeCosts");

	i5array costsArray;
	costsArray.fill(0);


	for (int x = 0; x < 5; x++) {
		costsArray[x] = costToUpgrade.at(x) * unitLevel;
	}
		
	return costsArray;
}

void Commanders::printCosts(std::array <int, 5> costs)
{
	//For debugging
	INF::debugFunction("Commanders, printCosts");

	for (int x = 0; x < 5; x++) {
		std::cout << INF::RESOURCE_NAMES[x] << " cost: " << costs[x] << std::endl;
	}
		
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


bool Commanders::getDelete() {
	//For debugging
	INF::debugFunction("Commanders, getDelete");

	return deleteCommander;
}

bool Commanders::hasMoved() {
	//For debugging
	INF::debugFunction("Commanders, hasMoved");

	return moved;
}

void Commanders::resetCommanderMoved() {
	//For debugging
	INF::debugFunction("Commanders, resetCommanderHasMoved");

	moved = false;
}