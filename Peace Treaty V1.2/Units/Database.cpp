#include "Database.h"

Database::Database() {
	//For debugging
	OF::debugFunction("Database, Database");

	//Default
	pNum = 0;
	maxCommanders = 0;
	currentParticipant = NULL;

}

void Database::updateTurnResources() {
	//For debugging
	OF::debugFunction("Database, updateTurnResources");

	Participants* tempParticipant = new Participants;
	tempParticipant->updateTurnResourcesParticipant();
}

void Database::initializeParticipants(int totalPlayers, int humanPlayers) {
	//For debugging
	OF::debugFunction("Database, initializeParticipant");

	for (int x = 0; x < pNum; x++)
	{
		std::cout << "Creating participant " << x + 1 << ": " << std::endl;
		Participants newParticipant(x);

		//Create players many players
		if (x < totalPlayers /*I don't know if this is right*/) {
			newParticipant.createAsPlayer(true);
		} /*Everyone else is enemy AI*/ else {
			newParticipant.createAsPlayer(false);
		}

		participantsList.push_back(newParticipant);
	}

	createCapitals();
}

std::vector <Participants> *Database::getParticipantsList() {
	//For debugging
	OF::debugFunction("Database, getParticipantsList");

	return &participantsList;
}

void Database::setMaxCommanders(int num) {
	//For debugging
	OF::debugFunction("Database, setMaxCommanders");

	maxCommanders = num;
}
int Database::getMaxCommanders() {
	//For debugging
	OF::debugFunction("Database, getMaxCommanders");

	return maxCommanders;
}

void Database::setCurrentParticipant(Participants* p) {
	//For debugging
	OF::debugFunction("Database, setCurrentParticipant");

	currentParticipant = p;
}

Participants *Database::getCurrentParticipant() {
	//For debugging
	OF::debugFunction("Database, getCurrentParticipant");

	return currentParticipant;
}

bool Participants::isPlayer() {
	//For debugging
	OF::debugFunction("Database, isPlayer");

	return playerStatus;
}

void Participants::setPlayerStatus(bool status) {
	//For debugging
	OF::debugFunction("Database, setPlayerStatus");

	playerStatus = status;
}

Participants *Database::getParticipant(int index) {
	//For debugging
	OF::debugFunction("Database, getParticipant");

	return &participantsList[index];
}


void Database::Mobility::moveUnitOne(CommanderProfile* commander) {
	//For debugging
	OF::debugFunction("Database, moveUnitOne");

	//This will have the list of provinces that can be moved to
	std::vector<Provinces*> provincesCanSelect;

	if (commander->hasMovedQuestion() == true) {
		std::cout
			<< "This unit has already moved this turn. Please pick another unit. \n";
		std::cout << "Returning to previous menu... \n\n";
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
	for (Provinces *province:provincesCanSelect) {
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
	}
	else {
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


std::vector<Provinces*> Database::Mobility::moveUnitTwo(CommanderProfile* commander) {
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

std::pair<int, int> Database::pickCoords() {
	//For debugging
	OF::debugFunction("Database, pickCoords");

	Participants* tempParticipant = new Participants();
	tempParticipant->showMap();
	delete tempParticipant;

	std::string
		xCoordinateString,
		yCoordinateString;

	std::cout << "Enter an x coordinate: ";
	getline(std::cin, xCoordinateString);
	std::cout << "Enter a y coordinate: ";
	getline(std::cin, yCoordinateString);

	int
		xCoordinate = std::stoi(xCoordinateString),
		yCoordinate = std::stoi(yCoordinateString);

	if (xCoordinate > 0 && xCoordinate <= CV::continentSize && yCoordinate > 0 && yCoordinate <= CV::continentSize) {
		return { xCoordinate, yCoordinate };
	}

	OF::addColor(RED);
	std::cout << "Inputed coordinates are out of bounds... please try again.";
	OF::addColor(RESET);
	pickCoords();

	//Error path
	std::pair<int, int> tempPair(-1, -1);
	return tempPair;
}

void Database::createCapitals() {
	//For debugging
	OF::debugFunction("Database, createCapitals()");

	for (Participants participant : participantsList) {
		start:
			std::pair<int, int> systemCoords;
			systemCoords.first = rand() % CV::continentSize;
			systemCoords.second = rand() % CV::continentSize;

			Provinces* province = participantsList[0].getSystemProvince(systemCoords);

			if (province->getParticipantIndex() == -1)
			{
				province->changeParticipantIndex(participant.getParticipantIndex());
				province->changeUnitName(participant.getNewName());
				participant.addProvince(province);
				participant.setCapital(province);
			}
			else
			{
				goto start;
			}
	}
	
}

void Database::createMap() {
	//For debugging
	OF::debugFunction("Database, createMap");

	Participants* tempParticipant = new Participants;
	tempParticipant->createMapParticipant();
	delete tempParticipant;
}