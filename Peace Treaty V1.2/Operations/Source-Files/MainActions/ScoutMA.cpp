#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER

using namespace PROV;
using namespace COMM;
using namespace PART;
using namespace COORD;

/*Main ScoutMA function. Takes a target province pointer as a parameter
If the target */
void Participants::mainScoutMA(PROV::provSPTR provinceArg) {
	//For debugging
	DEBUG_FUNCTION("ScoutMA, mainScoutmA");

	PROV::provSPTR yourProvince = provinceArg;
	PROV::provSPTR targetProvince = this->pickProvince(1);
	
	ScoutMA::scoutTypes canScout = selectTarget(targetProvince);
	unitSPTR scoutUnit = nullptr;
	COMM::commSPTRList commList = canScout.first;
	PROV::provSPTRList provList = canScout.second;


	int accuracy = 0;
	//If the lists are not of null type
	if (commList.at(0) != nullptr || provList.at(0) != nullptr) {
		std::pair<unitSPTR, int> tempPair = playerScoutStepTwo(canScout, targetProvince);
		scoutUnit = tempPair.first;
		accuracy = tempPair.second;
	}

	scoutProvince(getSystemProvince(scoutUnit->getCoords(CoordsBASE::SYSTEM)), accuracy);

	INF::enterAnything(1);
}

/*Selects a target to scout*/
ScoutMA::scoutTypes Participants::selectTarget(PROV::provSPTR targetProvince)
{
	//For debugging
	DEBUG_FUNCTION("ScoutMA, selectTarget");

	//The participant selects a province
	//Make sure the province being scouted is not the current participant's 
	if (this->hasProvince(targetProvince)) {
		std::cout << "This province belongs to you; please select a different province";
		selectTarget(this->pickProvince(1));
	}

	//If the selected province doesn't belong to the participant
	std::cout << "Province " << targetProvince->getName() << " selected \n";
	std::cout << "You can only scout this unit if one of your provinces or commanders is next to it... \n";

	//Check nearby provinces
	ScoutMA::scoutTypes canScout = getCanScout(targetProvince);
	// If there are commanders or provinces that can scout the target
	if (canScout.first.size() > 0 || canScout.second.size() > 0) {
		return canScout;
	}
	else {
		std::cout << "No player provinces or armies are around the target... \n";
		COMM::commSPTRList commList = {nullptr};
		PROV::provSPTRList provList = {nullptr};
		canScout = std::make_pair(commList, provList);
	}
	std::cout << "Returning to previous menu\n\n";

	return canScout;
} /*fix this-- needs to be reviewed*/



ScoutMA::scoutTypes Participants::getCanScout(PROV::provSPTR targetProvince)
{
	//For debugging
	DEBUG_FUNCTION("ScoutMA, getCanScout");

	ipair targetUserCoords = targetProvince->getCoords(USER);
	int targetX = targetUserCoords.first;
	int targetY = targetUserCoords.second;

	ScoutMA::scoutTypes canScout;

	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			getCanScoutTwo(targetX, targetY, a, b, canScout);
		}
	}

	//Error case
	ScoutMA::scoutTypes tempScout({nullptr}, {nullptr});
	return tempScout;
}

void Participants::getCanScoutTwo(int targetX, int targetY, int a, int b, ScoutMA::scoutTypes &canScout) 
{
	//For debugging
	DEBUG_FUNCTION("ScoutMA, getCanScoutTwo");

	bool xCoordsCondition = targetX + a >= 0 && targetX + a < INF::continentSize;
	bool yCoordsCondition = targetY + b >= 0 && targetY + b < INF::continentSize;
	if (!xCoordsCondition || !yCoordsCondition) {
		//Check this later
		std::cout << "Cannot scout...\n";
	}
	
	ipair tempPair(targetX + a, targetY + b);
	PROV::provSPTR newProvince = this->getSystemProvince(tempPair);
	if (newProvince->getParticipantIndex() == this->participantIndex) {
		canScout.second.push_back(newProvince);
	}

	typedef std::unordered_map<std::string, COMM::commSPTR> commandersPtrMap;
	commandersPtrMap newMap = this->getCommandersMap(); 
	commandersPtrMap::iterator it;
	for (it = newMap.begin(); it != newMap.end(); it++){
		if (it->second->getCoords(USER) == newProvince->getCoords(USER))
			canScout.first.push_back(it->second);
	}

	for (COMM::commSPTR commander : commandersVector) { 
		//Add implementation
	}
	
}

