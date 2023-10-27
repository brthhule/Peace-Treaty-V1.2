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
}

void ScoutMA::selectTarget()
{
	//The participant selects a province
	Provinces* targetProvince = participant->getCoords(1);

	//If the province belongs to the participant
	if (targetProvince->getParticipantIndex() == participant->getParticipantIndex()) {
		std::cout << "This province belongs to you; please select a different province";
		selectTarget();
	}

	//If the selected province doesn't belong to the participant
	std::cout << "Province " << targetProvince->getUnitName() << " selected \n";
	std::cout << "You can only scout this unit if one of your provinces or commanders is next to it... \n";

	//Check nearby provinces
	ScoutMA::scoutTypes canScout = getCanScout();
	// If there are commanders or provinces that can scout the target
	if (canScout.first.size() > 0 || canScout.second.size() > 0) {
		playerScoutStepTwo(canScout);
	}
	else {
		std::cout << "No player provinces or armies are around the target... \n";
	}
	std::cout << "Returning to previous menu\n\n";
} /*fix this-- needs to be reviewed*/


void ScoutMA::playerScoutStepTwo(scoutTypes canScout) // Finish this later
{
	int accuracy = 0;
	std::vector<int> unitsCanScoutWith;

	std::cout << "You have " << canScout.second.size() << " provinces and " << canScout.first.size() << "armies next to the target. Below is a list of units that can scout the target.";
	std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyLevel << "). \n\n";

	std::pair<int, int> systemCoords;

	AllUnits *unit = selectUnitToScout(canScout);
	Participants tempParticipant(-1000000000000);
	Provinces tempProvince();
	std::cout << "Proceed scout action with unit at " << tempParticipant.getSystemProvince(unit->getSystemCoords()) << "? (Y/N) ";
	char proceedWithScoutChar = Input::getInputText("", { "Y", "N" }).at(0);

	if (proceedWithScoutChar == 'Y')
	{
		int accuracy = 50;
		int unitLevel = unit->getLevel();

		//Greater level comapred to target = greater accuracy
		if (unitLevel > enemyLevel)
			for (int x = unitLevel; x >= enemyLevel; x--)
				accuracy += 5;
		if (unitLevel < enemyLevel)
			for (int x = unitLevel; x <= enemyLevel; x++)
				accuracy -= 5;
	}

	if (accuracy > 100) {
		accuracy = 100;
	}
	else if (accuracy < 0) {
		accuracy = 0;
	}
		
	participant->scoutProvince(tempParticipant.getSystemProvince(unit->getSystemCoords()), accuracy);
	OF::enterAnything();
}

ScoutMA::scoutTypes ScoutMA::getCanScout()
{
	std::pair<int, int> targetUserCoords = targetProvince->getUserCoords();
	int targetX = targetUserCoords.first;
	int targetY = targetUserCoords.second;

	ScoutMA::scoutTypes canScout;

	for (int a = -1; a <= 1; a++)
	{
		for (int b = -1; b <= 1; b++)
			getCanScoutTwo(targetX, targetY, a, b, canScout);
	}
}

void ScoutMA::getCanScoutTwo(int targetX, int targetY, int a, int b, ScoutMA::scoutTypes &canScout)
{
	if (/*X coordinates*/ targetX + a >= 0 &&
		targetX + a < CV::continentSize && /*Y coordinates*/ targetY + b >= 0 && targetY + b < CV::continentSize)
	{
		Provinces* newProvince = &provincesMap[targetX + a][targetY + b];
		if (newProvince->getParticipantIndex() == participant->getParticipantIndex()) {
			canScout.second.push_back(newProvince);
		}

		std::unordered_map<std::string, CommanderProfile*> newMap = participant->getCommandersMap();
		std::unordered_map<std::string, CommanderProfile*>::iterator it;
		for (it = newMap.begin(); it != newMap.end(); it++)
		{
			if (it->second->getUserCoords() == newProvince->getUserCoords())
				canScout.first.push_back(it->second);
		}
	}
}

AllUnits *ScoutMA::selectUnitToScout(ScoutMA::scoutTypes canScout) {
	int unitLevel = 0;
	std::cout << "\033[;34m";

	// For all the provinces in the std::vector

	std::cout << "Provinces that can scout: " << std::endl;
	for (Provinces* province : canScout.second) {
		std::cout << province->getUnitName() + "; ";
		province->printUserCoords();
		std::cout << "; Level: " << province->getLevel() << std::endl;
	}

	std::cout << "Commanders that can scout: \n";
	for (CommanderProfile* commander : canScout.first) {
		std::cout << commander->getUnitName() << "; ";
		commander->printUserCoords();
		std::cout << "; Level: " << commander->getLevel() << std::endl;
	}
	std::cout << "\n\033[;0m";

	return selectUnitToScoutTwo(canScout);
}

AllUnits *ScoutMA::selectUnitToScoutTwo(ScoutMA::scoutTypes canScout)
{
	std::string unitName;
	print("Enter the name of the province/commander you wish to select to scout: ");
	std::getline(std::cin, unitName);

	if (participant->hasUnit(unitName) == false) {
		std::cout << "Invalid name entered; please try again \n";
		selectUnitToScoutTwo(canScout);
	}

	println(unitName + " selected...");

	//If a province has the name, isProvince is true; otherwise, it is false
	for (Provinces* province : canScout.second) {
		if (unitName == province->getUnitName()) {
			return province;
		}
	}
	for (CommanderProfile* commander : canScout.first) {
		if (unitName == commander->getUnitName()) {
			return commander;
		}
	}
	//Error path
	return NULL;
}


