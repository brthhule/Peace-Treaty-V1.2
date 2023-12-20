#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER 

using namespace COMM;
using namespace PART;
using namespace PROV;

i5array trainCosts = { 5, 4, 3, 2, 1 }; 

std::vector<partSPTR> Participants::playersList = {};  
std::vector<partSPTR> Participants::botsList = {};  
std::vector<partSPTR> Participants::participantsList = {};

Participants::Participants() {
	//For debugging
	DEBUG_FUNCTION("Participants, Participants (0 Param)");

	Participants(0);

	capitalProvince = nullptr;
}

Participants::Participants(int pIndex) {
	//For debugging
	DEBUG_FUNCTION("Participants, Participants (1 Param)");
	addCommander();
	initialCapRSS();
	setKingdomName("-1");
	participantIndex = pIndex;

	capitalIndex = 0;

	//Defaults
	commandersMap = std::unordered_map<std::string, commSPTR>();
	provincesMap = std::unordered_map<std::string, provSPTR>();
	commIt = std::unordered_map<std::string, commSPTR>::iterator();

	provincesVector = std::vector<provSPTR>();
	commandersVector = std::vector<Commanders>();
}

// Accessors
provSPTR Participants::getCapitalProvince() { 
	//For debugging
	DEBUG_FUNCTION("Participants, getCapitalProvince");
	
	return capitalProvince; 
}

int Participants::getProvincesNum() { 
	//For debugging
	DEBUG_FUNCTION("Participants, getProvincesNum");

	return (int) provincesVector.size(); 
}

int Participants::getCommandersNum() { 
	//For debugging
	DEBUG_FUNCTION("Participants, getCommandersNum");
	
	return (int) commandersVector.size();
}


void Participants::initialCapRSS() {
	//For debugging
	DEBUG_FUNCTION("Participants, initialCaRSS");

	//Add functionality so, depending on the difficulty, AI participants get more or less resources to start off with
	provSPTR newProvince = getCapitalProvince();
	newProvince->modifyResources(INF::INITIAL_VALUES, true);
}

// Mutators
void Participants::setCapital(provSPTR newProvince) {
	//For debugging
	DEBUG_FUNCTION("Participants, setCapital");

	capitalProvince = newProvince;
}

void Participants::addProvince(provSPTR newProvince) {
	//For debugging
	DEBUG_FUNCTION("Participants, addProvince");

	provincesVector.push_back(newProvince);
	provincesMap[newProvince->getName()] = provincesVector[provincesVector.size() - 1];
}




void Participants::setKingdomName(std::string newName) {
	//For debugging
	DEBUG_FUNCTION("Participants, setKingdomName");

	if (newName == "-1") {
		newName = getNewName();
	}
		
	kingdomName = newName;
}

std::string Participants::getKingdomName() { return kingdomName; }

bool Participants::isAlive() {
	//For debugging
	DEBUG_FUNCTION("Participants, isAlive");

	if (getProvincesNum() > 0 || getCommandersNum() > 0) {
		return true;
	}

	return false;
}

void Participants::createAsPlayer(bool status)
{
	//For debugging
	DEBUG_FUNCTION("Participants, createAsPlayer");

	std::cout << "This is a human player...\n";
	//If player
	if (status == true)
	{
		std::string name;
		std::cout << "Enter a name for this participant: " << RED;
		getline(std::cin, name);
		this->setKingdomName(name);
		std::cout << WHITE << "Participant " << RED << kingdomName << WHITE << " created... \n\n";
		return;
	}
	std::cout << "Player created \n";
	std::cout << "AI created \n";
}

