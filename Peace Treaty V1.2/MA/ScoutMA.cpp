#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Participants.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

Participants::ScoutInfo::ScoutInfo(Provinces* newProvince) {
	Participants::ScoutInfo::participant = this;
	Participants::ScoutInfo::targetParticipant = NULL;
	Participants::ScoutInfo::yourProvince = newProvince;
	Participants::ScoutInfo::targetProvince = NULL;
}
/*Constructor*/
Participants::mainScoutMA() {
	//For debugging
	INF::debugFunction("ScoutMA, mainScoutmA");
	ScoutMA::scoutTypes canScout = selectTarget();
	if (canScout != NULL) {
		playerScoutStepTwo(canScout);
	}
}

/*Selects a target to scout*/
ScoutMA::scoutTypes Participants::selectTarget()
{
	//For debugging
	INF::debugFunction("ScoutMA, selectTarget");

	//The participant selects a province
	ScoutInfo::targetProvince = this->pickProvince(1);

	//Make sure the province being scouted is not the current participant's 
	if (this->hasProvince(targetProvince)) {
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
		return canScout;
	}
	else {
		std::cout << "No player provinces or armies are around the target... \n";
		canScout = NULL;
	}
	std::cout << "Returning to previous menu\n\n";

	return canScout;
} /*fix this-- needs to be reviewed*/


// Finish this later
void Participants::playerScoutStepTwo(scoutTypes canScout) 
{
	//For debugging
	INF::debugFunction("ScoutMA, playerScoutStepTwo");

	int accuracy = 0;
	std::vector<int> unitsCanScoutWith;

	int enemyLevel = ScoutInfo::targetParticipant->getLevel();//Fix this later


	std::cout << "You have " << canScout.second.size() << " provinces and " << canScout.first.size() << "armies next to the target. Below is a list of units that can scout the target.";
	std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyLevel << "). \n\n";

	std::pair<int, int> systemCoords;

	AllUnits *unit = selectUnitToScout(canScout);
	Participants* tempParticipant = new Participants();
	Provinces *tempProvince = new Provinces;
	std::cout << "Proceed scout action with unit at " << tempParticipant->getSystemProvince(unit->getCoords(SYSTEM)) << "? (Y/N) ";
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

	this->scoutProvince(this->getSystemProvince(unit->getCoords(SYSTEM)), accuracy);

	INF::enterAnything(1);
}

ScoutMA::scoutTypes Participants::getCanScout()
{
	//For debugging
	INF::debugFunction("ScoutMA, getCanScout");

	std::pair<int, int> targetUserCoords = ScoutInfo::targetProvince->getCoords(USER);
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

void Participants::getCanScoutTwo(int targetX, int targetY, int a, int b, ScoutMA::scoutTypes &canScout)
{
	//For debugging
	INF::debugFunction("ScoutMA, getCanScoutTwo");

	bool xCoordsCondition = targetX + a >= 0 && targetX + a < INF::continentSize;
	bool yCoordsCondition = targetY + b >= 0 && targetY + b < INF::continentSize;
	if (!xCoordsCondition || !yCoordsCondition) {
		//Check this later
		std::cout << "Cannot scout...\n";
	}
	
	std::pair<int, int> tempPair(targetX + a, targetY + b);
	Provinces* newProvince = this->getSystemProvince(tempPair);
	if (newProvince->getParticipantIndex() == participant->getParticipantIndex()) {
		canScout.second.push_back(newProvince);
	}

	typedef std::unordered_map<std::string, Commanders
	std::unordered_map<std::string, Commanders*> newMap = this->getCommandersMap();
	std::unordered_map<std::string, Commanders*>::iterator it;
	for (it = newMap.begin(); it != newMap.end(); it++)
	{
		if (it->second->getCoords(USER) == newProvince->getCoords(USER))
			canScout.first.push_back(it->second);
	}

	for (Commanders c : commandersVector) {
		if ()
	}
	
}

AllUnits * Participants::selectUnitToScout(ScoutMA::scoutTypes canScout) {
	//For debugging
	INF::debugFunction("ScoutMA, selectUnitToScout");

	int unitLevel = 0;
	std::cout << "\033[;34m";

	// For all the provinces in the std::vector

	std::cout << "Provinces that can scout: " << std::endl;
	for (Provinces* province : canScout.second) {
		std::cout << province->getUnitName() + "; ";
		province->printCoords(USER);
		std::cout << "; Level: " << province->getLevel() << std::endl;
	}

	std::cout << "Commanders that can scout: \n";
	for (Commanders* commander : canScout.first) {
		std::cout << commander->getUnitName() << "; ";
		commander->printCoords(USER);
		std::cout << "; Level: " << commander->getLevel() << std::endl;
	}
	std::cout << "\n\033[;0m";

	return selectUnitToScoutTwo(canScout);
}

AllUnits * Participants::selectUnitToScoutTwo(ScoutMA::scoutTypes canScout)
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
	for (Commanders* commander : canScout.first) {
		if (unitName == commander->getUnitName()) {
			return commander;
		}
	}
	//Error path
	return NULL;
}


