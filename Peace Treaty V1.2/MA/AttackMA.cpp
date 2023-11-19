#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Participants.h"

void Participants::mainAttackMA(
	Provinces* defendingProvinceArg, 
	Commanders* attackingCommanderArg) {

	INF::debugFunction("AttackMA, mainAttackMA");

	Provinces* defendingProvince = defendingProvinceArg;
	Commanders* attackingCommander = attackingCommanderArg;

	//Find commander to attack with
	if (attackingCommander == nullptr) {
		std::vector<Commanders*> commandersCanAttack = getCommandersCanAttack(defendingProvince->getCoords(SYSTEM));
		if (commandersCanAttack.size() == 0) {
			std::cout << "There are no armies available to attack the enemy. Please move an army unit to one of the provinces around the target. \n\n";
			return;
		}

		attackingCommander = pickCommanderAttack(commandersCanAttack);
	}
	
	playerCommitAttack(defendingProvince);
}


std::vector<Commanders*> Participants::getCommandersCanAttack(std::pair<int, int> defenderSystemCoords) {
	std::vector<Commanders*> commandersCanAttack = {};

	std::array<std::pair<int, int>, 8> surroundingProvinces;
	int currentElements = 0;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++)
		{
			//Make sure the changed provinces aren't the same as the unchanged province
			if (x != 0 || y != 0) {
				std::pair<int, int> tempPair(x, y);
				surroundingProvinces[currentElements] = tempPair;
				currentElements++;
			}
		}
	}

	for (std::pair<int, int> currentPair : surroundingProvinces) {
		int
			firstCoordinate = defenderSystemCoords.first + x,
			secondCoordinate = defenderSystemCoords.second + y;

		bool
			checkFirstCoordinate = (
				firstCoordinate >= 0 &&
				firstCoordinate < INF::continentSize),
			checkSecondCoordinate = (
				secondCoordinate >= 0 &&
				secondCoordinate < INF::continentSize);

		if (checkFirstCoordinate && checkSecondCoordinate) {
			std::pair<int, int> tempCoords(firstCoordinate, secondCoordinate);

			Provinces* provincePtr = this->getSystemProvince(tempCoords);

			//Get all Commanders at this province
			std::vector<Commanders*> provinceCommanders = provincePtr->getAllCommanders();

			//Add this participant's commanders the vector of commanders that can attack
			for (Commanders* element : provinceCommanders) {
				if (element->getParticipantIndex() == participantIndex) {
					commandersCanAttack.push_back(element);
				}
			}
		}
	}
			
	return commandersCanAttack;
}

Commanders* Participants::pickCommanderAttack(std::vector <Commanders*> commandersCanAttack) {
	//For debugging
	INF::debugFunction("AttackMA, findCommander");

	std::cout << "The following commanders can attack the target: \n";
	std::cout << "Amount of commanders: " << commandersCanAttack.size() << std::endl;


	for (Commanders* commander : commandersCanAttack) {
		std::cout << "Commander " << commander->getUnitName() +
			", Level: " << commander->getLevel();
	}
	
	std::cout << "Enter the name of the commander you would like to select: ";
	std::string commanderName;
	getline(std::cin, commanderName);

	//If participant doesn't have commander, recurse until it does
	if (this->hasCommander(commanderName) == false) {
		std::cout << "Invalid commander selected... please try again.\n";
		pickCommanderAttack(commandersCanAttack);
	}
		
	return getCommander(commanderName);
}

void AttackMA::preAttack()
{
	//For debugging
	INF::debugFunction("AttackMA, preAttack");

	oldResources = attackingCommander->getAllResources();
	playerCommitAttack();
}

void Participants::playerCommitAttack(Provinces* defendingProvince,  Commanders* attackingCommander) {
	//For debugging
	INF::debugFunction("AttackMA, playerCommitAttack");

	std::vector<Commanders*> defendingCommanders = defendingProvince->getAllCommanders();

	i5array preAttackResources = attackingCommander->getAllResources();

	for (Commanders* defendingCommander : defendingCommanders) {

	}
	Commanders* defendingCommander = defendingCommanders[0];
	int attackerCP = attackingCommander->getCP();
	int defendingCP = defendingCommander->getCP();
	int attackerLostCP = 0;
	int defenderLostCP = 0;

	determineLostCP(attackerCP, defendingCP, attackerLostCP, defenderLostCP);

	std::array<int, 5> troopsLost = { 0, 0, 0, 0, 0 };
	std::array<int, 5> injuredTroops = { 0, 0, 0, 0, 0 };

	calculateTroopsLost(attackingCommander, attackerLostCP, troopsLost, 0);

	for (int x = 0; x < 5; x++) {
		injuredTroops[x] = troopsLost[x] / (2 * enemyDifficulty);
		troopsLost[x] -= injuredTroops[x];
	}
	attackingCommander->mutateTroop(INJURED, NULL, injuredTroops, ALL, INCREASE);
	attackingCommander->mutateTroop(LOST, NULL, troopsLost, ALL, INCREASE);

	std::cout << "  Results: \n\n";
	printResourcesGained();
	attackingCommander->printResources();
	casualtyReport(troopsLost, injuredTroops);

	char viewAllArmyStats = ' ';
	char repeatViewAllArmyStats = 'N';
	std::string viewAllArmyStatsString;

	defendingProvince->addCommander(
		attackingCommander);

	do {
		repeatViewAllArmyStats = 'N';
		viewAllArmyStats = Input::getInputText("View all army stats? (Y/N) ", { "Y", "N" }).at(0);
		std::cout << std::endl;

		switch (viewAllArmyStats) {
		case 'Y': {
			attackingCommander->printCommanderStats();
			break;
		}
		case 'N':
			break;
			std::cout << std::endl;
		default:
			repeatViewAllArmyStats = 'Y';
			std::cout << "Invalid character entered. Please try again.\n";
			break;
		}
	} while (repeatViewAllArmyStats == 'Y');

	/*fix this-- add attack functionality, differences in CP and stuff*/
}


