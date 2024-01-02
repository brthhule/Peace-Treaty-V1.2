#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER  

using namespace COMM;
using namespace PROV; 
using namespace PART;
using namespace INF;
using namespace PROV;
using namespace UNIT;
using namespace COORD;

i5array trainCosts = { 5, 4, 3, 2, 1 };  

std::vector<partSPTR> Participants::playersList = {};  
std::vector<partSPTR> Participants::botsList = {};  
std::vector<Participants> Participants::participantsList = {};
int totalPlayers = 0;

Participants::Participants() : Participants(0) {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "Participants (0 Param)");
	capitalProvince = nullptr;
}

Participants::Participants(int pIndex) { 
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "Participants (1 Param)");
	capitalProvince = nullptr; 
	addCommander();
	setKingdomName("-1");
	participantIndex = pIndex;

	capitalIndex = 0;

	//Defaults
	commandersMap = std::unordered_map<std::string, commSPTR>();
	provincesMap = std::unordered_map<std::string, provSPTR>();
	commIt = std::unordered_map<std::string, commSPTR>::iterator();

	provincesVector = std::vector<provSPTR>();
	commandersVector = std::vector<commSPTR>(); 
}

// Accessors
provSPTR Participants::getCapitalProvince() { return capitalProvince; }

int Participants::getProvincesNum() const { return (int) provincesVector.size(); }

int Participants::getCommandersNum() const { return (int) commandersVector.size(); }

Participants::~Participants() {    

}


// Mutators
void Participants::setCapital(provSPTR newProvince) {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "setCapital");

	capitalProvince = newProvince;
}

void Participants::addProvince(provSPTR newProvince) {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "addProvince");

	provincesVector.push_back(newProvince);
	provincesMap[newProvince->getName()] = provincesVector[provincesVector.size() - 1];
}




void Participants::setKingdomName(std::string newName) {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "setKingdomName");

	if (newName == "-1") {
		newName = getNewName();
	}
		
	kingdomName = newName;
}

std::string Participants::getKingdomName() { return kingdomName; }

bool Participants::isAlive() const {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "isAlive");

	if (getProvincesNum() > 0 || getCommandersNum() > 0) { return true; }
	return false;
}

void Participants::createAsPlayer(bool status)
{
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "createAsPlayer");

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
	DEBUG_FUNCTION("Participants.cpp", "viewStats");

	i5array eachUnit = calculateEach(1);
	i5array totalResources = calculateEach(2);

	std::cout << "Kingdom name: " << kingdomName << "\n\n";

	for (int x = 0; x < 5; x++) {
		std::cout << "Total " << INF::RESOURCE_NAMES[x] << ": " << totalResources[x] << std::endl;
	}

	for (int x = 0; x < 5; x++)
		std::cout << "Total " << TROOP::TROOP_NAMES[x] << " alive: " << eachUnit[x] << std::endl;

	std::cout << "Your total army combat power: " << calculatePlayerValues(1).at(0);
	std::cout << "\nYour numnber of provinces: " << getProvincesNum() << "\n\n";

	if (Input::getInputText("View all stats? (Y/N) ", { "Y", "N" }).at(0) == 'Y')
		viewAllStatsFunction();

	std::cout << "Returning to menu" << std::endl;
}

std::vector<int> Participants::calculatePlayerValues(int decision) {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "calculatePlayerValues");

	i5array newArray = calculateEach(decision);
	switch (decision) {
	case 1: { // Return total CP
		int totalCPThingy = 0;
		for (int x = 0; x < 5; x++)
			totalCPThingy += newArray[x] * TROOP::TROOPS_CP[x];
		return { totalCPThingy };
	}
	case 2: {
		std::vector<int> newArray;
		std::vector<int> troopsLost;//?????????????????????????????????????????????????
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
	DEBUG_FUNCTION("Participants.cpp", "getProvince");

	return provincesVector[index]; 
}

std::string Participants::getNewName() {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getNewName");

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

constArrayReference Participants::getTrainCosts() { 
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getTrainCosts");

	return trainCosts; 
}

void Participants::setParticipantIndex(int num) { 
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "setParticipantIndex");

	participantIndex = num; 
}

constINT Participants::getParticipantIndex() const { 
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getParticipantIndex");

	return participantIndex; 
}

void Participants::viewAllStatsFunction() {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "viewAllStatsFunction");

	std::string literallyAnyRandomCharacter;
	std::cout << BLUE; // NW
	i5array troopsLost = calculateEach(3);
	for (int x = 0; x < 5; x++) {
		std::cout << TROOP::TROOP_NAMES[x] << " lost: "
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
	DEBUG_FUNCTION("Participants.cpp", "printListOfProvinces");

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
	DEBUG_FUNCTION("Participants.cpp", "pickYourProvince");

	provSPTR newProvince = pickProvince(identifier);
	if (newProvince->getParticipantIndex() == participantIndex)
	{
		std::cout << "This is one of your provinces...\n" + newProvince->CoordsBASE::getCoordsString(USER) + "\n"; 
		return newProvince;
	}

	std::cout << "This province does not belong to you. Please try again \n";
	INF::clearScreen();

	pickYourProvince(identifier);

	//Invalid path
	return NULL;
}

const bool Participants::hasCommander(std::string name) const {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "hasCommander");

	if (commandersMap.find(name) == commandersMap.end()) { return false; }
	return true;
}