UNIT::unitSPTR Participants::selectUnitToScout(ScoutMA::scoutTypes canScout) {
	//For debugging
	DEBUG_FUNCTION("ScoutMA, selectUnitToScout");

	int unitLevel = 0;
	std::cout << "\033[;34m";

	// For all the provinces in the std::vector

	std::cout << "Provinces that can scout: \n";
	for (PROV::provSPTR province : canScout.second) {
		std::cout << province->getName() + "; ";
		province->printCoords(USER);
		std::cout << "; Level: " << province->getLevel() << std::endl;
	}

	std::cout << "Commanders that can scout: \n";
	for (COMM::commSPTR commander : canScout.first) {
		std::cout << commander->getName() << "; ";
		commander->printCoords(USER);
		std::cout << "; Level: " << commander->getLevel() << std::endl;
	}
	std::cout << "\n\033[;0m";

	return selectUnitToScoutTwo(canScout);
}

unitSPTR Participants::selectUnitToScoutTwo(ScoutMA::scoutTypes canScout){
	//For debugging
	DEBUG_FUNCTION("ScoutMA, selectUnitToScoutTwo");

	std::string unitName;
	print("Enter the name of the province/commander you wish to select to scout: ");
	std::getline(std::cin, unitName);

	if (this->hasUnit(unitName) == false) { 
		std::cout << "Invalid name entered; please try again \n";
		selectUnitToScoutTwo(canScout);
	}

	println(unitName + " selected...");

	//If a province has the name, isProvince is true; otherwise, it is false
	for (PROV::provSPTR province : canScout.second) {
		if (unitName == province->getName()) {
			return province;
		}
	}
	for (COMM::commSPTR commander : canScout.first) {
		if (unitName == commander->getName()) {
			return commander;
		}
	}
	//Error path
	return nullptr;
}


/*Add implementation later*/
void Participants::scoutProvince(PROV::provSPTR targetProvince, int accuracy) {
	//For debugging
	DEBUG_FUNCTION("Participants, scoutProvince");

}


// Returns a pair-- first: unit to scout with, second: accuracy
std::pair <unitSPTR, int> Participants::playerScoutStepTwo(ScoutMA::scoutTypes canScout, PROV::provSPTR targetProvince) {
	//For debugging
	DEBUG_FUNCTION("ScoutMA, playerScoutStepTwo");

	int accuracy = 0;
	std::vector<int> unitsCanScoutWith;

	PART::partSPTR targetParticipant = nullptr;
	int index = targetProvince->getParticipantIndex();

	if (index >= 0) {
		targetParticipant = playersList.at(index);
	} else {
		targetParticipant = botsList.at(index);
	}

	int enemyLevel = targetProvince->getLevel();//Fix this later


	std::cout << "You have " << canScout.second.size() << " provinces and " << canScout.first.size() << "armies next to the target. Below is a list of units that can scout the target.";
	std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyLevel << "). \n\n";

	unitSPTR unit = selectUnitToScout(canScout);
	std::cout << "Proceed scout action with unit at " << getSystemProvince(unit->getCoords(CoordsBASE::SYSTEM)) << "? (Y/N) ";

	char proceedWithScoutChar = Input::getInputText("", { "Y", "N" }).at(0);
	if (proceedWithScoutChar == 'N') {
		std::cout << "Returning to previous page...\n";
		unitSPTR unit = nullptr;
		return std::make_pair(unit, -1);
	}

	accuracy = 50;
	int unitLevel = unit->getLevel();

	//Greater level comapred to target = greater accuracy
	if (unitLevel > enemyLevel) {
		for (int x = unitLevel; x >= enemyLevel; x--) {
			accuracy += 5;
		}
	} else if (unitLevel < enemyLevel) {
		for (int x = unitLevel; x <= enemyLevel; x++) {
			accuracy -= 5;
		}
	}

	if (accuracy > 100) {
		accuracy = 100;
	} else if (accuracy < 0) {
		accuracy = 0;
	}

	return std::make_pair(unit, accuracy);
}