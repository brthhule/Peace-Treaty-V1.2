#include "..\..\..\Support\Paths.h"
#include PARTICIPANTS_HEADER

//using namespace PART;
using namespace TROOP;
using PROV::provSPTR; 
using COMM::commSPTR; 
using COMM::commSPTRList; 
using namespace Input;

using namespace INF;

void Participants::mainAttackMA(provSPTR defendProv, commSPTR attackComm) {
	DEBUG_FUNCTION("AttackMA.cpp", "mainAttackMA(provSPTR, commSPTR)");

	provSPTR defendingProvince = defendProv;
	commSPTR attackingCommander = attackComm;

	//Find commander to attack with
	if (attackingCommander == nullptr) {
		commSPTRList commandersCanAttack = getCommandersCanAttack(defendingProvince); 
		if (commandersCanAttack.size() == 0) {
			std::cout << "There are no armies available to attack the enemy. Please move an army unit to one of the Provinces:: around the target. \n\n";
			return;
		}

		attackingCommander = pickCommanderAttack(commandersCanAttack);
	}
	
	playerCommitAttack(defendingProvince, attackingCommander);
}

//Get the commanders that can attack the defending province. defenderSystemCoords reflects the corods of the province
std::vector<commSPTR> Participants::getCommandersCanAttack(provSPTR defendingProvince) {
	DEBUG_FUNCTION("AttackMA.cpp", "getCommandersCanAtack(provSPTR)");

	std::vector<commSPTR> commandersCanAttack = {};
	std::array<ipair, 8> surroundingProvinces;
	ipair defenderSystemCoords = defendingProvince->CoordsBASE::getCoords(COORD::SYSTEM);
	int currentElements = 0;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++)
		{
			//Make sure the changed Provinces:: aren't the same as the unchanged province
			if (x != 0 || y != 0) {
				ipair tempPair(defenderSystemCoords.first + x, defenderSystemCoords.second + y);
				surroundingProvinces[currentElements] = tempPair;
				currentElements++;
			}
		}
	}

	
	for (ipair currentPair : surroundingProvinces) {
		int coord1 = currentPair.first;
		int coord2 = currentPair.second;

		bool checkCoord1 = (coord1 >= 0 && coord1 < continentSize);
		bool checkCoord2 = (coord2 >= 0 && coord2 < continentSize);

		if (checkCoord1 && checkCoord2) {
			ipair tempCoords(coord1, coord2); 

			provSPTR provincePtr = getSystemProvince(tempCoords);

			//Get all Commanders at this province
			std::vector<commSPTR> provinceCommanders = provincePtr->getAllCommanders();

			//Add this participant's commanders the vector of commanders that can attack
			for (commSPTR element : provinceCommanders) {
				if (element->getParticipantIndex() == participantIndex) {
					commandersCanAttack.push_back(element);
				}
			}
		}
	}
			
	return commandersCanAttack;
}

commSPTR Participants::pickCommanderAttack(commSPTRList commandersCanAttack) {
	DEBUG_FUNCTION("AttackMA.cpp", "pickCommanderCanAttack(commSPTRList)");

	LOG::PRINT("The following number of commanders can attack the target: " +
		 std::to_string(commandersCanAttack.size()) + "\n");


	for (commSPTR commander : commandersCanAttack) { commander->printNameLevel(); }
	
	std::string commanderName = getInputText("Enter the name of the commander you would like to select: ", {});
	if (this->hasCommander(commanderName)) { return getCommander(commanderName); }

	//If participant doesn't have commander, recurse until it does
	LOG::ERROR("Invalid commander selected... please try again...\n");
	pickCommanderAttack(commandersCanAttack);

	//not all control paths return a value
	return nullptr;
}

