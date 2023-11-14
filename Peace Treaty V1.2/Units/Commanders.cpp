#include "Commanders.h"

/*Constructors*/
CommanderProfile::CommanderProfile() {
	//For debugging
	INF::debugFunction("CommanderProfile, CommanderProfile (0 Param)");

	unitLevel = 1;
	hasMoved = false;
	maxTroops = 0;
	totalMaxResources = 0;
	commanderIndex = 0;
	changeUnitName("Unnamed");
	deleteCommander = false;
}
CommanderProfile::CommanderProfile(int level, std::string name) {
	//For debugging
	INF::debugFunction("CommanderProfile, CommanderProfile (1 Param)");

	
	unitLevel = level;


	maxTroops = unitLevel * 10;
	totalMaxResources = 0;
	changeUnitName(name);
}
/*Destructor*/
CommanderProfile::~CommanderProfile() {
	//For debugging
	INF::debugFunction("CommanderProfile, ~CommanderProfile");
}

/*Accessor Functions*/
void CommanderProfile::printCommanderStats() {
	//For debugging
	INF::debugFunction("CommanderProfile, printCommanderStats");

	// print out stats
	INF::addColor(INF::BLUE);
	//Add implementation

	std::cout << MANDescriptions[5] << ": \n";
	INF::addColor(INF::RESET);
}
int CommanderProfile::getCommanderStat(int index) {
	//For debugging
	INF::debugFunction("CommanderProfile, getCommanderStat");

	//placeholder
	return -1;
	//return *commanderArmyStats[index];
}

std::array<int, 5> CommanderProfile::getUpgradeCosts() {
	//For debugging
	INF::debugFunction("CommanderProfile, getUpgradeCosts");

	std::array<int, 5> costsArray;
	for (int& x : costsArray) x = 0;
	for (int x = 0; x < 5; x++)
		costsArray[x] = costToUpgrade[x] * unitLevel;
	return costsArray;
}

void CommanderProfile::printCosts(std::array <int, 5> costs)
{
	//For debugging
	INF::debugFunction("CommanderProfile, printCosts");

	for (int x = 0; x < 5; x++)
		std::cout << INF::RESOURCE_NAMES[x] << " cost: " << costs[x] << std::endl;
	std::cout << std::endl;
}

void CommanderProfile::calculateCommanderScoutLog()
{
	//For debugging
	INF::debugFunction("CommanderProfile, calculateCommanderScoutLog");

	//Implement this
}

void CommanderProfile::addLevel() {
	//For debugging
	INF::debugFunction("CommanderProfile, addLevel");

	unitLevel++;
}

void CommanderProfile::setDelete() {
	//For debugging
	INF::debugFunction("CommanderProfile, setDelete");

	deleteCommander = true;
}

bool CommanderProfile::getDelete() {
	//For debugging
	INF::debugFunction("CommanderProfile, getDelete");

	return deleteCommander;
}

bool CommanderProfile::hasMovedQuestion() {
	//For debugging
	INF::debugFunction("CommanderProfile, hasMovedQuestion");

	return hasMoved;
}

void CommanderProfile::resetCommanderMoved() {
	//For debugging
	INF::debugFunction("CommanderProfile, resetCommanderHasMoved");

	hasMoved = false;
}
