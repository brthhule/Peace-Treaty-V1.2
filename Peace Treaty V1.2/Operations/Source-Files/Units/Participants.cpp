#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER

using namespace COMM;
using namespace PART;
using namespace PROV;

i5array Participants::allCommandersArray = {};
i5array Participants::allProvincesArray = {};
i5array trainCosts = { 5, 4, 3, 2, 1 };

std::vector<partSPTR> Participants::playersList = {};  
std::vector<partSPTR> Participants::botsList = {};  


Participants::actionsMap = {
		{'B', 0}, //Build
		{'T', 1}, // Train
		{'S', 2}, //View stats
		{'U', 3}, //View map
		{'D', 4}, //View army overview
		{'N', 5}, //Go to next turn
		{'H', 6}, //View help screen
		{'P', 7}  //Pause game
};

	// Constructor
//Constructor
Participants::Participants() {
	//For debugging
	INF::debugFunction("Participants, Participants (0 Param)");

	Participants(0);

	capitalProvince = nullptr;
	//Default
	selectedCommander = nullptr;
}

Participants::Participants(int pIndex) {
	//For debugging
	INF::debugFunction("Participants, Participants (1 Param)");
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
	INF::debugFunction("Participants, getCapitalProvince");
	
	return capitalProvince; 
}

int Participants::getProvincesNum() { 
	//For debugging
	INF::debugFunction("Participants, getProvincesNum");

	return (int) provincesVector.size(); 
}

int Participants::getCommandersNum() { 
	//For debugging
	INF::debugFunction("Participants, getCommandersNum");
	
	return (int) commandersVector.size();
}


void Participants::initialCapRSS() {
	//For debugging
	INF::debugFunction("Participants, initialCaRSS");

	//Add functionality so, depending on the difficulty, AI participants get more or less resources to start off with
	provSPTR newProvince = getCapitalProvince();
	newProvince->modifyResources(INF::INITIAL_VALUES, true);
}

// Mutators
void Participants::setCapital(provSPTR newProvince) {
	//For debugging
	INF::debugFunction("Participants, setCapital");

	capitalProvince = newProvince;
}

void Participants::addProvince(provSPTR newProvince) {
	//For debugging
	INF::debugFunction("Participants, addProvince");

	provincesVector.push_back(newProvince);
	provincesMap[newProvince->getUnitName()] = provincesVector[provincesVector.size() - 1];
}


void Participants::addCommander() {
	//For debugging
	INF::debugFunction("Participants, addCommander");

	Commanders newCommander(1, getNewName());
	ipair tempSystemCoords = getCapitalProvince()->getCoords(CoordsBASE::SYSTEM);
	ipair tempUserCoords = getCapitalProvince()->getCoords(CoordsBASE::USER);

	newCommander.setParticipantIndex(participantIndex);
	newCommander.setCoords(tempSystemCoords, tempUserCoords);

	commandersVector.push_back(newCommander);
	commSPTR commanderPtr = std::make_shared(commandersVector.size() - 1);
	commandersMap[newCommander.getUnitName()] = commanderPtr;

	getCapitalProvince()->addCommander(commanderPtr);
}

void Participants::setKingdomName(std::string newName) {
	//For debugging
	INF::debugFunction("Participants, setKingdomName");

	if (newName == "-1") {
		newName = getNewName();
	}
		
	kingdomName = newName;
}

std::string Participants::getKingdomName() { return kingdomName; }

bool Participants::isAlive() {
	//For debugging
	INF::debugFunction("Participants, isAlive");

	if (getProvincesNum() > 0 || getCommandersNum() > 0) {
		return true;
	}

	return false;
}

void Participants::createAsPlayer(bool status)
{
	//For debugging
	INF::debugFunction("Participants, createAsPlayer");

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
	INF::debugFunction("Participants, viewStats");

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
	INF::debugFunction("Participants, calculatePlayerValues");

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
	INF::debugFunction("Participants, getProvince");

	return provincesVector[index]; 
}

std::string Participants::getNewName() {
	//For debugging
	INF::debugFunction("Participants, getNewName");

	std::string newName = INF::createRandomName();
	for (provSPTR newProvince : provincesVector)
		if (newName == newProvince->getUnitName())
			getNewName();


	for (commIt = commandersMap.begin(); commIt != commandersMap.end(); commIt++)
		if (newName == commIt->second->getUnitName())
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
	INF::debugFunction("Participants, getTrainCosts");

	return trainCosts; 
}

void Participants::setParticipantIndex(int num) { 
	//For debugging
	INF::debugFunction("Participants, setParticipantIndex");

	participantIndex = num; 
}

int Participants::getParticipantIndex() { 
	//For debugging
	INF::debugFunction("Participants, getParticipantIndex");

	return participantIndex; 
}

void Participants::viewAllStatsFunction() {
	//For debugging
	INF::debugFunction("Participants, viewAllStatsFunction");

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
	INF::debugFunction("Participants, printListOfProvinces");

	std::cout << "Here is a list of your provinces (Name, Coordinates): \n";
	for (provSPTR province : provincesVector)
	{
		std::cout << "- " << province->getUnitName() << ": ";
		province->getCoords(CoordsBASE::USER);
		std::cout << "\n";
	}
}

/*Calls pickProvince(the current participant picks a province).Makes sure the province picked belongs to this participant.If not, call pickProvince again.

add functionality to potentially break out of the process-- enter -1 to leave the function and not be forced to pick a province??

-- revise to make it an array??*/
provSPTR Participants::pickYourProvince(int identifier) {
	//For debugging
	INF::debugFunction("Participants, pickYourProvince");

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
	INF::debugFunction("Participants, hasCommander");

	if (commandersMap.find(name) == commandersMap.end())
		return false;
	return true;
}

