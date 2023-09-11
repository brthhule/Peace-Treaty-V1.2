#include "Participants.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
#define RED "\033[31m"
#define WHITE "\033[0m"
#define BLUE "\033[;34m"

// Constructor
Participants::Participants(int pIndex) {
	std::cout << "Create Capital\n";
	createCapital();
	std::cout << "Add commander\n";
	addCommander();
	std::cout << "Initial cap rss";
	initialCapRSS();
	std::cout << "Set kingdom name\n";
	setKingdomName("-1");
	participantIndex = pIndex;

	for (int x = 0; x < continentSize; x++)
	{
		std::vector<Provinces> provincesVector;
		for (int y = 0; y < continentSize; y++)
		{
			Provinces newProvince;
			provincesVector.push_back(newProvince);
		}
		scoutMap.push_back(provincesVector);
	}
}
void Participants::createCapital() {
	/*For each participant, generate random x and y values, see if the province
	 * associated with these values (coordinates) is empty. If it's empty, change
	 * the province identifier and add it to a partipant's list of provinces. If
	 * it's not empty, repeatMap is 'Y' and the process repeats*/

	 // int xCoord = getRandomCoordinate();
	 // int yCoord = getRandomCoordinate();
	 // Provinces *newProvince = &provincesMap[xCoord][yCoord];
	 // if (newProvince->getParticipantIndex() == -1) {
	 //   newProvince->changeParticipantIndex(participantIndex);
	 //   newProvince->initializeCapital();
		   // newProvince->changeUnitName(getNewName());
	 //   addProvince(newProvince);
	 //   setCapital(newProvince);

	 // } else {
	 //   createCapital();
	 // }

	   //ParticipantsList Alternative
	int num = rand() % provincesLL.getProvincesNum();
	std::cout << "Num: " << num << std::endl;
	Provinces* newProvince = provincesLL.getProvinceByNum(num);
	std::cout << "New province participant index: " << newProvince->getParticipantIndex() << std::endl;
	if (newProvince->getParticipantIndex() == -1)
	{
		newProvince->changeParticipantIndex(participantIndex);
		newProvince->initializeCapital();
		newProvince->changeUnitName(getNewName());
		addProvince(newProvince);
		setCapital(newProvince);
	}
	else
	{
		createCapital();
	}
}

// Accessors
Provinces* Participants::getCapital() { return provincesList[capitalIndex]; }
Provinces* Participants::findProvince(int x, int y) {
	for (int a = 0; a < (int)provincesList.size(); a++) {
		Provinces* newProvince = provincesList[a];
		if (x == newProvince->getCoordinate(0) &&
			y == newProvince->getCoordinate(1))
			return newProvince;
	}

	std::cout << "Error occurred, error path...\n";
	Provinces newProvince;
	return &newProvince;
}

int Participants::provincesNum() { return provincesList.size(); }
int Participants::commandersNum() { return commandersList.size(); }


void Participants::initialCapRSS() {
	//Add functionality so, depending on the difficulty, AI participants get more or less resources to start off with
	Provinces* newProvince = getCapital();
	newProvince->modifyResources(CV::INITIAL_VALUES, true);
}

// Mutators
void Participants::setCapital(Provinces* newProvince) {
	for (int x = 0; x < (int)provincesList.size(); x++) {
		if (provincesList[x] == newProvince) {
			capitalIndex = x;
			x = provincesList.size();
		}
	}
}

void Participants::addProvince(Provinces* newProvince) {
	provincesList.push_back(newProvince);
}

void Participants::addCommander() {
	CommanderProfile newCommander(1, getNewName());
	std::array<int, 2> newCoordinates = getCapital()->getCoordinates();
	newCommander.changeParticipantIndex(participantIndex);
	newCommander.setLocation(newCoordinates);
	commandersList.insert({ newCommander.getUnitName(), &newCommander });
	getCapital()->addCommander(&newCommander);
}

void Participants::setKingdomName(std::string newName) {
	if (newName == "-1")
		newName = getNewName();
	kingdomName = newName;
}

std::string Participants::getKingdomName() { return kingdomName; }

bool Participants::isAlive() {
	if (provincesNum() > 0 && commandersNum() > 0)
		return true;

	return false;
}

void Participants::createAsPlayer(bool choice)
{
	playerStatus = choice;
	//If player
	if (choice == true)
	{
		std::cout << "Enter a name for this participant: " << RED;
		getline(std::cin, kingdomName);
		std::cout << WHITE << "Participant " << RED << kingdomName << WHITE << " created... \n\n";
	}

}

