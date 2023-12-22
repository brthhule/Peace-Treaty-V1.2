#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include PARTICIPANTS_HEADER

using namespace PART;
using namespace COORD;



void Participants::moveUnitOne(commSPTR commander) {
	//For debugging
	DEBUG_FUNCTION("Mobility.cpp", "moveUnitOne");

	if (commander->hasMoved() == true) {
		std::cout << "This unit has already moved this turn. Please pick another unit. \nReturning to previous menu... \n\n";
	}

	provSPTR provinceSelected = std::make_shared<Provinces>(pickProvinceToMoveTo(*commander)); 
	std::string confirmMove;

	ProvinceRelation relation = FRIENDLY_PROVINCE;
	// If province is in the list

	if (provinceSelected->getParticipantIndex() !=
		commander->getParticipantIndex()) {
		relation = ENEMY_PROVINCE; 
		println("This is an enemy province. Moving here will attack the enemy garrison stationed here.");
	} else {
		std::cout << "This is a friendly province.\n";
	}

	std::string prompt = "Confirm moving your unit to " + provinceSelected->getCoords(COORD::USER) + "? (Y / N) ";

	// If participants confirms movement
	if (Input::getInputText(prompt, { "Y", "N" }).at(0) == 'N') {
		std::cout << "Cancelling action...\n";
		return;
	}

	if (relation == ENEMY_PROVINCE) {
		//Have to work this out
		//AttackMA newAttackMA(selectedCommanderProvince, attackProvince, participant, selectedCommander);
	}

	// If it's peaceful (moving to one of their own provinces)
	//Remove commander from previous province
	provSPTR formerProvince = Map::getProvince(SYSTEM, commander->CoordsBASE::getCoords(SYSTEM)); 
	formerProvince->removeCommander(commander);
	provinceSelected->addCommander(*commander); 
	std::cout << "Returning to previous menu... \n\n";

} /* unfinished*/


Provinces& Participants::pickProvinceToMoveTo(Commanders& commanderReference) {
	//This will have the list of provinces that can be moved to
	provSPTRList provincesCanSelect;
	std::cout << "The coordinates of the chosen unit unit are: ";
	commSPTR commander = std::make_shared<Commanders>(commanderReference);

	commander->printCoords(COORD::USER); 
	println("\n\nYou can only move this unit to one of the provinces adjacent to the province it is in");

	//Get list of provinces that can be moved to
	provincesCanSelect = getSurroundingProvinces(commander); 

	// The participant slects coordinates
	ipair pickUserCoords = Map::pickCoords();

	if (pickUserCoords.first == -1) {
		std::cout << "Cancelling action...\n";
		INF::enterAndClear(1);
		nullptr;
	}

	provSPTR provinceSelected = Map::getProvince(USER, pickUserCoords);
	bool validProvince = false;
	for (provSPTR provincePtr : provincesCanSelect) {
		if (provincePtr == provinceSelected) {
			validProvince == true;
		}
	}

	if (!validProvince) {
		std::cout << "Invalid province selected... please choose a valid province\n";
		pickProvinceToMoveTo(*commander); 
	}
}

provSPTRList Participants::getSurroundingProvinces(commSPTR commander) {
	//For debugging
	DEBUG_FUNCTION("Mobility.cpp", "getSurroundingProvinces");

	std::vector<provSPTR> provincesSelectList;
	ipair systemCoords = commander->CoordsBASE::getCoords(COORD::SYSTEM);

	/*Identify all the provinces that the player can move a unit to*/
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			// Check to see if the coordinates are in bounds (not outside of the map
			// size)
			int
				firstCoordinate = systemCoords.first + x,
				secondCoordinate = systemCoords.second + y;

			bool
				checkFirstCoordinate = (
					firstCoordinate >= 0 &&
					firstCoordinate < INF::continentSize),
				checkSecondCoordinate = (
					secondCoordinate >= 0 &&
					secondCoordinate < INF::continentSize),
					//Returns true if the changed coordinates aren't both the same as the original coordinates
				checkBothCoordinates = (
					firstCoordinate != systemCoords.first ||
					secondCoordinate != systemCoords.second);


			if (checkFirstCoordinate && checkSecondCoordinate && checkBothCoordinates){
				ipair pushCoords(firstCoordinate, secondCoordinate);
				provSPTR province = Map::getProvince(SYSTEM, pushCoords);
				provincesSelectList.push_back(std::make_shared<Provinces>(*province)); 
			}
		}
	}
	return provincesSelectList;
}
