#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Participants.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;


/*Main ScoutMA function. Takes a target province pointer as a parameter
If the target */
void Participants::mainScoutMA(Provinces* provinceArg) {
	//For debugging
	INF::debugFunction("ScoutMA, mainScoutmA");

	Provinces* yourProvince = provinceArg;
	Provinces* targetProvince = this->pickProvince(1);
	
	ScoutMA::scoutTypes canScout = selectTarget(targetProvince);
	AllUnits *scoutUnit = nullptr;

	int accuracy = 0;
	if (canScout.first == nullptr || nullptr.second = nullptr) {
		std::pair<AllUnits*, int> tempPair = playerScoutStepTwo(canScout, targetProvince);
		scoutUnit = tempPair.first;
		accuracy = tempPair.second;
	}

	scoutProvince(getSystemProvince(scoutUnit->getCoords(Coords::SYSTEM)), accuracy);

	INF::enterAnything(1);
}

/*Selects a target to scout*/
ScoutMA::scoutTypes Participants::selectTarget(Provinces* targetProvince)
{
	//For debugging
	INF::debugFunction("ScoutMA, selectTarget");

	//The participant selects a province
	

	//Make sure the province being scouted is not the current participant's 
	if (this->hasProvince(targetProvince)) {
		std::cout << "This province belongs to you; please select a different province";
		selectTarget(this->pickProvince(1));
	}

	//If the selected province doesn't belong to the participant
	std::cout << "Province " << targetProvince->getUnitName() << " selected \n";
	std::cout << "You can only scout this unit if one of your provinces or commanders is next to it... \n";

	//Check nearby provinces
	ScoutMA::scoutTypes canScout = getCanScout(targetProvince);
	// If there are commanders or provinces that can scout the target
	if (canScout.first.size() > 0 || canScout.second.size() > 0) {
		return canScout;
	}
	else {
		std::cout << "No player provinces or armies are around the target... \n";
		canScout = std::make_pair(nullptr, nullptr);
	}
	std::cout << "Returning to previous menu\n\n";

	return canScout;
} /*fix this-- needs to be reviewed*/


// Finish this later
std::pair <AllUnits*, int> Participants::playerScoutStepTwo(scoutTypes canScout, Provinces* targetProvince) 
{
	//For debugging
	INF::debugFunction("ScoutMA, playerScoutStepTwo");

	int accuracy = 0;
	std::vector<int> unitsCanScoutWith;

	Participants* targetParticipant = nullptr;
	int index = targetProvince->getParticipantIndex();
	if (index >= 0) {
		targetParticipant = playersList.at(index);
	} else {
		targetParticipant = botsList.at(index);
	}

	int enemyLevel = targetProvince->getLevel();//Fix this later


	std::cout << "You have " << canScout.second.size() << " provinces and " << canScout.first.size() << "armies next to the target. Below is a list of units that can scout the target.";
	std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyLevel << "). \n\n";

	std::pair<int, int> systemCoords;

	AllUnits *unit = selectUnitToScout(canScout);


	std::cout << "Proceed scout action with unit at " << getSystemProvince(unit->getCoords(Coords::SYSTEM)) << "? (Y/N) ";

	char proceedWithScoutChar = Input::getInputText("", { "Y", "N" }).at(0);

	if (proceedWithScoutChar == 'Y'){
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

	return std::make_pair(unit, accuracy);
}

ScoutMA::scoutTypes Participants::getCanScout(Provinces* targetProvince)
{
	//For debugging
	INF::debugFunction("ScoutMA, getCanScout");

	std::pair<int, int> targetUserCoords = targetProvince->getCoords(Coords::USER);
	int targetX = targetUserCoords.first;
	int targetY = targetUserCoords.second;

	ScoutMA::scoutTypes canScout;

	for (int a = -1; a <= 1; a++)
	{
		for (int b = -1; b <= 1; b++)
			getCanScoutTwo(targetX, targetY, a, b, canScout);
	}

	//Error case
	ScoutMA::scoutTypes tempScout({}, {});
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
	if (newProvince->getParticipantIndex() == this->participantIndex) {
		canScout.second.push_back(newProvince);
	}

	typedef std::unordered_map<std::string, Commanders*> commandersPtrMap;
	commandersPtrMap newMap = this->getCommandersMap();
	commandersPtrMap::iterator it;
	for (it = newMap.begin(); it != newMap.end(); it++){
		if (it->second->getCoords(Coords::USER) == newProvince->getCoords(Coords::USER))
			canScout.first.push_back(it->second);
	}

	for (Commanders c : commandersVector) {
		//Add implementation
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
		province->printCoords(Coords::USER);
		std::cout << "; Level: " << province->getLevel() << std::endl;
	}

	std::cout << "Commanders that can scout: \n";
	for (Commanders* commander : canScout.first) {
		std::cout << commander->getUnitName() << "; ";
		commander->printCoords(Coords::USER);
		std::cout << "; Level: " << commander->getLevel() << std::endl;
	}
	std::cout << "\n\033[;0m";

	return selectUnitToScoutTwo(canScout);
}

AllUnits* Participants::selectUnitToScoutTwo(ScoutMA::scoutTypes canScout){
	//For debugging
	INF::debugFunction("ScoutMA, selectUnitToScoutTwo");

	std::string unitName;
	print("Enter the name of the province/commander you wish to select to scout: ");
	std::getline(std::cin, unitName);

	if (this->hasUnit(unitName) == false) { 
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
	return nullptr;
}


/*Add implementation later*/
void Participants::scoutProvince(Provinces* targetProvince, int accuracy) {
	//For debugging
	INF::debugFunction("Participants, scoutProvince");

}