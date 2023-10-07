#include "ScoutMA.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

extern std::vector<std::vector<Provinces>> provincesMap;
extern std::vector<Participants> participantsList;
extern std::vector<std::vector<CommanderProfile>> allCommanders;
extern int currentParticipantIndex;
extern int continentSize;

ScoutMA::ScoutMA(Participants* newParticipant, Provinces* newProvince) {
  participant = newParticipant;
  yourProvince = newProvince;
	provincesCanScout = {};
	commandersCanScout = {};
}

void ScoutMA::selectTarget()
{
  Provinces *targetProvince = participant->getCoords(1);
  if (targetProvince->getParticipantIndex() == participant->getParticipantIndex())
	{
		std::cout << "This province belongs to you; please select a different province";
		selectTarget();
	}
	
  std::cout << "Province " << targetProvince->getUnitName() << " selected \n";
  std::cout << "You can only scout this unit if one of your provinces or commanders is next to it... \n";

	//Check nearby provinces
	getCanScout();
  // If there are commanders or provinces that can scout the target
  if (provincesCanScout.size() > 0 || commandersCanScout.size() > 0) {
    playerScoutStepTwo();
  } else {
    std::cout << "No player provinces or armies are around the target... \n";
  }
  std::cout << "Returning to previous menu\n\n";
} /*fix this-- needs to be reviewed*/


void ScoutMA::playerScoutStepTwo() // Finish this later
{
  int accuracy = 0;
  std::vector<int> unitsCanScoutWith;

  std::cout << "You have " << provincesCanScout.size() << " provinces and " << commandersCanScout.size() << "armies next to the target. Below is a list of units that can scout the target.";
  std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyLevel << "). \n\n";

	std::string returnUnitName = " ";
	bool isProvince = false;
	std::array<int, 2> coordinates;
	
  int unitLevel = selectUnitToScout(returnUnitName, isProvince, coordinates);

  std::cout << "Proceed scout action with unit at " << OF::printCoordinates(coordinates) << "? (Y/N) ";
  char proceedWithScoutChar = OF.getInput(false, -1, " ", {"Y", "N"}, false, false).at(0);

  if (proceedWithScoutChar == 'Y') 
	{
    int accuracy = 50;

		//Greater level comapred to target = greater accuracy
    if (unitLevel > enemyLevel) 
      for (int x = unitLevel; x >= enemyLevel; x--) 
        accuracy += 5;
    if (unitLevel < enemyLevel) 
      for (int x = unitLevel; x <= enemyLevel; x++) 
        accuracy -= 5;
	}
		
	if (accuracy > 100) 
		accuracy = 100;
	if (accuracy < 0) 
		accuracy = 0;

	participant->scoutProvince(&provincesMap[coordinates[0]][coordinates[1]], accuracy);
	OF::enterAnything();
}

void ScoutMA::getCanScout()
{
	int targetX = targetProvince->getCoordinate('X');
	int targetY = targetProvince->getCoordinate('Y');
	
	for (int a = -1; a <= 1; a++)
  {
    for (int b = -1; b <= 1; b++) 
			getCanScoutTwo(targetX, targetY, a, b);
  }
}

void ScoutMA::getCanScoutTwo (int targetX, int targetY, int a, int b)
{
	if (/*X coordinates*/ targetX + a >= 0 &&
			targetX + a < continentSize && /*Y coordinates*/ targetY + b >= 0 && targetY + b < continentSize) 
  {
    Provinces* newProvince = &provincesMap[targetX + a][targetY + b];
		if (newProvince->getParticipantIndex() == participant->getParticipantIndex()) {
			provincesCanScout.push_back(newProvince);
		}

    std::unordered_map<std::string, CommanderProfile*> newMap = participant->getCommandersMap();
    std::unordered_map<std::string, CommanderProfile*>::iterator it;
		for (it = newMap.begin(); it != newMap.end(); it++) 
    {
			if (it->second->getCoordinates() == newProvince->getCoordinates())
				commandersCanScout.push_back(it->second);
		}
	}
}

int ScoutMA::selectUnitToScout(std::string &unitName, bool &isProvince, std::array<int, 2> &coordinates) {
	int unitLevel = 0;
	std::cout << "\033[;34m";
 
  // For all the provinces in the std::vector

  std::cout << "Provinces that can scout: " << std::endl;
  for (Provinces* province: provincesCanScout) {
    std::cout<< province->getUnitName() + "; " + province->printOutputCoordinates() + "; Level: " << province->getLevel() << std::endl;
  }

  std::cout << "Commanders that can scout: \n";
  for (CommanderProfile* commander: commandersCanScout) {
    std::cout<< commander->getUnitName() << "; " + commander->printOutputCoordinates() + "; Level: " << commander->getLevel() << std::endl;
  }
  std::cout << "\n\033[;0m";

	return selectUnitToScoutTwo(unitName, isProvince, coordinates);
}

int ScoutMA::selectUnitToScoutTwo(std::string &unitName, bool &isProvince, std::array<int, 2> &coordinates)
{
  int unitLevel = 0;
	print("Enter the name of the province/commander you wish to select to scout: ");
	std::getline(std::cin, unitName);

	if (checkHasUnit(unitName) == false)
	{
		std::cout << "Invalid name entered; please try again \n";
		selectUnitToScoutTwo(unitName, isProvince, coordinates);
	}
  
	println(unitName + " selected...");

  //If a province has the name, isProvince is true; otherwise, it is false
	isProvince = false;
	for(Provinces* province: provincesCanScout)
		if (unitName == province -> getUnitName())
		{
			isProvince = true;
			coordinates = province->getCoordinates();
      unitLevel = province->getLevel();
		}
	for (CommanderProfile* commander: commandersCanScout)
		if (unitName == commander->getUnitName())
    {
			coordinates = commander->getCoordinates();
      unitLevel = commander->getLevel();
    }
	
  return unitLevel;
}

bool ScoutMA::checkHasUnit (std::string unitName)
{
	for (Provinces* province: provincesCanScout)
		if (unitName == province->getUnitName())
			return true;
	for (CommanderProfile* commander: commandersCanScout)
		if (unitName == commander -> getUnitName())
			return true;
	return false;
}