commSPTR Participants::getCommander(std::string name) {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getCommander");

	return commandersMap[name];
}

int Participants::calculateTotals(int option)
{
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "calculateTotals");

	int sum = 0;
	std::array <int, 5> totals = calculateEach(option);
	for (int x : totals)
		sum += x;

	return sum;
}

i5array Participants::calculateEach(int option)
{
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "calculateEach");

	i5array returnArray = { 0, 0, 0, 0, 0 };

	std::vector<std::shared_ptr<Commanders>> commandersTempVector = {};

	/*unitsVector = [&](std::vector < std::shared_ptr<PrimeUnits>> unitsVector, std::vector<provSPTR> provincesVector) {
		for (std::shared_ptr<PrimeUnits> ptr : provincesVector) {
			unitsVector.push_back(ptr);
		}
	}*/


	for (std::shared_ptr<Commanders> ptr : commandersVector) {
		commandersTempVector.push_back(ptr);
	}

	//Iterate through all Provinces and Commanders
	for (std::shared_ptr<Commanders> commander : commandersTempVector) {
		i5array secondaryArray;
		switch (option) {
			case 1://Calculate each Unit
				secondaryArray = commander->getArrayOfSumsOfTiersOfAllTroops(TROOP::REGULAR);
				break;
			case 2://Calculate each resource
				secondaryArray = commander->getAllResources(); 
				break;
			case 3://calculate each troop lost
				secondaryArray = commander->getArrayOfSumsOfTiersOfAllTroops(TROOP::LOST); 
				break;
		}

		returnArray = mutateArray(returnArray, secondaryArray, INF::INCREASE);
		
	}
	
	return returnArray;
}

bool Participants::subtractCheckResources(unitSPTR unit, i5array resources) {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "subtractCheckResources");
	unit->mutateAllResources(resources, DECREASE); 
	for (int x : unit->getAllResources()) {
		if (x < 0) {
			//Undo subtractions
			unit->mutateAllResources(resources, INCREASE); 
			return false;
		}
	}
	//Original resources array is greater than the resources being subtracted
	return true;
}





provSPTR Participants::getProvince(std::string name)
{
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getProvince");

	return provincesMap[name];
}

/*provSPTR Participants::selectRandomProvince()
{
	//place holder
	Provinces newProvince;
	return &newProvince;
}*/

const bool Participants::hasProvince(std::string name) const {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "hasProvince");

	if (provincesMap.find(name) != provincesMap.end()) {
		return true;
	}

	return false;
}

const bool Participants::hasProvince(int participantNumberArg) const {
	return participantNumberArg == participantIndex;
}

const bool Participants::hasProvince(provSPTR province) const {
	return province->getParticipantIndex() == participantIndex;
}

commSPTR Participants::pickCommander() const { 
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "pickCommander");

	this->displayCommanders();
	std::string name = " ";
	std::cout << "Enter the name of the commander you wish to select (Enter - 1 to cancel selection) : ";

	getline(std::cin, name);

	if (hasCommander(name)) {
		std::cout << "Commander " << name << " selected...\n";
		return commandersMap.at(name);
	} else if (name != "-1") {
		std::cout << "Invalid name entered. Please try again...\n(Enter any character to continue)";

		INF::enterAnything(1);
		pickCommander();
	}

	std::cout << "Cancelling selection\n";
		
	return nullptr;
}

void Participants::displayCommanders() const{
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "displayCommanders");

	std::cout << "Here is list of your commanders: \n";
	commMAP commandersMap = getCommandersMap();
	commMAP::iterator it; 

	for (it = commandersMap.begin(); it != commandersMap.end(); it++) {
		commSPTR tempCommander = it->second;
		std::cout << "- Commander " << tempCommander->getName() + 
			"; Level: " << tempCommander->getLevel() << std::endl;
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
	DEBUG_FUNCTION("Participants.cpp", "pickProvince");

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
	if (phrase == 1 || phrase == 2) { printListOfProvinces(); }

	/*Added explicitness below to get rid of Int - arithn error
	Error: A sub-expression may overflow before being assigned to a wider type*/
	int phraseString = phrase - 1;
	std::string xCoordPrompt = "Enter the x coordinate of the " + 
		phrases.at(phraseString) +
		" (Enter '-1' to go back to previous menu): ";

	std::string yCoordPrompt = xCoordPrompt;
	//Make x prompt relatable to y
	yCoordPrompt.at(10) = 'y';

	// Critical: check to make sure the coordinate checkings are correct
	int xUserCoord = std::stoi(Input::getInputText(xCoordPrompt, actualCoordinatesAVTwo));
	int yUserCoord = std::stoi(Input:: getInputText(yCoordPrompt, actualCoordinatesAVTwo));

	//Cancel action
	if (xUserCoord == -1 || yUserCoord == -1) { return nullptr; }
	return Map::getProvince(USER, std::make_pair(xUserCoord, yUserCoord));
}

