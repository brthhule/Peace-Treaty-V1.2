#include "CommanderProfile.h"

/*Constructors*/
CommanderProfile::CommanderProfile() {
	unitLevel = 1;
	hasMoved = false;
	maxTroops = 0;
	totalMaxResources = 0;
	commanderIndex = 0;
	changeUnitName("Unnamed");
	deleteCommander = false;
}
CommanderProfile::CommanderProfile(int level, std::string name) {
	unitLevel = level;




	maxTroops = unitLevel * 10;
	totalMaxResources = 0;
	changeUnitName(name);
}
/*Destructor*/
CommanderProfile::~CommanderProfile() {}

/*Accessor Functions*/
void CommanderProfile::printCommanderStats() {
	// print out stats
	addColor(BLUE);
	//Add implementation

	std::cout << MANDescriptions[5] << ": \n";
	addColor(RESET);
}
int CommanderProfile::getCommanderStat(int index) {
	//placeholder
	return -1;
	//return *commanderArmyStats[index];
}

std::array<int, 5> CommanderProfile::getUpgradeCosts() {
	std::array<int, 5> costsArray;
	for (int& x : costsArray) x = 0;
	for (int x = 0; x < 5; x++)
		costsArray[x] = costToUpgrade[x] * unitLevel;
	return costsArray;
}

void CommanderProfile::printCosts(std::array <int, 5> costs)
{
	for (int x = 0; x < 5; x++)
		std::cout << CV::RESOURCE_NAMES[x] << " cost: " << costs[x] << std::endl;
	std::cout << std::endl;
}

void CommanderProfile::calculateCommanderScoutLog()
{

}

void CommanderProfile::addLevel() {
	unitLevel++;
}

void CommanderProfile::setDelete() {
	deleteCommander = true;
}

bool CommanderProfile::getDelete() {
	return deleteCommander;
}

bool CommanderProfile::hasMovedQuestion() {
	return hasMoved;
}

void CommanderProfile::resetCommanderMoved() {
	hasMoved = false;
}
