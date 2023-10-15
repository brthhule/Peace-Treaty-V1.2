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
  std::cout << "\033[;34m";
  int c = 0;
  for (int a = 0; a < 4; a++) {
    std::cout << MANDescriptions[a] << " this army: \n";
    for (int b = 0; b < 5; b++) {
      std::cout << "- " << namesOfMANOne[a][b] << ": " << *commanderArrays[a][b]
                << std::endl;
      c++;
    }
  }

	std::cout << MANDescriptions[5] << ": \n";
  std::cout << "\n\033[;0m";
}
int CommanderProfile::getCommanderStat(int index) {
	//placeholder
	return -1;
  //return *commanderArmyStats[index];
}
int CommanderProfile::printCommanderScoutReport(int index) {
  return commanderScoutReport[index];
}


void CommanderProfile::updateCommanderScoutReport(int index, int value) {
  //commanderScoutReport[index] = value;
}

void CommanderProfile::completeCommanderScoutReport(int accuracy) {
  /*Higher accuracy = more accurate scout log-- default is 50% accuracy (if
  there are 10 food resources in a province,
  the margin is 50%-- 5-15 units. 100 accuracy is the most accurate, 0 accuracy
  is the least accurate*/
  double newAccuracy = (double)accuracy / 100;
  newAccuracy = 1 - newAccuracy;
  double accuracyAdjustedValueOne;
  int accuracyAdjustedValueTwo;
  int fooOne;
  int fooTwo;
  int findRange;
  for (int x = 0; x < 20; x++) {
    findRange = getCommanderStat(x);
    accuracyAdjustedValueOne = findRange * newAccuracy;
    fooOne = findRange - (int)accuracyAdjustedValueOne;
    fooTwo = findRange + (int)accuracyAdjustedValueOne;
    accuracyAdjustedValueTwo = rand() % fooOne + fooTwo;
    updateCommanderScoutReport(x, accuracyAdjustedValueTwo);
  }
  updateCommanderScoutReport(20, turn);
  updateCommanderScoutReport(21, accuracy);
}

std::array<int, 5> CommanderProfile::getUpgradeCosts(){
  std::array<int, 5> costsArray;
	for (int &x: costsArray) x = 0;
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
