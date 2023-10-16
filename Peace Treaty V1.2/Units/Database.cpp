#include "Database.h"

Database::Database() {
	//provincesUM = provincesLL.createMap();
}

void Database::createMap() {
	OF::debugFunction("main, createMap--review");
	/*Basically create the map-- make each province an object of Provinces*/
	// int a = 1;
	// for (int x = 0; x < continentSize; x++) 
	// {
	 //    std::vector<Provinces> vectorThingy;
	 //    provincesMap.push_back(vectorThingy);
	 //    for (int y = 0; y < continentSize; y++) {
	// 	Provinces newProvince(x-1, y, -1);
	// 	newProvince.assignLinkedListNumber(a);
	// 	a++;
	// 	std::cout << ""
	// 	provincesLL.addNode(newProvince);
	// 	provincesHH[a] = &newProvince;
	// 	provincesMap[x].push_back(newProvince);
	 //    }
	 //  }
	try {
		//Need to change this to unordered map
		std::vector<Provinces>* allProvinces = provincesLL.createMap(continentSize);
		for (int x = 0; x < (int)allProvinces->size(); x++)
		{
			//Evaluate if this is what I want to do
			std::pair<int, Provinces*> thang = { x, &allProvinces->at(x) };
			//Fix this later
			//provincesHH[x] = thang;
		}

		provincesLL.listProvinces();
	}
	catch (...) {
		std::cout << "Error occurred...";
	}
			
	
}

void Database::initializeParticipants(int totalPlayers, int humanPlayers) {
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

}

std::vector <Participants> *Database::getParticipantsList() {
	return &participantsList;
}

void Database::updateTurnResources() {
	OF::debugFunction("main, updateTurnResources");
	for (int x = 0; x < continentSize; x++) {
		for (int y = 0; y < continentSize; y++) {
			map[x][y].updateBuildingsProduction();
			map[x][y].updateProvinceResources();
		}
	}

	//LL Alternative:
	provincesLL.LLupdateprovinceResources();
}

void Database::setContinentSize(int num) {
	continentSize = num;
}
int Database::getContinentSize() {
	return continentSize;
}
void Database::setMaxCommanders(int num) {
	maxCommanders = num;
}
int Database::getMaxCommanders() {
	return maxCommanders;
}

void Database::setCurrentParticipant(Participants* p) {
	currentParticipant = p;
}

Participants *Database::getCurrentParticipant() {
	return currentParticipant;
}

bool Participants::isPlayer() {
	return playerStatus;
}

void Participants::setPlayerStatus(bool status) {
	playerStatus = status;
}

Participants *Database::getParticipant(int index) {
	return &participantsList[index];
}


void Database::Mobility::moveUnitOne(CommanderProfile* commander) {
	//This will have the list of provinces that can be moved to
	std::vector<Provinces*> provincesCanSelect;

	//If this commander has not moved yet
	if (commander->hasMovedQuestion() == false) {
		//Get their system coords
		std::pair<int, int> newCoordinates = commander->getSystemCoords();

		std::cout << "The coordinates of the chosen unit unit are: ";
		commander->printUserCoords();
		println("\n\nYou can only move this unit to one of the provinces adjacent to the province it is in");

		//Get list of provinces that can be moved to
		provincesCanSelect = moveUnitTwo();

		// The participant slects coordiantes
		std::pair<int, int> userCoords = pickCoords();

		int provinceIndexSelected = 0;
		char provinceIsInList = 'N';

		for (Provinces *province:provincesCanSelect) {
			if (userCoords == province->getUserCoords()) {
				provinceIndexSelected = x;
				provinceIsInList =
					'Y';
			}
		}

		// For display
		std::pair<int, int> systemCoords = getProvince()
			int moveToX = moveTwo->translateX(false);
		int moveToY = moveTwo->translateY(false);

		std::string confirmMove;
		char attackScenario = 'P'; /*P is for peace, A is for attack*/
		// If province is in the list
		if (provinceIsInList == 'Y') {
			Provinces* attackProvince = provincesCanSelect[provinceIndexSelected];

			if (attackProvince->getParticipantIndex() !=
				participant->getParticipantIndex()) {
				attackScenario = 'A';
				println("Moving here will cause your unit to attack any enemy units stationed at this province.");
			}
			std::cout << "Confirm moving your unit to (" << moveToX << ", " << moveToY
				<< ")? (Y/N) ";

			// If participants confirms movement
			if (Input::getInputText("Confirm Y/N: ", { "Y", "N" }).at(0) == 'Y') {
				// If it's peaceful (moving to one of their own provinces)
				if (attackScenario == 'P') {
					std::array<int, 2> coordinates = moveTwo->getCoordinates();
					selectedCommander->setLocation(coordinates);
					attackProvince->addCommander(selectedCommander);
				}
				// If scenario is attack
				else
					AttackMA newAttackMA(selectedCommanderProvince, attackProvince, participant, selectedCommander);
			}
		}
		else {
			std::cout << "Invalid province selected... please try again. " << std::endl;
			// Recursion until suitable coordinates are chosen
			moveUnitOne();
		}
	}
	else {
		std::cout
			<< "This unit has already moved this turn. Please pick another unit. "
			<< std::endl;
	}
	std::cout << "Returning to previous menu... " << std::endl << std::endl;
} /* unfinished*/


std::vector<Provinces*> Database::Mobility::moveUnitTwo(CommanderProfile* commander) {
	std::vector<Provinces*> vectorThingy;
	for (int x = -1; x <= 1;
		x++) /*Identify all the provinces that the player can move a unit to*/
	{
		for (int y = -1; y <= 1; y++) {
			// Check to see if the coordinates are in bounds (not outside of the map
			// size)
			if (/*X coordinate stuff*/ x >= 0 && x < CV::continentSize &&
				/*Y coordinate stuff*/ y >= 0 && y < CV::continentSize) {
				// Make sure province isn't the starting province
				if (x != 0 || y != 0) {
					// Add province to list of provinces can move to
					vectorThingy.push_back(
						db.getProvince(selectedCommanderProvince->getSystemCoords()));
				}
			}
		}
	}
	return vectorThingy;
}

std::pair<int, int> Database::pickCoords() {
	showMap();
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

	if (xCoordinate > 0 && xCoordinate <= CV::continentSize && yCoordinate > 0 && yCoordinate <= continentSize) {
		return { xCoordinate, yCoordinate };
	}

	CV::addColor(RED);
	std::cout << "Inputed coordinates are out of bounds... please try again.";
	CV::addColor(RESET);
	pickCoords();
}