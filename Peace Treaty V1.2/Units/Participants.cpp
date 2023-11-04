#include "Participants.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;


ARRAY Participants::allCommandersArray = {};
ARRAY Participants::allProvincesArray = {};


	// Constructor
//Constructor
Participants::Participants() {
	playerStatus = false;
	capitalIndex = 0;
	participantIndex = 0;
	capitalProvince = new Provinces;

	//Default
	selectedCommander = NULL;


	//Defaults
	commandersMap = std::unordered_map<std::string, CommanderProfile*>();
	provincesMap = std::unordered_map<std::string, Provinces*>();
	it = std::unordered_map<std::string, CommanderProfile*>::iterator();

	provincesVector = std::vector<Provinces*>();
	commandersVector = std::vector<CommanderProfile>();
}

Participants::Participants(int pIndex) {
	std::cout << "Add commander\n";
	addCommander();
	std::cout << "Initial cap rss";
	initialCapRSS();
	std::cout << "Set kingdom name\n";
	setKingdomName("-1");
	participantIndex = pIndex;

	//Defaults
	commandersMap = std::unordered_map<std::string, CommanderProfile*>();
	provincesMap = std::unordered_map<std::string, Provinces*>();
	it = std::unordered_map<std::string, CommanderProfile*>::iterator();

	provincesVector = std::vector<Provinces*>();
	commandersVector = std::vector<CommanderProfile>();
}

// Accessors
Provinces* Participants::getCapitalProvince() { return capitalProvince; }

Provinces* Participants::findProvince(std::pair<int, int> userCoords) {
	for (Provinces* province : provincesVector) {
		if (province->getUserCoords() == userCoords) {
			return province;
		}
	}

	std::cout << "Error occurred, error path...\n";
	return NULL;
}

int Participants::provincesNum() { return (int) provincesVector.size(); }
int Participants::commandersNum() { return (int) commandersVector.size(); }


void Participants::initialCapRSS() {
	//Add functionality so, depending on the difficulty, AI participants get more or less resources to start off with
	Provinces* newProvince = getCapitalProvince();
	newProvince->modifyResources(CV::INITIAL_VALUES, true);
}

// Mutators
void Participants::setCapital(Provinces* newProvince) {
	capitalProvince = newProvince;
}

void Participants::addProvince(Provinces* newProvince) {
	provincesVector.push_back(newProvince);
	provincesMap[newProvince->getUnitName()] = provincesVector[provincesVector.size() - 1];
}

