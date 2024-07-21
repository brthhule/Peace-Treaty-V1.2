#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include COMMANDERS_HEADER

using namespace COMM;
using namespace TROOP;
using namespace INF;

/*	"Resources:      ",
	"Troops present: ",
	"Troops injured: ",
	"Troops lost:    ",
	"Other stats:    "
*/
s5array COMM::statsOne = {
	"Resources:      ",
	"Troops present: ",
	"Troops injured: ",
	"Troops lost:    ",
	"Other stats:    "
};

//Check this
std::array<s5array, 4> namesOfManOne = {
	INF::RESOURCE_NAMES,
	TROOP::TROOP_NAMES
};

std::array<std::string, 6> namesOfManTwo{
	 "Total Troops",
	 "Total Army CP",
	 "Commander Level",
	 "Max Troops this army can have",
	 "Army Food consumption",
	 "Max Resources this army can have"
};

/*Constructors*/
Commanders::Commanders() : Commanders(1, "Unnamed", -1) { }

Commanders::Commanders(int level, std::string name, int participantIndex) : PrimeUnits(participantIndex) {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "Commanders (1 Param)");

	level = level;
	moved = false;
	maxTroops = level * 10;
	totalMaxResources = 0;
	setName(name);

	troopConditions = {};
	for (int condition = 0; condition < 3; condition++) {
		for (int troopType = 0; troopType < 5; troopType++) {
			for (int tier = 0; tier < 5; tier++) {
				troopConditions.at(condition).at(troopType).at(tier) = {};
			}
		}
	}

	std::array<std::array<std::vector<TroopUnitsBASE>, 5>, 5> battleFormation; 
	for (int lane = 0; lane < 5; lane++) {
		for (int cell = 0; cell < 5; cell++) {
			battleFormation.at(lane).at(cell) = {};
		}
	}
}
/*Destructor*/
Commanders::~Commanders() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "~Commanders");
}

/////////////////////Display///////////
void Commanders::printCommanderStats() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "printCommanderStats");

	// print out stats
	LOG::addColor(LOG::BLUE);
	//Add implementation
	 
	std::cout << COMM::statsOne.at(0) << std::endl; 
	this->printResources();

	std::cout << COMM::statsOne.at(0) << std::endl;
	this->printTroopsPresent();

	//Continue implementing here
	LOG::addColor(LOG::RESET);
}

////////////Accessors//////////////////
int Commanders::getCommanderStat(int index) {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "getCommanderStat");

	//placeholder
	return -1;
	//return *commanderArmyStats[index];
}

const i5array Commanders::getUpgradeCosts() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "getUpgradeCosts");

	i5array costsArray = {};
	costsArray.fill(0);


	for (int x = 0; x < 5; x++) {
		costsArray[x] = costToUpgrade.at(x) * level;
	}
		
	return costsArray;
}



void Commanders::calculateCommanderScoutLog(){
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "calculateCommanderScoutLog");

	//Implement this
}

void Commanders::addLevel() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "addLevel");
	level++;
}

bool Commanders::hasMoved() const {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "hasMoved");

	return moved;
}

void Commanders::resetCommanderMoved() {
	//For debugging
	DEBUG_FUNCTION("Commanders.cpp", "resetCommanderHasMoved");

	moved = false;
}

constINT Commanders::getCombatPower() const { return combatPower; } 

void Commanders::calculateFoodConsumption() {
	foodConsumption = 0;
	for (int troopType = 0; troopType < 5; troopType++) { 
		foodConsumption += getSumOfTiersOfTroop(REGULAR, TroopTypes(troopType)); 
	}
}

constINT Commanders::getFoodConsumption() const {
	return foodConsumption;
}

constINT Commanders::getLevel() const {
	return level;
}

void Commanders::setIndexInProvince(int index) {
	indexInProvince = index;
}

const int& Commanders::getIndexInProvince() const {
	return indexInProvince;
}

commSPTR COMM::make_commSPTR(Commanders& commander_ref) { 
	return std::make_shared<Commanders>(commander_ref);
}