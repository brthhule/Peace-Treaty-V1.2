#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include PARTICIPANTS_HEADER

using namespace PART;

void Participants::moveUnitOne(commSPTR commander) {
	//For debugging
	INF::debugFunction("Mobility, moveUnitOne");

	//This will have the list of provinces that can be moved to
	provSPTRList provincesCanSelect;

	if (commander->hasMoved() == true) {
		std::cout << "This unit has already moved this turn. Please pick another unit. \nReturning to previous menu... \n\n";
	}

	//If this commander has not moved yet
	//Get their system coords
	ipair comamnderSystemCoords = commander->CoordsBASE::getCoords(COORD::SYSTEM); 

	std::cout << "The coordinates of the chosen unit unit are: ";
	commander->printCoords(COORD::USER);
	println("\n\nYou can only move this unit to one of the provinces adjacent to the province it is in");

	//Get list of provinces that can be moved to
	provincesCanSelect = moveUnitTwo(commander);

	// The participant slects coordiantes
	ipair pickUserCoords = pickCoords();

	ipair pickSystemCorods = commander->translateCoords(pickUserCoords, USER); 
	provSPTR provinceSelected = NULL;
	for (provSPTR province : provincesCanSelect) {
		if (userCoords == province->getCoords(COORD::USER)) {
			provinceSelected = province;
		}
	}

	if (provinceSelected == NULL) {
		std::cout << "Invalid province selected... please try again. " << std::endl;
		// Recursion until suitable coordinates are chosen
		moveUnitOne(commander);
	}

	// For display
	ipair systemCoords = provinceSelected->getCoords(COORD::SYSTEM);
	std::string confirmMove;

	enum Scenario {
		ENEMY_PROVINCE,
		FRIENDLY_PROVINCE
	};
	Scenario situation = FRIENDLY_PROVINCE;
	// If province is in the list

	if (provinceSelected->getParticipantIndex() !=
		commander->getParticipantIndex()) {
		situation = ENEMY_PROVINCE;
		println("This is an enemy province. Moving here will attack the enemy garrison stationed here.");
	} else {
		situation = FRIENDLY_PROVINCE;
		std::cout << "This is a friendly province.\n";
	}

	std::cout << "Confirm moving your unit to ";
	provinceSelected->printCoords(COORD::USER);
	std::cout << "? (Y / N) ";

	// If participants confirms movement
	if (Input::getInputText("Confirm Y/N: ", { "Y", "N" }).at(0) == 'Y') {
		// If it's peaceful (moving to one of their own provinces)
		if (situation == FRIENDLY_PROVINCE) {
			//Remove commander from previous province

			partSPTR tempParticipant = new Participants;
			provSPTR formerProvince = tempParticipant->getSystemProvince(commander->getCoords(COORD::SYSTEM));
			formerProvince->removeCommander(commander);

			//Change commander coords to province coords
			ipair tempSystemCoords, tempUserCoords;
			tempSystemCoords = provinceSelected->getCoords(COORD::SYSTEM);
			tempUserCoords = provinceSelected->getCoords(COORD::USER);
			commander->setCoords(tempSystemCoords, tempUserCoords);
			//Add the commander to the province's list of commanders
			provinceSelected->addCommander(commander);

		// If scenario is attack
		} else {
			//Have to work this out
			//AttackMA newAttackMA(selectedCommanderProvince, attackProvince, participant, selectedCommander);
		}
	}

	std::cout << "Returning to previous menu... \n\n";

} /* unfinished*/


std::vector<provSPTR> Participants::moveUnitTwo(commSPTR commander) {
	//For debugging
	INF::debugFunction("Mobility, moveUnitTwo");

	std::vector<provSPTR> provincesSelectList;
	ipair systemCoords = commander->getCoords(COORD::SYSTEM);


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
				partSPTR tempParticipant = new Participants();
				provSPTR province = tempParticipant->getSystemProvince(pushCoords);
				provincesSelectList.push_back(province);
				delete tempParticipant;

			}
		}
	}
	return provincesSelectList;
}