void Participants::viewStats() {
	std::array<int, 5> eachUnit = calculateEach(1);
	std::array<int, 5> totalResources = calculateEach(2);

	std::cout << "Kingdom name: " << kingdomName << "\n\n";

	for (int x = 0; x < 5; x++) {
		std::cout << "Total " << CV::RESOURCE_NAMES[x] << ": " << totalResources[x] << std::endl;
	}

	for (int x = 0; x < 5; x++)
		std::cout << "Total " << CV::TROOP_NAMES[x] << " alive: " << eachUnit[x] << std::endl;

	std::cout << "Your total army combat power: " << calculatePlayerValues(1).at(0);
	std::cout << "\nYour numnber of provinces: " << provincesNum() << "\n\n";

	if (OF.getInput(false, -1, "View all stats? (Y/N) ", { "Y", "N" }, false, false).at(0) == 'Y')
		viewAllStatsFunction();

	std::cout << "Returning to menu" << std::endl;
}

std::vector<int> Participants::calculatePlayerValues(int decision) {
	std::array<int, 5> newArray = calculateEach(decision);
	switch (decision) {
	case 1: { // Return total CP
		int totalCPThingy = 0;
		for (int x = 0; x < 5; x++)
			totalCPThingy += newArray[x] * CV::TROOPS_CP[x];
		return { totalCPThingy };
	}
	case 2: {
		std::vector<int> newArray;
		for (int x : troopsLost)
			newArray.push_back(x);
		return newArray;
	}
	}

	std::cout << "Error case; shouldn't happen\n";
	std::vector<int> emptyVector;
	return emptyVector;
}

Provinces* Participants::getProvince(int index) { return provincesList[index]; }

std::string Participants::getNewName() {
	std::string newName = OF.createRandomName();
	for (Provinces* newProvince : provincesList)
		if (newName == newProvince->getUnitName())
			getNewName();


	for (it = commandersList.begin(); it != commandersList.end(); it++)
		if (newName == it->second->getUnitName())
			getNewName();

	return newName;
}

// CommanderProfile *Participants::getCommander(int index) {
//   std::unordered_map<std::string, CommanderProfile*>::iterator it;
//   for (it = commandersList.begin(); it != commandersList.end(); it++)
//     if ()
// }

std::array<int, 5> Participants::getTrainCosts() { return trainCosts; }

int Participants::getMaxCommanders() { return maxCommanders; }

void Participants::setParticipantIndex(int num) { participantIndex = num; }

int Participants::getParticipantIndex() { return participantIndex; }

void Participants::viewAllStatsFunction() {
	std::string literallyAnyRandomCharacter;
	std::cout << BLUE; // NW
	std::array<int, 5> troopsLost = calculateEach(3);
	for (int x = 0; x < 5; x++) {
		std::cout << CV::TROOP_NAMES[x] << " lost: "
			<< troopsLost[x]
			<< std::endl;
	}
	std::cout << "Total troops lost: ";
	calculatePlayerValues(2);
	std::cout << "\n\n\033[;0m"; // NW
	OF.enterAnything();
}

void Participants::printListOfProvinces() {
	std::cout << "Here is a list of your provinces (Name, Coordinates): \n";
	for (Provinces* tempProvince : provincesList)
	{
		std::cout << "Capital Coords (Output): " + getCapital()->printOutputCoordinates() + "\n";
		std::cout << "Capital Coords (input): " + getCapital()->printCoordinates() + "\n";
		std::cout << "XCoord: " << tempProvince->getCoordinate('X') << std::endl;
		std::cout << "YCoord: " << tempProvince->getCoordinate('Y') << std::endl;
		std::cout << "- " << tempProvince->getUnitName() << " " + tempProvince->printOutputCoordinates() + "\n";
	}
}