void Participants::viewStats() {
	//For debugging
	DEBUG_FUNCTION("Participants, viewStats");

	i5array eachUnit = calculateEach(1);
	i5array totalResources = calculateEach(2);

	std::cout << "Kingdom name: " << kingdomName << "\n\n";

	for (int x = 0; x < 5; x++) {
		std::cout << "Total " << INF::RESOURCE_NAMES[x] << ": " << totalResources[x] << std::endl;
	}

	for (int x = 0; x < 5; x++)
		std::cout << "Total " << INF::TROOP_NAMES[x] << " alive: " << eachUnit[x] << std::endl;

	std::cout << "Your total army combat power: " << calculatePlayerValues(1).at(0);
	std::cout << "\nYour numnber of provinces: " << getProvincesNum() << "\n\n";

	if (Input::getInputText("View all stats? (Y/N) ", { "Y", "N" }).at(0) == 'Y')
		viewAllStatsFunction();

	std::cout << "Returning to menu" << std::endl;
}

std::vector<int> Participants::calculatePlayerValues(int decision) {
	//For debugging
	DEBUG_FUNCTION("Participants, calculatePlayerValues");

	i5array newArray = calculateEach(decision);
	switch (decision) {
	case 1: { // Return total CP
		int totalCPThingy = 0;
		for (int x = 0; x < 5; x++)
			totalCPThingy += newArray[x] * INF::TROOPS_CP[x];
		return { totalCPThingy };
	}
	case 2: {
		std::vector<int> newArray;
		for (int x : troopsLost) {
			newArray.push_back(x);
		}
		return newArray;
	}
	}

	std::cout << "Error case; shouldn't happen\n";
	std::vector<int> emptyVector;
	return emptyVector;
}

provSPTR Participants::getProvince(int index) { 
	//For debugging
	DEBUG_FUNCTION("Participants, getProvince");

	return provincesVector[index]; 
}

std::string Participants::getNewName() {
	//For debugging
	DEBUG_FUNCTION("Participants, getNewName");

	std::string newName = INF::createRandomName();
	for (provSPTR newProvince : provincesVector)
		if (newName == newProvince->getName())
			getNewName();


	for (commIt = commandersMap.begin(); commIt != commandersMap.end(); commIt++)
		if (newName == commIt->second->getName())
			getNewName();

	return newName;
}

// commSPTR Participants::getCommander(int index) {
//   std::unordered_map<std::string, commSPTR>::iterator it;
//   for (it = commandersMap.begin(); it != commandersMap.end(); it++)
//     if ()
// }

i5array Participants::getTrainCosts() { 
	//For debugging
	DEBUG_FUNCTION("Participants, getTrainCosts");

	return trainCosts; 
}

void Participants::setParticipantIndex(int num) { 
	//For debugging
	DEBUG_FUNCTION("Participants, setParticipantIndex");

	participantIndex = num; 
}

int Participants::getParticipantIndex() { 
	//For debugging
	DEBUG_FUNCTION("Participants, getParticipantIndex");

	return participantIndex; 
}

void Participants::viewAllStatsFunction() {
	//For debugging
	DEBUG_FUNCTION("Participants, viewAllStatsFunction");

	std::string literallyAnyRandomCharacter;
	std::cout << BLUE; // NW
	i5array troopsLost = calculateEach(3);
	for (int x = 0; x < 5; x++) {
		std::cout << INF::TROOP_NAMES[x] << " lost: "
			<< troopsLost[x]
			<< std::endl;
	}
	std::cout << "Total troops lost: ";
	calculatePlayerValues(2);
	std::cout << "\n\n\033[;0m"; // NW
	INF::enterAnything(1);
}

void Participants::printListOfProvinces() {
	//For debugging
	DEBUG_FUNCTION("Participants, printListOfProvinces");

	std::cout << "Here is a list of your provinces (Name, Coordinates): \n";
	for (provSPTR province : provincesVector)
	{
		std::cout << "- " << province->getName() << ": ";
		province->getCoords(USER);
		std::cout << "\n";
	}
}