void Participants::addCommander() {
	CommanderProfile newCommander(1, getNewName());
	std::pair<int, int> systemCoords = getCapitalProvince()->getSystemCoords();
	std::pair<int, int> userCoords = getCapitalProvince()->getUserCoords();

	newCommander.changeParticipantIndex(participantIndex);
	newCommander.setCoords(systemCoords, userCoords);

	commandersVector.push_back(newCommander);
	CommanderProfile* commanderPtr = &commandersVector[commandersVector.size() - 1];
	commandersMap[newCommander.getUnitName()] = commanderPtr;

	getCapitalProvince()->addCommander(commanderPtr);
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

void Participants::createAsPlayer(bool status)
{
	std::cout << "This is a human player...\n";
	playerStatus = status;
	//If player
	if (status == true)
	{
		std::string name;
		std::cout << "Enter a name for this participant: " << RED;
		getline(std::cin, name);
		this->setKingdomName(name);
		this->setPlayerStatus(true);
		std::cout << WHITE << "Participant " << RED << kingdomName << WHITE << " created... \n\n";
		return;
	}
	std::cout << "Player created \n";
	std::cout << "AI created \n";
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

	if (Input::getInputText("View all stats? (Y/N) ", { "Y", "N" }).at(0) == 'Y')
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

Provinces* Participants::getProvince(int index) { return provincesVector[index]; }

std::string Participants::getNewName() {
	std::string newName = OF::createRandomName();
	for (Provinces* newProvince : provincesVector)
		if (newName == newProvince->getUnitName())
			getNewName();


	for (it = commandersMap.begin(); it != commandersMap.end(); it++)
		if (newName == it->second->getUnitName())
			getNewName();

	return newName;
}

// CommanderProfile *Participants::getCommander(int index) {
//   std::unordered_map<std::string, CommanderProfile*>::iterator it;
//   for (it = commandersMap.begin(); it != commandersMap.end(); it++)
//     if ()
// }

std::array<int, 5> Participants::getTrainCosts() { return trainCosts; }

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
	OF::enterAnything();
}

void Participants::printListOfProvinces() {
	std::cout << "Here is a list of your provinces (Name, Coordinates): \n";
	for (Provinces* province : provincesVector)
	{
		std::cout << "- " << province->getUnitName() << ": ";
		province->getUserCoords();
		std::cout << "\n";
	}
}

//Shows the list of provinces, prompts user to select a province, checks if the province belongs to the participant. If it does, return that province. If it doesn't, call method again
Provinces* Participants::getYourProvince(int identifier) {
	OF::debugFunction("Participants, getYourProvince-- revise to make it an array??");
	Provinces* newProvince = getCoords(identifier);
	if (newProvince->getParticipantIndex() == participantIndex)
	{
		std::cout << "This is one of your provinces...\n" + newProvince->getUserCoordsString() + "\n";
		return newProvince;
	}

	std::cout << "This province does not belong to you. Please try again \n";
	OF::clearScreen();
	getYourProvince(identifier);

	std::cout << "Invalid path... \n";
	return NULL;
}



int Participants::getRandomCoordinate() { return rand() % CV::continentSize; }

bool Participants::hasCommander(std::string name) {
	if (commandersMap.find(name) == commandersMap.end())
		return false;
	return true;
}

CommanderProfile* Participants::getCommander(std::string name) {
	return commandersMap[name];
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
	for (it = commandersMap.begin(); it != commandersMap.end(); it++)
	{
		CommanderProfile* newCommander = it->second;
		switch (option)
		{
		case 1://Calculate each Unit
			returnArray = OF::modifyArray(returnArray, newCommander->getTroop(REGULAR, NULL, ALL), true);
			break;
		case 2://Calculate each resource
			returnArray = OF::modifyArray(returnArray, newCommander->getAllResources(), true);
			break;
		case 3://calculate each troop lost
			returnArray = OF::modifyArray(returnArray, newCommander->getTroop(LOST, NULL, ALL), true);
			break;
		default:
			break;
			//do nothing
		}
		delete newCommander;
	}

	for (Provinces* newProvince : provincesVector)
	{
		switch (option)
		{
		case 1://Calculate each Unit
			returnArray = OF::modifyArray(returnArray, newProvince->getTroop(REGULAR, NULL, ALL), true);
			break;
		case 2://Calculate each resource
			returnArray = OF::modifyArray(returnArray, newProvince->getAllResources(), true);
			break;
		case 3://calculate each troop lost
			returnArray = OF::modifyArray(returnArray, newProvince->getTroop(LOST, NULL, ALL), true);
			break;
		default:
			break;
		}
	}
	return returnArray;
}


void Participants::showMapOld() {
	std::cout << "Map: \n";

	int foo = CV::continentSize;
	for (int x = 0; x < CV::continentSize; x++) {
		// Y axis stuff
		if (foo < 10)
			std::cout << " " << foo << "| ";
		else
			std::cout << foo << "| ";

		foo--;
		// End y axis stuff

		for (int y = 0; y < CV::continentSize; y++) {
			char letter = ' '; // Fix this later
			Provinces* mapProvince = getSystemProvince({x,y});

			if (mapProvince->getParticipantIndex() == participantIndex){
				std::cout << BLUE;
				if (mapProvince->isCapital() == true) {
					letter = 'C';
				}
				else {
					letter = 'p';
				}
					
			}
			else if (mapProvince->getParticipantIndex() != -1)
			{
				std::cout << RED;
				if (getSystemProvince({x, y})->isCapital() == true)
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
	for (int a = 0; a < CV::continentSize - 1; a++) {
		std::cout << "----";
	}
	std::cout << "--";
	std::cout << std::endl;
	std::cout << "    ";
	for (int a = 0; a < CV::continentSize; a++) {
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
	return provincesMap[name];
}

/*Provinces* Participants::selectRandomProvince()
{
	//place holder
	Provinces newProvince;
	return &newProvince;
}*/

bool Participants::hasProvince(std::string name)
{
	if (provincesMap.find(name) != provincesMap.end()) {
		return true;
	}

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

Provinces* Participants::getCoords(int identifier) {
	std::vector<std::string> actualCoordinatesAVTwo = { "-1" };
	//range of possible coordinates
	for (int x = 1; x <= CV::continentSize; x++)
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

	int xCoordinate = std::stoi(getInputText("Enter the x coordinate " + phrase + " (Enter '-1' to go back to previous menu): ", actualCoordinatesAVTwo));
	// Critical: check to make sure the coordinate checkings are correct
	int yCoordinate = std::stoi(getInputText("Enter the y coordinate " + phrase + " (Enter '-1' to go back to previous menu): ", actualCoordinatesAVTwo));


	if (xCoordinate != -1 && yCoordinate != -1) {
		return getUserProvince({ xCoordinate, yCoordinate });
	}

	return NULL;
}



Provinces* Participants::findProvince() {
	OF::debugFunction("Participants, findProvince--revise");
	std::cout << "Welcome to the Player Build menu\n\n";
	Provinces* province = this->getCoords(1);

	//Make sure the user wants to do this action. A -1 value means that 
	if (province->getSystemCoords().first != NULL) {
		//If this province belongs to the current participant
		int participantIndex = this->getParticipantIndex();
		if (province->getParticipantIndex() == participantIndex) {
			return province;
			//What does this do???
			province->playerBuildFunction();
		}
		else {//If does not belong to the current participant
			print("Invalid province elected. Please try again. \nEnter anything to "
				"proceed back to the Player Build menu (Screen will clear) ");
			OF::enterAnything();
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Returning to player action menu...\n";
	}

	std::cout << "Error path...\n";
	return NULL;
}

CommanderProfile* Participants::getSelectedCommander() {
	return selectedCommander;
}

bool Participants::hasUnit(std::string unitName) {
	if (hasCommander(unitName)) {
		return true;
	}
	else if (hasProvince(unitName)) {
		return true;
	}
	return false;
}

Provinces* Participants::getSystemProvince(std::pair<int, int> systemCoords) {
	return Map::getSystemProvince(systemCoords);
}

void Participants::showMap() {
	Map::showMap();
}

ARRAY Participants::getAllUnitsArray() {;
	ARRAY returnArray = {0,0,0,0,0};

	Participants* p = new Participants();
	try {
		std::thread th1 = p->th1Method();
		std::thread th2 = p->th2Method();
		th1.join();
		th2.join();
	}
	catch (...) {
		getAllUnitsArrayCommanders();
		getAllUnitsArrayProvinces();
	}
	

	returnArray = modifyArray(returnArray, allCommandersArray, true);
	returnArray = modifyArray(returnArray, allProvincesArray, true);
	return returnArray;
}

VOID Participants::getAllUnitsArrayCommanders() {
	for (CommanderProfile instance : commandersVector) {
		ARRAY commanderArray = instance.getTroop(REGULAR, -1, ALL);
		OF::modifyArray(allCommandersArray, commanderArray, true);
	}
}

VOID Participants::getAllUnitsArrayProvinces() {
	for (Provinces *instance : provincesVector) {
		ARRAY provincesArray = instance->getTroop(REGULAR, -1, ALL);
		OF::modifyArray(allProvincesArray, provincesArray, true);
	}
}

INTEGER Participants::getAllUnitsAmount() {
	int amount = 0;
	for (int x : getAllUnitsArray()) {
		amount += x;
	}

	return amount;
}

std::thread Participants::th1Method() {
	return std::thread([=] {getAllUnitsArrayProvinces(); });
}

std::thread Participants::th2Method() {
	return std::thread([=] {getAllUnitsArrayCommanders(); });
}

void Participants::updateTurnResourcesParticipant() {
	this->updateTurnResources();
}

void Participants::createMapParticipant() {
	setMap();
}