Provinces* Participants::getYourProvince(int identifier) {
	OF.debugFunction("Participants, getYourProvince-- revise to make it an array??");
	Provinces* newProvince = getCoords(identifier);
	if (newProvince->getParticipantIndex() == participantIndex)
	{
		std::cout << "This is one of your provinces...\n";
		std::cout << newProvince->printCoordinates() << std::endl;
		return newProvince;
	}

	std::cout << "This province does not belong to you. Please try again \n";
	OF.clearScreen();
	getYourProvince(identifier);

	std::cout << "Invalid path... \n";
	Provinces emptyProvince;
	return &emptyProvince;
}
Provinces* Participants::getCoords(int identifier) {
	std::vector<std::string> actualCoordinatesAVTwo = { "-1" };
	//range of possible coordinates
	for (int x = 1; x <= continentSize; x++)
		actualCoordinatesAVTwo.push_back(std::to_string(x));

	showMap();
	std::string phrase;
	switch (identifier) {
	case 1:
		printListOfProvinces();
		phrase = "of the province you want to select";
		break;
	case 2:
		printListOfProvinces();
		phrase = "of the province you want to move to";
		break;
	case 3:
		phrase = "of the army you want to use to attack the target with";
	}

	int xCoordinate = std::stoi(OF.getInput(false, -1, "Enter the x coordinate " + phrase + " (Enter '-1' to go back to previous menu): ", actualCoordinatesAVTwo, false, false));
	// Critical: check to make sure the coordinate checkings are correct
	int yCoordinate = std::stoi(OF.getInput(false, -1, "Enter the y coordinate " + phrase + " (Enter '-1' to go back to previous menu): ", actualCoordinatesAVTwo, false, false));

	std::cout << "X Coordinate: " << xCoordinate << std::endl;
	std::cout << "Y Coordinate: " << yCoordinate << std::endl;
	if (xCoordinate != -1 && yCoordinate != -1)
	{
		int replacement = xCoordinate;
		xCoordinate = OF.translateCoordinate(yCoordinate, 'y', 'I');
		yCoordinate = OF.translateCoordinate(replacement, 'x', 'I');
		std::cout << "Translated x: " << xCoordinate << std::endl;
		std::cout << "Translated y: " << yCoordinate << std::endl;
		OF.enterAnything();
		Provinces* newProvince = &provincesMap[xCoordinate][yCoordinate];
		return newProvince;
	}

	if (xCoordinate == -1 || yCoordinate == -1) {
		std::cout << "XCoord: " << xCoordinate << std::endl;
		std::cout << "YCoord: " << yCoordinate << std::endl;
		Provinces* newProvince = &provincesMap[xCoordinate][yCoordinate];
		newProvince->setDeleteProvince();
		return newProvince;
	}
	
	//Empty path
	std::cout << "Error path...";
	Provinces newProvince;
	return &newProvince;
}

int Participants::getRandomCoordinate() { return rand() % continentSize; }

bool Participants::hasCommander(std::string name) {
	if (commandersList.find(name) == commandersList.end())
		return false;
	return true;
}

CommanderProfile* Participants::getCommanderByName(std::string name) {
	return commandersList[name];
}
int Participants::calculateTotals(int option)
{
	int sum = 0;
	std::array <int, 5> totals = calculateEach(option);
	for (int x : totals)
		sum += x;

	return sum;
}

std::array<int, 5> Participants::calculateEach(int option)
{
	std::array<int, 5> returnArray = { 0, 0, 0, 0, 0 };
	//Go through all commanders at this province
	for (it = commandersList.begin(); it != commandersList.end(); it++)
	{
		CommanderProfile* newCommander = it->second;
		switch (option)
		{
		case 1://Calculate each Unit
			returnArray = OF.modifyArray(returnArray, newCommander->getAllTroopsPresent(), true);
			break;
		case 2://Calculate each resource
			returnArray = OF.modifyArray(returnArray, newCommander->getAllResources(), true);
			break;
		case 3://calculate each troop lost
			returnArray = OF.modifyArray(returnArray, newCommander->getAllTroopsLost(), true);
			break;
		default:
			break;
			//do nothing
		}
		delete newCommander;
	}

	for (Provinces* newProvince : provincesList)
	{
		switch (option)
		{
		case 1://Calculate each Unit
			returnArray = OF.modifyArray(returnArray, newProvince->getAllTroopsPresent(), true);
			break;
		case 2://Calculate each resource
			returnArray = OF.modifyArray(returnArray, newProvince->getAllResources(), true);
			break;
		case 3://calculate each troop lost
			returnArray = OF.modifyArray(returnArray, newProvince->getAllTroopsLost(), true);
			break;
		default:
			break;
		}
	}
	return returnArray;
}


void Participants::showMapOld() {
	std::cout << "Map: \n";

	int thingy = continentSize;
	for (int x = 0; x < continentSize; x++) {
		// Y axis stuff
		if (thingy < 10)
			std::cout << " " << thingy << "| ";
		else
			std::cout << thingy << "| ";

		thingy--;
		// End y axis stuff

		for (int y = 0; y < continentSize; y++) {
			char letter = ' '; // Fix this later
			Provinces* mapProvince = &provincesMap[x][y];

			if (mapProvince->getParticipantIndex() == participantIndex)
			{
				std::cout << BLUE;
				if (mapProvince->isCapital() == true)
					letter = 'C';
				else
					letter = 'p';
			}
			else if (mapProvince->getParticipantIndex() != -1)
			{
				std::cout << RED;
				if (provincesMap[x][y].isCapital() == true)
					letter = 'C';
				else
					letter = 'p';
			}
			else {
				letter = '0';
			}

			std::cout << letter << mapProvince->commandersNum() << "  " << WHITE;
		}
		std::cout << std::endl;
	}

	// X axis stuff
	std::cout << "    ";
	for (int a = 0; a < continentSize - 1; a++) {
		std::cout << "----";
	}
	std::cout << "--";
	std::cout << std::endl;
	std::cout << "    ";
	for (int a = 0; a < continentSize; a++) {
		if (a < 9)
			std::cout << a + 1 << "   ";
		else
			std::cout << a + 1 << "  ";
	}
	std::cout << "\n\n";
}