/*Calls pickProvince(the current participant picks a province).Makes sure the province picked belongs to this participant.If not, call pickProvince again.

add functionality to potentially break out of the process-- enter -1 to leave the function and not be forced to pick a province??

-- revise to make it an array??*/
provSPTR Participants::pickYourProvince(int identifier) {
	//For debugging
	DEBUG_FUNCTION("Participants, pickYourProvince");

	provSPTR newProvince = pickProvince(identifier);
	if (newProvince->getParticipantIndex() == participantIndex)
	{
		std::cout << "This is one of your provinces...\n" + newProvince->getUserCoordsString() + "\n";
		return newProvince;
	}

	std::cout << "This province does not belong to you. Please try again \n";
	INF::clearScreen();

	pickYourProvince(identifier);

	//Invalid path
	return NULL;
}





bool Participants::hasCommander(std::string name) {
	//For debugging
	DEBUG_FUNCTION("Participants, hasCommander");

	if (commandersMap.find(name) == commandersMap.end())
		return false;
	return true;
}

commSPTR Participants::getCommander(std::string name) {
	//For debugging
	DEBUG_FUNCTION("Participants, getCommander");

	return commandersMap[name];
}

int Participants::calculateTotals(int option)
{
	//For debugging
	DEBUG_FUNCTION("Participants, calculateTotals");

	int sum = 0;
	std::array <int, 5> totals = calculateEach(option);
	for (int x : totals)
		sum += x;

	return sum;
}

i5array Participants::calculateEach(int option)
{
	//For debugging
	DEBUG_FUNCTION("Participants, calculateEach");

	i5array returnArray = { 0, 0, 0, 0, 0 };

	std::vector<std::shared_ptr<PrimeUnits>> unitsVector = {};

	/*unitsVector = [&](std::vector < std::shared_ptr<PrimeUnits>> unitsVector, std::vector<provSPTR> provincesVector) {
		for (std::shared_ptr<PrimeUnits> ptr : provincesVector) {
			unitsVector.push_back(ptr);
		}
	}*/

	for (std::shared_ptr<PrimeUnits> ptr : provincesVector){
		unitsVector.push_back(ptr);
	}

	for (std::shared_ptr<PrimeUnits> ptr : commandersVector) {
		unitsVector.push_back(ptr);
	}

	//Iterate through all Provinces and Commanders
	for (std::shared_ptr<PrimeUnits> unit : unitsVector) {
		i5array secondaryArray;
		switch (option) {
			case 1://Calculate each Unit
				secondaryArray = unit->getGenericTroops(REGULAR);
				break;
			case 2://Calculate each resource
				secondaryArray = unit->getAllResources();
				break;
			case 3://calculate each troop lost
				secondaryArray = unit->getGenericTroops(LOST);
				break;
		}

		returnArray = mutateArray(returnArray, modifyArrayAmount, INF::INCREASE);
		
	}
	
	return returnArray;
}

bool Participants::subtractCheckResources(unitSPTR unit, i5array resources) {
	//For debugging
	DEBUG_FUNCTION("Participants, subtractCheckResources");
	unit->mutateAllResources(costs, DECREASE); 
	for (int x : unit->getAllResources()) {
		if (x < 0) {
			//Undo subtractions
			unit->mutateAllResources(costs, INCREASE); 
			return false;
		}
	}
	//Original resources array is greater than the resources being subtracted
	return true;
}





provSPTR Participants::getProvince(std::string name)
{
	//For debugging
	DEBUG_FUNCTION("Participants, getProvince");

	return provincesMap[name];
}

/*provSPTR Participants::selectRandomProvince()
{
	//place holder
	Provinces newProvince;
	return &newProvince;
}*/

bool Participants::hasProvince(std::string name)
{
	//For debugging
	DEBUG_FUNCTION("Participants, hasProvince");

	if (provincesMap.find(name) != provincesMap.end()) {
		return true;
	}

	return false;
}

bool Participants::hasProvince(int participantNumberArg) {
	return participantNumberArg == participantIndex;
}

bool Participants::hasProvince(provSPTR province) {
	return province->getParticipantIndex() == participantIndex;
}