bool Participants::hasUnit(const std::string &unitName) const { 
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "hasUnit(const std::string&)");

	if (hasCommander(unitName)) { return true; }
	else if (hasProvince(unitName)) { return true; }
	return false;
}

bool Participants::hasUnit(PrimeUnits &unit) const { 
	try {
		const std::string name = unit.getName();

		if (typeid(unit).name() == "Commanders") {
			return hasCommander(name); 
		}

		return hasProvince(name); 

	} catch (...) {
		std::cout << "Something wrong... Participants::hasUnit(PrimeUnits unit&)";
	}

	//Something went wrong, placeholder value
	return false;
}

provSPTR Participants::getSystemProvince(ipair systemCoords) {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getSystemProvince");

	return Map::getProvince(SYSTEM, systemCoords);
}

i5array Participants::getPrimeUnitsArray() const {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getPrimeUnitsArray");

	i5array returnArray = {0,0,0,0,0};

	try {
		std::thread th1 = this->th1Method();
		std::thread th2 = this->th2Method();
		th1.join();
		th2.join();
	}
	catch (...) {
		getPrimeUnitsArrayCommanders();
		getPrimeUnitsArrayProvinces();
	}
	

	return mutateArray(returnArray, allCommandersArray, INCREASE); 
}


int Participants::getPrimeUnitsAmount() const{
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getPrimeUnitsAmount");

	int amount = 0;
	for (int x : getPrimeUnitsArray()) {
		amount += x;
	}

	return amount;
}

std::thread Participants::th1Method() const {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "th1Method");

	return std::thread([=] {getPrimeUnitsArrayProvinces(); });
}

std::thread Participants::th2Method() const {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "the2Method");

	return std::thread([=] {getPrimeUnitsArrayCommanders(); });
}

partSPTR Participants::getParticipant(int listIndex) const { 
	return std::make_shared<Participants>(participantsList.at(listIndex));
}
std::unordered_map<std::string, commSPTR> Participants::getCommandersMap() const{
	return commandersMap;
}

void Participants::getPrimeUnitsArrayCommanders() const {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getPrimeUnitsArrayCommanders");

	for (commSPTR instance : commandersVector) {
		//i5array commanderArray = instance.getTroop(REGULAR, -1, ALL);
		//INF::mutateArray(allCommandersArray, commanderArray, INCREASE);
	}
}

void Participants::getPrimeUnitsArrayProvinces() const {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "getPrimeUnitsArrayProvinces");

	for (provSPTR instance : provincesVector) {
		//i5array provincesArray = instance->getTroop(REGULAR, -1, ALL);
		//INF::mutateArray(allProvincesArray, provincesArray, INCREASE);
	}
}


void Participants::initializeParticipants(int totalPlayers, int humanPlayers, int count) {
	if (count == totalPlayers) { return; }

	std::cout << "Creating participant " << count + 1 << ": \n"; 
	Participants participant(count);
	participant.createCapital();
	if (count < totalPlayers) { participant.createAsPlayer(true); }
	else { participant.createAsPlayer(false); }
	participantsList.push_back(participant);

	initializeParticipants(totalPlayers, humanPlayers, ++count);
}

void Participants::createCapital() {
	//For debugging
	DEBUG_FUNCTION("Participants.cpp", "createCapital()")

	ipair systemCoords(rand() % continentSize, rand() % continentSize);
	provSPTR province = Map::getProvince(SYSTEM, systemCoords);

	//Recurses if Province is already taken
	if (province->getParticipantIndex() != -1) { createCapital(); }

	province->setParticipantIndex(participantIndex);
	province->setName(getNewName());
	addProvince(province);
	setCapital(province);
}



partSPTR Participants::getCurrentParticipant() {
	return std::make_shared<Participants>(participantsList.at(currentParticipantIndex));
}

bool Participants::isPlayer() const {
	if (participantIndex < humanPlayers) { return true; }
	return false;
}

void Participants::setHumanPlayers(int num) {
	humanPlayers = num;
}

const std::vector<Participants>& Participants::getParticipants() { 
	return participantsList; 
}