void Participants::scoutProvince(Provinces* targetProvince, int accuracy) /*Add implementation later*/
{

}

bool Participants::subtractCheckResources(std::string provinceName, std::array<int, 5> resourcesArray)
{
	Provinces* newProvince = getProvinceByName(provinceName);
	//returns false if resources dip into negatives
	newProvince->modifyResources(resourcesArray, false);
	for (int x : newProvince->getAllResources())
		if (x < 0)
			return false;
	return true;
}

Provinces* Participants::getProvinceByName(std::string name)
{
	for (Provinces* newProvince : provincesList)
		if (newProvince->getUnitName() == name)
			return newProvince;
	return NULL;
}

/*Provinces* Participants::selectRandomProvince()
{
	//place holder
	Provinces newProvince;
	return &newProvince;
}*/

bool Participants::hasProvince(std::string name)
{
	for (Provinces* newProvince : provincesList)
		if (newProvince->getUnitName() == name)
			return true;
	return false;
}

std::string Participants::selectCommander() {
	displayCommanders();
	std::string commanderName = " ";
	println("Enter the name of the commander you wish to select (Enter -1 to cancel selection): ");
	getline(std::cin, commanderName);

	if (hasCommander(commanderName) == false && commanderName != "-1") {
		println("Invalid character entered. Please try again... (Enter any character to continue)");
		selectCommander();
	}

	if (commanderName == "-1")
	{
		std::cout << "Cancelling selection\n";
	}
	else
		std::cout << "Commander " << commanderName << " selected...\n";

	return commanderName;
}
void Participants::displayCommanders()
{
	std::cout << "Here is list of your commanders: \n";
	std::unordered_map<std::string, CommanderProfile*> commandersMap = getCommandersMap();
	std::unordered_map<std::string, CommanderProfile*>::iterator it;
	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		CommanderProfile* tempCommander = it->second;
		std::cout << "- Commander " << tempCommander->getUnitName() << "; Level: " << tempCommander->getLevel() << std::endl;
		delete tempCommander;
	}
}

void Participants::showMapCoordinates()
{
	std::cout << "Input: \n";
	for (int x = 0; x < (int)provincesMap.size(); x++)
	{
		for (int y = 0; y < (int)provincesMap[x].size(); y++)
		{
			std::cout << provincesMap[x][y].printCoordinates() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Output: \n";
	for (int x = 0; x < (int)provincesMap.size(); x++)
	{
		for (int y = 0; y < (int)provincesMap[x].size(); y++)
		{
			std::cout << provincesMap[x][y].printOutputCoordinates() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Participants::showMap()
{
	int LLNumber = 1;
	std::cout << "Map: \n";

	int thingy = continentSize;
	for (int x = 0; x < continentSize; x++) {
		// Y axis stuff
		if (thingy < 10)
			std::cout << " " << thingy << "| ";
		else
			std::cout << thingy << "| ";

		thingy--;
		// End y axis stuff

		for (int y = 0; y < continentSize; y++) {
			char letter = ' '; // Fix this later
			Provinces* showMapProvince = provincesHH[LLNumber];
			LLNumber++;

			if (showMapProvince->getParticipantIndex() == participantIndex)
			{
				std::cout << BLUE;
				if (showMapProvince->isCapital() == true)
					letter = 'C';
				else
					letter = 'p';
			}
			else if (showMapProvince->getParticipantIndex() != -1)
			{
				std::cout << RED;
				if (provincesMap[x][y].isCapital() == true)
					letter = 'C';
				else
					letter = 'p';
			}
			else {
				letter = '0';
			}

			std::cout << letter << showMapProvince->commandersNum();
			//std::cout << "  ";
			std::cout << LLNumber - 1 << " ";
			std::cout << WHITE;
		}
		std::cout << std::endl;
	}

	// X axis stuff
	std::cout << "    ";
	for (int a = 0; a < continentSize - 1; a++) {
		std::cout << "----";
	}
	std::cout << "--";
	std::cout << std::endl;
	std::cout << "    ";
	for (int a = 0; a < continentSize; a++) {
		if (a < 9)
			std::cout << a + 1 << "   ";
		else
			std::cout << a + 1 << "  ";
	}
	std::cout << "\n\n";
}