void Participants::playerCommitAttack(provSPTR defendingProvince,  commSPTR attackingCommander) { 
	DEBUG_FUNCTION("AttackMA.cpp", "playerCommitAttack(provSPTR, commSPTR)");

	std::vector<commSPTR> defendingCommanders = defendingProvince->getAllCommanders(); 
	
	constArrayRef preAttackResources = attackingCommander->getAllResources();

	for (commSPTR defendingCommander : defendingCommanders) {
		//Add implementation
	}

	commSPTR defendingCommander = defendingCommanders[0]; 

	int attackerCP = attackingCommander->getCombatPower();  
	int defendingCP = defendingCommander->getCombatPower(); 
	

	ipair lostCPPair = determineLostCP(attackerCP, defendingCP); 
	int attackerLostCP = lostCPPair.first;
	int defenderLostCP = lostCPPair.second;

	i5array troopsLost = { 0, 0, 0, 0, 0 };
	i5array injuredTroops = { 0, 0, 0, 0, 0 };

	calculateTroopsLost(attackingCommander, attackerLostCP, troopsLost, 0);

	//Fix this later
	TROOP::TroopTypes type = GUARDS; 
	int troopTier = 1;

	for (int x = 0; x < 5; x++) {
		injuredTroops[x] = troopsLost[x] / (2 * enemyDifficulty);
		troopsLost[x] -= injuredTroops[x];
	}

	troopsArray injuredTroopsTemp = {}, troopsLostTemp = {};//Fix this later

	//Super scuffed check this stuff out
	attackingCommander->mutateTroop(INJURED, type, injuredTroopsTemp, ALL, INCREASE, NULL);
	attackingCommander->mutateTroop(LOST, type, troopsLostTemp, ALL, INCREASE, NULL);

	LOG::PRINT("    Results:\n\n");
	LOG::PRINT("Resources gained: ", LOG::BLUE);

	i5array oldResources = {};///////////////////
	printResources(mutateArray(attackingCommander->getAllResources(), oldResources, DECREASE));
	attackingCommander->printResources();
	casualtyReport(troopsLost, injuredTroops);

	char viewAllArmyStats = ' ';
	char repeatViewAllArmyStats = 'N';
	std::string viewAllArmyStatsString;

	defendingProvince->addCommander(*attackingCommander);

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
void Participants::calculateTroopsLost(commSPTR commander, int lostCombatPower, constArrayRef troopsLost, int troopIndex) {
	/*DEBUG_FUNCTION("AttackMA.cpp", "calculateTroopsLost(commSPTR, int, constArrayRef, int)");

	//Have to implement Troop functionality before doing this
	//int troopPresent = commander->getTroop(REGULAR, troopIndex, SINGLE)[0];
	int troopsPresent;
	int troopCP = TROOPS_CP[troopIndex];

	//If lostCP > 16
	if (lostCombatPower - 16 > 0) {
		if (troopPresent >= 16 / troopCP) {
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
*/
}


void Participants::battleCalculationsTwo(constINT lostCombatPower, i5array troopsLost, int troopIndex, commSPTR attackingCommander) {
	/*
	DEBUG_FUNCTION("AttackMA.cpp", "battleCalculationsTwo(constINT, i5array, int, commSPTR)");

	partSPTR playerParticipant = Participants::participantsVector.at(currentParticipantIndex);

	int z = abs(4 - troopIndex);

	for (int b = 0; b < TROOPS_CP[z]; b++) {
		if (attackingCommander->getAllTiersOfTroop(REGULAR, 5, SINGLE)[0] > 0) {
			b = TROOPS_CP[z];
		}
		else {
			if (lostCombatPower > 0) {
				lostCombatPower -= TROOPS_CP[troopIndex];
				troopsLost[troopIndex]++;
				attackingCommander->mutateTroop(REGULAR, troopIndex, {1}, SINGLE, DECREASE);
				attackingCommander->mutateTroop(LOST, troopIndex, {1}, SINGLE, INCREASE);
			}
			else
				b = TROOPS_CP[z];
		}
	}
	*/
}

ipair Participants::determineLostCP(int attackerCP, int defendingCP) { 
	//For debugging
	DEBUG_FUNCTION("AttackMA", "determineLostCP");

	int higherCP, lowerCP = 0;
	higherCP = defendingCP;
	lowerCP = attackerCP;


	if (attackerCP > defendingCP) { std::swap(higherCP, lowerCP); }

	int difference = attackerCP / defendingCP;
	int differenceInverse = 1 / difference;

	auto calcLostCP = [](int whichCP, int diffInv) { return (whichCP * diffInv) / 2; };

	int attackerLostCP = calcLostCP(defendingCP, differenceInverse);   
	int defenderLostCP = calcLostCP(attackerCP, differenceInverse);  

	//Add functionality so that there have to be some amount of CP lost; if no CP is lost, then will just repeat forever
	if (attackerLostCP == 0) { attackerLostCP = 1; }
	if (defendingCP == 0) { defendingCP = 1; }

	return std::make_pair(attackerLostCP, defenderLostCP);
}

void Participants::casualtyReport(constArrayRef troopsLost, constArrayRef injuredTroops) {
	//For debugging
	DEBUG_FUNCTION("AttackMA", "casualtyReport");

	std::cout << "\nTroops casualties: \n";
	/*print out deaths*/
	for (int x = 0; x < 5; x++) {
		std::cout << TROOP::TROOP_NAMES[x] << " lost: " << troopsLost[x] << std::endl;
	}
	std::cout << std::endl;

	/*print out deaths*/
	for (int x = 0; x < 5; x++) {
		std::cout << TROOP::TROOP_NAMES[x] << " injured: " << injuredTroops[x] << std::endl;
	}
	std::cout << std::endl;
}