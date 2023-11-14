#include "Commanders.h"

/*Constructors*/
CommanderProfile::CommanderProfile() {
	//For debugging
	CV::debugFunction("CommanderProfile, CommanderProfile (0 Param)");

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
	CV::debugFunction("CommanderProfile, CommanderProfile (1 Param)");

	
	unitLevel = level;


	maxTroops = unitLevel * 10;
	totalMaxResources = 0;
	changeUnitName(name);
}
/*Destructor*/
CommanderProfile::~CommanderProfile() {
	//For debugging
	CV::debugFunction("CommanderProfile, ~CommanderProfile");
}

/*Accessor Functions*/
void CommanderProfile::printCommanderStats() {
	//For debugging
	CV::debugFunction("CommanderProfile, printCommanderStats");

	// print out stats
	CV::addColor(CV::BLUE);
	//Add implementation

	std::cout << MANDescriptions[5] << ": \n";
	CV::addColor(CV::RESET);
}
int CommanderProfile::getCommanderStat(int index) {
	//For debugging
	CV::debugFunction("CommanderProfile, getCommanderStat");

	//placeholder
	return -1;
	//return *commanderArmyStats[index];
}

std::array<int, 5> CommanderProfile::getUpgradeCosts() {
	//For debugging
	CV::debugFunction("CommanderProfile, getUpgradeCosts");

	std::array<int, 5> costsArray;
	for (int& x : costsArray) x = 0;
	for (int x = 0; x < 5; x++)
		costsArray[x] = costToUpgrade[x] * unitLevel;
	return costsArray;
}

void CommanderProfile::printCosts(std::array <int, 5> costs)
{
	//For debugging
	CV::debugFunction("CommanderProfile, printCosts");

	for (int x = 0; x < 5; x++)
		std::cout << CV::RESOURCE_NAMES[x] << " cost: " << costs[x] << std::endl;
	std::cout << std::endl;
}

void CommanderProfile::calculateCommanderScoutLog()
{
	//For debugging
	CV::debugFunction("CommanderProfile, calculateCommanderScoutLog");

	//Implement this
}

void CommanderProfile::addLevel() {
	//For debugging
	CV::debugFunction("CommanderProfile, addLevel");

	unitLevel++;
}

void CommanderProfile::setDelete() {
	//For debugging
	CV::debugFunction("CommanderProfile, setDelete");

	deleteCommander = true;
}

bool CommanderProfile::getDelete() {
	//For debugging
	CV::debugFunction("CommanderProfile, getDelete");

	return deleteCommander;
}

bool CommanderProfile::hasMovedQuestion() {
	//For debugging
	CV::debugFunction("CommanderProfile, hasMovedQuestion");

	return hasMoved;
}

void CommanderProfile::resetCommanderMoved() {
	//For debugging
	CV::debugFunction("CommanderProfile, resetCommanderHasMoved");

	hasMoved = false;
}