/*Basically go through each unit type and subtract 16CP worth of troops and keep going (done so that lost troops are distributed evenly among the various ranks, but there is still use to training lower rank troops as meat shields (if all lower troops are used up, then losses start piling up on higher rank troops; it's key to keep a healthy proportion of troops in your army))*/
void AttackMA::calculateTroopsLost(Commanders* commander, int lostCombatPower, std::array<int, 5>& troopsLost, int troopIndex) {
	//For debugging
	INF::debugFunction("AttackMA, calculateTroopsLost");

	int troopPresent = commander->getTroop(REGULAR, troopIndex, INF::SINGLE)[0];

	int troopCP = INF::Troops_CP[troopIndex];

	//If lostCP > 16
	if (lostCombatPower - 16 > 0)
	{
		if (troopPresent >= 16 / troopCP)
		{
			troopsLost[troopIndex] += 16 / troopCP;
			lostCombatPower -= 16;
		}
		else if (troopPresent > 0)
		{
			troopsLost[troopIndex] += troopPresent;
			lostCombatPower -= troopPresent * troopCP;
		}
	}
	//If lostCP < 16
	else
	{
		//This is how many troops are needed to get down to 0
		int troopsNeeded = 16 / (troopPresent * troopCP);
		if (troopPresent >= troopsNeeded)
		{
			lostCombatPower -= troopsNeeded * troopCP;
			troopsLost[troopIndex] += troopsNeeded;
		}
		else
		{
			troopsLost[troopIndex] += troopPresent;
			lostCombatPower -= troopPresent * troopCP;
		}
	}
	troopIndex += 1;
	if (lostCombatPower > 0)
	{
		calculateTroopsLost(commander, lostCombatPower, troopsLost, troopIndex);
	}
}


void AttackMA::battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex) /*fix this*/
{
	//For debugging
	INF::debugFunction("AttackMA, battleCalculationsTwo");

	Participants* playerParticipant = db.getCurrentParticipant();

	int z = abs(4 - troopIndex);

	for (int b = 0; b < INF::Troops_CP[z]; b++) {
		if (attackingCommander->getTroop(REGULAR, 5, SINGLE)[0] > 0) {
			b = INF::Troops_CP[z];
		}
		else {
			if (lostCombatPower > 0) {
				lostCombatPower -= INF::Troops_CP[troopIndex];
				troopsLost[troopIndex]++;
				attackingCommander->mutateTroop(REGULAR, troopIndex, {1}, SINGLE, DECREASE);
				attackingCommander->mutateTroop(LOST, troopIndex, {1}, SINGLE, INCREASE);
			}
			else
				b = INF::Troops_CP[z];
		}
	}
}

void AttackMA::printResourcesGained()
{
	//For debugging
	INF::debugFunction("AttackMA, printResourcesGained");

	std::array<int, 5> currentResources = attackingCommander->getAllResources();
	std::cout << "Resources gained: \n \033[;34m";

	for (int x = 0; x < 5; x++)
		std::cout << "- " << INF::RESOURCE_NAMES[x] << ": " << currentResources[x] - oldResources[x] << "\n\n\033[;0m";
}

void AttackMA::determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP)
{
	//For debugging
	INF::debugFunction("AttackMA, determineLostCP");

	int higherCP, lowerCP = 0;

	if (attackerCP > defendingCP)
	{
		higherCP = attackerCP;
		lowerCP = defendingCP;
	}
	else
	{
		higherCP = defendingCP;
		lowerCP = attackerCP;
	}

	int difference = attackerCP / defendingCP;
	attackerLostCP =
		(defendingCP *
			(1 / difference)) / 2;
	defenderLostCP = (attackerCP * (1 / difference)) / 2;

	//Add functionality so that there have to be some amount of CP lost; if no CP is lost, then will just repeat forever
	if (attackerLostCP == 0)
		attackerLostCP = 1;
	if (defendingCP == 0)
		defendingCP = 1;
}

void AttackMA::casualtyReport(std::array<int, 5> troopsLost, std::array<int, 5> injuredTroops)
{
	//For debugging
	INF::debugFunction("AttackMA, casualtyReport");

	std::cout << "\nTroops casualties: \n";
	for (int x = 0; x < 5; x++) /*print out deaths*/
	{
		std::cout << INF::TROOP_NAMES[x] << " lost: " << troopsLost[x] << std::endl;
	}
	std::cout << std::endl;
	for (int x = 0; x < 5; x++) /*print out deaths*/
	{
		std::cout << INF::TROOP_NAMES[x] << " injured: " << injuredTroops[x] << std::endl;
	}
	std::cout << std::endl;
}