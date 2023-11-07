#include "../Peace Treaty V1.2/Units/Participants.h"

void Participants::moveUnitOne(CommanderProfile* commander) {
	//For debugging
	OF::debugFunction("Database, moveUnitOne");

	//This will have the list of provinces that can be moved to
	std::vector<Provinces*> provincesCanSelect;

	if (commander->hasMovedQuestion() == true) {
		std::cout << "This unit has already moved this turn. Please pick another unit. \nReturning to previous menu... \n\n";
	}
	//If this commander has not moved yet
	//Get their system coords
	std::pair<int, int> newCoordinates = commander->getSystemCoords();

	std::cout << "The coordinates of the chosen unit unit are: ";
	commander->printUserCoords();
	println("\n\nYou can only move this unit to one of the provinces adjacent to the province it is in");

	//Get list of provinces that can be moved to
	provincesCanSelect = moveUnitTwo(commander);

	// The participant slects coordiantes
	std::pair<int, int> userCoords = pickCoords();


	Provinces* provinceSelected = NULL;
	for (Provinces* province : provincesCanSelect) {
		if (userCoords == province->getUserCoords()) {
			provinceSelected = province;
		}
	}

	if (provinceSelected == NULL) {
		std::cout << "Invalid province selected... please try again. " << std::endl;
		// Recursion until suitable coordinates are chosen
		moveUnitOne(commander);
	}

	// For display
	std::pair<int, int> systemCoords = provinceSelected->getSystemCoords();
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
	provinceSelected->printUserCoords();
	std::cout << "? (Y / N) ";

	// If participants confirms movement
	if (Input::getInputText("Confirm Y/N: ", { "Y", "N" }).at(0) == 'Y') {
		// If it's peaceful (moving to one of their own provinces)
		if (situation == FRIENDLY_PROVINCE) {
			//Remove commander from previous province

			Participants* tempParticipant = new Participants;
			tempParticipant->getSystemProvince(commander->getSystemCoords())->removeCommander(commander);
			//Change commander coords to province coords
			commander->setCoords(provinceSelected->getSystemCoords(), provinceSelected->getUserCoords());
			//Add the commander to the province's list of commanders
			provinceSelected->addCommander(commander);
		}
		// If scenario is attack
		else
		{
			//Have to work this out
			//AttackMA newAttackMA(selectedCommanderProvince, attackProvince, participant, selectedCommander);
		}

	}

	std::cout << "Returning to previous menu... \n\n";

} /* unfinished*/


std::vector<Provinces*> Participants::moveUnitTwo(CommanderProfile* commander) {
	//For debugging
	OF::debugFunction("Database, moveUnitTwo");

	std::vector<Provinces*> provincesSelectList;
	std::pair<int, int> systemCoords = commander->getSystemCoords();

	for (int x = -1; x <= 1; x++) /*Identify all the provinces that the player can move a unit to*/
	{
		for (int y = -1; y <= 1; y++) {
			// Check to see if the coordinates are in bounds (not outside of the map
			// size)
			int
				firstCoordinate = systemCoords.first + x,
				secondCoordinate = systemCoords.second + y;
			bool
				checkFirstCoordinate = (
					firstCoordinate >= 0 &&
					firstCoordinate < CV::continentSize
					),
				checkSecondCoordinate = (
					secondCoordinate >= 0 &&
					secondCoordinate < CV::continentSize
					),
					//Returns true if the changed coordinates aren't both the same as the original coordinates
				checkBothCoordinates = (
					firstCoordinate != systemCoords.first ||
					secondCoordinate != systemCoords.second
					);


			if (checkFirstCoordinate && checkSecondCoordinate && checkBothCoordinates)
			{
				std::pair<int, int> pushCoords(firstCoordinate, secondCoordinate);
				Participants* tempParticipant = new Participants();
				Provinces* province = tempParticipant->getSystemProvince(pushCoords);
				provincesSelectList.push_back(province);
				delete tempParticipant;

			}
		}
	}
	return provincesSelectList;
}