commSPTR Participants::getCommander(std::string name) {
	//For debugging
	INF::debugFunction("Participants, getCommander");

	return commandersMap[name];
}

int Participants::calculateTotals(int option)
{
	//For debugging
	INF::debugFunction("Participants, calculateTotals");

	int sum = 0;
	std::array <int, 5> totals = calculateEach(option);
	for (int x : totals)
		sum += x;

	return sum;
}

i5array Participants::calculateEach(int option)
{
	//For debugging
	INF::debugFunction("Participants, calculateEach");

	i5array returnArray = { 0, 0, 0, 0, 0 };

	std::vector<std::shared_ptr<AllUnits>> unitsVector = {};

	/*unitsVector = [&](std::vector < std::shared_ptr<AllUnits>> unitsVector, std::vector<provSPTR> provincesVector) {
		for (std::shared_ptr<AllUnits> ptr : provincesVector) {
			unitsVector.push_back(ptr);
		}
	}*/

	for (std::shared_ptr<AllUnits> ptr : provincesVector){
		unitsVector.push_back(ptr);
	}

	for (std::shared_ptr<AllUnits> ptr : commandersVector) {
		unitsVector.push_back(ptr);
	}

	//Iterate through all Provinces and Commanders
	for (std::shared_ptr<AllUnits> unit : unitsVector) {
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
	INF::debugFunction("Participants, subtractCheckResources");
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
	INF::debugFunction("Participants, getProvince");

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
	INF::debugFunction("Participants, hasProvince");

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
	INF::debugFunction("Participants, pickCommander");

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

/*Display this participant's list of commSPTR/
void Participants::displayCommanders() {
	//For debugging
	INF::debugFunction("Participants, displayCommanders");

	std::cout << "Here is list of your commanders: \n";
	CommandersPtrMap commandersMap = getCommandersMap();
	CommandersPtrMap::iterator it;

	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		commSPTR tempCommander = it->second;
		std::cout << "- Commander " << tempCommander->getUnitName() + 
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
	INF::debugFunction("Participants, pickProvince");

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
	INF::debugFunction("Participants, hasUnit");

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
		std::string name = tempUnit->getUnitName(); 
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
	INF::debugFunction("Participants, getSystemProvince");

	return Map::getSystemProvince(systemCoords);
}

void Participants::showMap() {
	//For debugging
	INF::debugFunction("Participants, showMap");

	Map::showMap();
}

i5array Participants::getAllUnitsArray() {
	//For debugging
	INF::debugFunction("Participants, getAllUnitsArray");

	i5array returnArray = {0,0,0,0,0};
	partSPTR p = std::make_shared(new Participants());

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
	

	return mutateArray(returnArray, allCommandersArray, true);
}


int Participants::getAllUnitsAmount() {
	//For debugging
	INF::debugFunction("Participants, getAllUnitsAmount");

	int amount = 0;
	for (int x : getAllUnitsArray()) {
		amount += x;
	}

	return amount;
}

std::thread Participants::th1Method() {
	//For debugging
	INF::debugFunction("Participants, th1Method");

	return std::thread([=] {getAllUnitsArrayProvinces(); });
}

std::thread Participants::th2Method() {
	//For debugging
	INF::debugFunction("Participants, the2Method");

	return std::thread([=] {getAllUnitsArrayCommanders(); });
}

void Participants::updateTurnResourcesParticipant() {
	//For debugging
	INF::debugFunction("Participants, updateTurnResourcesParticipant");

	this->updateTurnResources();
}

void Participants::createMapParticipant() {
	//For debugging
	INF::debugFunction("Participants, createMapParticipant");

	setMap();
}

ipair Participants::pickCoords() {
	//For debugging
	INF::debugFunction("Participants, pickCoords");

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

std::unordered_map<std::string, commSPTR> Participants::getCommandersMap() {
	return commandersMap;
}

Participants::AttackMAInfo::AttackMAInfo(provSPTR defendingProvinceArg) {
	INF::debugFunction("Participants, AttackMAInfo");
	AttackMAInfo::defendingProvince = defendingProvinceArg;
}

Participants::AttackMAInfo::AttackMAInfo(provSPTR defenderProvinceArg, commSPTR commanderArg) {
	//For debugging
	INF::debugFunction("AttackMA, AttackMA (4 Param)");

	defendingProvince = defenderProvinceArg;
	attackingCommander = commanderArg;
}

Participants::AttackMAInfo::AttackMAInfo() {
	defendingProvince = nullptr;
	attackingCommander = nullptr;
}

void Participants::getAllUnitsArrayCommanders() {
	//For debugging
	INF::debugFunction("Participants, getAllUnitsArrayCommanders");

	for (commSPTR instance : commandersVector) {
		i5array commanderArray = instance.getTroop(REGULAR, -1, ALL);
		//INF::mutateArray(allCommandersArray, commanderArray, INCREASE);
	}
}

void Participants::getAllUnitsArrayProvinces() {
	//For debugging
	INF::debugFunction("Participants, getAllUnitsArrayProvinces");

	for (provSPTR instance : provincesVector) {
		i5array provincesArray = instance->getTroop(REGULAR, -1, ALL);
		//INF::mutateArray(allProvincesArray, provincesArray, INCREASE);
	}
}

int Participants::getAllUnitsAmount() {
	//For debugging
	INF::debugFunction("Participants, getAllUnitsAmount");

	int amount = 0;
	for (int x : getAllUnitsArray()) {
		amount += x;
	}

	return amount;
}