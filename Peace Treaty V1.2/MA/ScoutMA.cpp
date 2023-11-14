#include "ScoutMA.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

ScoutMA::ScoutMA(Participants* newParticipant, Provinces* newProvince) {
	//For debugging
	INF::debugFunction("ScoutMA, ScoutMA");

	participant = newParticipant;
	yourProvince = newProvince;

	//Default values
	targetProvince = NULL;
	targetParticipant = NULL;
	std::pair<TargetTypes, TargetTypes> tempTypes(PROVINCE, PROVINCE);
	targetInformation = std::pair<std::pair<TargetTypes, TargetTypes>, int>(tempTypes, -1);
	enemyLevel = -1;
}

void ScoutMA::selectTarget()
{
	//For debugging
	INF::debugFunction("ScoutMA, selectTarget");

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
	//For debugging
	INF::debugFunction("ScoutMA, playerScoutStepTwo");

	int accuracy = 0;
	std::vector<int> unitsCanScoutWith;

	std::cout << "You have " << canScout.second.size() << " provinces and " << canScout.first.size() << "armies next to the target. Below is a list of units that can scout the target.";
	std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyLevel << "). \n\n";

	std::pair<int, int> systemCoords;

	AllUnits *unit = selectUnitToScout(canScout);
	Participants* tempParticipant = new Participants();
	Provinces *tempProvince = new Provinces;
	std::cout << "Proceed scout action with unit at " << tempParticipant->getSystemProvince(unit->getSystemCoords()) << "? (Y/N) ";
	delete tempParticipant;

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
	Participants* tempParticipant1 = new Participants();
	participant->scoutProvince(tempParticipant1->getSystemProvince(unit->getSystemCoords()), accuracy);
	delete tempParticipant1;

	INF::enterAnything(1);
}

ScoutMA::scoutTypes ScoutMA::getCanScout()
{
	//For debugging
	INF::debugFunction("ScoutMA, getCanScout");

	std::pair<int, int> targetUserCoords = targetProvince->getUserCoords();
	int targetX = targetUserCoords.first;
	int targetY = targetUserCoords.second;

	ScoutMA::scoutTypes canScout;

	for (int a = -1; a <= 1; a++)
	{
		for (int b = -1; b <= 1; b++)
			getCanScoutTwo(targetX, targetY, a, b, canScout);
	}

	//Error case
	ScoutMA::scoutTypes tempScout (NULL, NULL);
	return tempScout;
}

void ScoutMA::getCanScoutTwo(int targetX, int targetY, int a, int b, ScoutMA::scoutTypes &canScout)
{
	//For debugging
	INF::debugFunction("ScoutMA, getCanScoutTwo");

	if (/*X coordinates*/ targetX + a >= 0 &&
		targetX + a < INF::continentSize && /*Y coordinates*/ targetY + b >= 0 && targetY + b < INF::continentSize)
	{
		Participants* tempParticipant = new Participants;
		Provinces* newProvince = tempParticipant->getSystemProvince(std::pair<int, int>(targetX + a, targetY + b));
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
	//For debugging
	INF::debugFunction("ScoutMA, selectUnitToScout");

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
	//For debugging
	INF::debugFunction("ScoutMA, selectUnitToScoutTwo");

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