commSPTR Participants::pickCommander() { 
	//For debugging
	DEBUG_FUNCTION("Participants, pickCommander");

	this->displayCommanders();
	std::string name = " ";
	println(("Enter the name of the commander you wish to select " + 
		"(Enter - 1 to cancel selection) : "));

	getline(std::cin, name);

	if (hasCommander(name)) {
		std::cout << "Commander " << name << " selected...\n";
		return commandersMap.at(name);
	} else if (name != "-1") {
		println(("Invalid name entered. Please try again... " + 
			"(Enter any character to continue)"));

		INF::enterAnything(1);
		pickCommander();
	}

	std::cout << "Cancelling selection\n";
		
	return nullptr;
}

void Participants::displayCommanders() {
	//For debugging
	DEBUG_FUNCTION("Participants, displayCommanders");

	std::cout << "Here is list of your commanders: \n";
	CommandersPtrMap commandersMap = getCommandersMap();
	CommandersPtrMap::iterator it;

	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		commSPTR tempCommander = it->second;
		std::cout << "- Commander " << tempCommander->getName() + 
			"; Level: " << tempCommander->getLevel() << std::endl;
		delete tempCommander;
	}
}

/*
Prompt the user to enter coordinates for a province

Prompt: pick the coords...
switch(phrase)
1: of the province you want to select
2: of the province you want to move to
3: of the army you want to use to attack the target with"
*/
provSPTR Participants::pickProvince(int phrase) {
	//For debugging
	DEBUG_FUNCTION("Participants, pickProvince");

	std::vector<std::string> actualCoordinatesAVTwo = { "-1" };
	//range of possible coordinates
	for (int x = 1; x <= INF::continentSize; x++) {
		actualCoordinatesAVTwo.push_back(std::to_string(x));
	}
	
	showMap();

	std::array<std::string, 3> phrases{ 
		"province you want to select" , 
		"province you want to move to", 
		"army you want to use to attack the target with" 
	};

	//Prints list of provinces if prompted
	if (phrase == 1 || phrase == 2) {
		printListOfProvinces();
	}

	std::string xCoordPrompt = "Enter the x coordinate of the " + 
		phrases.at(phrase - 1) +
		" (Enter '-1' to go back to previous menu): ";

	std::string yCoordPrompt = xCoordPrompt;
	//Make x prompt relatable to y
	yCoordPrompt.at(10) = 'y';

	// Critical: check to make sure the coordinate checkings are correct
	int xUserCoord = std::stoi(getInputText(xCoordPrompt, actualCoordinatesAVTwo);
	int yUserCoord = std::stoi(getInputText(yCoordPrompt, actualCoordinatesAVTwo);

	//Cancel action
	if (xUserCoord == -1 || yUserCoord == -1) {
		return nullptr;
	}

	return getUserProvince(std::make_pair(xUserCoord, yUserCoord));
}

bool Participants::hasUnit(const std::string &unitName) { 
	//For debugging
	DEBUG_FUNCTION("Participants, hasUnit");

	if (hasCommander(unitName)) {
		return true;
	}
	else if (hasProvince(unitName)) {
		return true;
	}
	return false;
}

bool Participants::hasUnit(PrimeUnits unit&) { 
	try {
		PrimeUnits* tempUnit = unit; 
		std::string name = tempUnit->getName(); 
		delete tempUnit; 

		if (typeid(tempUnit).name == "Commanders") { 
			return hasCommander(name); 
		}

		return hasProvince(name); 
		bool returnValue = hasCommander(name); 
	} catch (...) {
		std::cout << "Something wrong... Participants::hasUnit(PrimeUnits unit&)";
	}
}

provSPTR Participants::getSystemProvince(ipair systemCoords) {
	//For debugging
	DEBUG_FUNCTION("Participants, getSystemProvince");

	return Map::getSystemProvince(systemCoords);
}

void Participants::showMap() {
	//For debugging
	DEBUG_FUNCTION("Participants, showMap");

	Map::showMap();
}

i5array Participants::getPrimeUnitsArray() {
	//For debugging
	DEBUG_FUNCTION("Participants, getPrimeUnitsArray");

	i5array returnArray = {0,0,0,0,0};
	partSPTR p = std::make_shared(new Participants());

	try {
		std::thread th1 = p->th1Method();
		std::thread th2 = p->th2Method();
		th1.join();
		th2.join();
	}
	catch (...) {
		getPrimeUnitsArrayCommanders();
		getPrimeUnitsArrayProvinces();
	}
	

	return mutateArray(returnArray, allCommandersArray, true);
}


int Participants::getPrimeUnitsAmount() {
	//For debugging
	DEBUG_FUNCTION("Participants, getPrimeUnitsAmount");

	int amount = 0;
	for (int x : getPrimeUnitsArray()) {
		amount += x;
	}

	return amount;
}

std::thread Participants::th1Method() {
	//For debugging
	DEBUG_FUNCTION("Participants, th1Method");

	return std::thread([=] {getPrimeUnitsArrayProvinces(); });
}

std::thread Participants::th2Method() {
	//For debugging
	DEBUG_FUNCTION("Participants, the2Method");

	return std::thread([=] {getPrimeUnitsArrayCommanders(); });
}




ipair Participants::pickCoords() {
	//For debugging
	DEBUG_FUNCTION("Participants, pickCoords");

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

	bool xCoordCondition = xCoordinate > 0 && xCoordinate <= INF::continentSize;
	bool yCoordCondition = yCoordinate > 0 && yCoordinate <= INF::continentSize;
	if (xCoordCondition && yCoordCondition) {
		return { xCoordinate, yCoordinate };
	}

	INF::addColor(RED);
	std::cout << "Inputed coordinates are out of bounds... please try again.";
	INF::addColor(RESET);
	pickCoords();

	//Error path
	ipair tempPair(-1, -1);
	return tempPair;
}

partSPTR Participants::getParticipant(int listIndex) { 
	return participantsList.at(listIndex);
}
std::unordered_map<std::string, commSPTR> Participants::getCommandersMap() {
	return commandersMap;
}

void Participants::getPrimeUnitsArrayCommanders() {
	//For debugging
	DEBUG_FUNCTION("Participants, getPrimeUnitsArrayCommanders");

	for (commSPTR instance : commandersVector) {
		i5array commanderArray = instance.getTroop(REGULAR, -1, ALL);
		//INF::mutateArray(allCommandersArray, commanderArray, INCREASE);
	}
}

void Participants::getPrimeUnitsArrayProvinces() {
	//For debugging
	DEBUG_FUNCTION("Participants, getPrimeUnitsArrayProvinces");

	for (provSPTR instance : provincesVector) {
		i5array provincesArray = instance->getTroop(REGULAR, -1, ALL);
		//INF::mutateArray(allProvincesArray, provincesArray, INCREASE);
	}
}

int Participants::getPrimeUnitsAmount() {
	//For debugging
	DEBUG_FUNCTION("Participants, getPrimeUnitsAmount");

	int amount = 0;
	for (int x : getPrimeUnitsArray()) {
		amount += x;
	}

	return amount;
}


void Participants::initializeParticipants(int totalPlayers, int humanPlayers) {
	//For debugging
	DEBUG_FUNCTION("Database, initializeParticipant");

	for (int x = 0; x < totalPlayers; x++)
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

void Participants::createCapitals() {
	//For debugging
	DEBUG_FUNCTION("Database, createCapitals()");

	for (partSPTR participant : participantsList) {
	start:
		ipair systemCoords;
		systemCoords.first = rand() % INF::continentSize;
		systemCoords.second = rand() % INF::continentSize;

		provSPTR province = Map::getProvince(SYSTEM, systemCoords);

		if (province->getParticipantIndex() == -1)
		{
			province->setParticipantIndex(participant->getParticipantIndex());
			province->setName(participant->getNewName());
			participant->addProvince(province);
			participant->setCapital(province);
		} else {
			goto start;
		}
	}

}