#include "AttackMA.h"

AttackMA::AttackMA(Provinces *defendingProvinceArg, Participants* attackingParticipantArg) {
  // Given a province to attack, see if you can attack with anything nearby
	attackingParticipant = attackingParticipantArg;
  defendingProvince = defendingProvinceArg;
  int DPX = defendingProvince->getCoordinate('X');
  int DPY = defendingProvince->getCoordinate('Y');
  std::vector<CommanderProfile *> commandersCanAttack;

  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      int candidateX = DPX + x;
      int candidateY = DPY + y;
      // check that coordinates are inbound
      if (DPX >= 0 && DPY >= 0 && DPY < continentSize && DPX < continentSize) {
        Provinces *newProvince = &provincesMap[DPX][DPY];
        std::vector<CommanderProfile*> commanderList = newProvince->getAllCommanders();
        for (CommanderProfile* newCommander: commanderList)
          commandersCanAttack.push_back(newCommander);
      }
    }
  }

  if (commandersCanAttack.size() == 0)
    std::cout << "There are no armies available to attack the enemy. Please move an army unit to one of the provinces around the target. \n\n";
  else
    findCommander(commandersCanAttack);
}

AttackMA::AttackMA(Provinces *attackerProvinceArg, Provinces *defenderProvinceArg, Participants *attackingParticipantArg, CommanderProfile *commanderArg) {
  attackingProvince = attackerProvinceArg;
  defendingProvince = defenderProvinceArg;
  attackingParticipant = attackingParticipantArg;
  attackingCommander = commanderArg;
	preAttack();
}

void AttackMA::findCommander(std::vector <CommanderProfile *> commandersCanAttack) {
	std::string commanderName;
  std::cout << "The following commanders can attack the target: \n";
  std::cout << "Amount of commanders: " << commandersCanAttack.size() << std::endl;
  for (int x = 0; x < commandersCanAttack.size(); x++) {
    std::cout << "Commander " << commandersCanAttack[x]->getUnitName() << ", Level: " << commandersCanAttack[x]->getLevel();
  }
	std::cout << "Enter the name of the commander you would like to select: ";
	getline(std::cin, commanderName);
	if (attackingParticipant->hasCommander(commanderName) == false)
		findCommander(commandersCanAttack);
	
	attackingCommander = attackingParticipant -> getCommanderByName(commanderName);
	preAttack();
}

void AttackMA::preAttack()
{
	defendingParticipant = &participantsList[defendingProvince->getParticipantIndex()];
	playerCommitAttack();
	defendingCommanders = defendingProvince -> getAllCommanders();
	oldResources = attackingCommander -> getAllResources();
	playerCommitAttack();
}

void AttackMA::playerCommitAttack() 
{
	CommanderProfile* defendingCommander = defendingCommanders[0];
	int attackerCP = attackingCommander -> getCP();
	int defendingCP = defendingCommander ->getCP();
	int attackerLostCP = 0;
	int defenderLostCP = 0;

	determineLostCP(attackerCP, defendingCP, attackerLostCP, defenderLostCP);

  std::array<int,5> troopsLost = {0, 0, 0, 0, 0};
  std::array<int,5> injuredTroops = {0, 0, 0, 0, 0};

	calculateTroopsLost(attackingCommander, attackerLostCP, troopsLost, 0);
	
	for (int x = 0; x < 5; x++) {
		injuredTroops[x] = troopsLost[x] / (2 * enemyDifficulty);
		troopsLost[x] -= injuredTroops[x];
	}
	attackingCommander->addInjuredTroops(injuredTroops);
	attackingCommander->modifyTroops(troopsLost, false);
	
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
		viewAllArmyStats = OF.getInput("View all army stats? (Y/N) ", {"Y", "N"}, 1).at(0);
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
void AttackMA::calculateTroopsLost(CommanderProfile* commander, int lostCombatPower, std::array<int,5> &troopsLost, int troopIndex) {
	
	int troopPresent = commander -> getTroopsPresent(troopIndex);
	
	int troopCP = CV.TROOPS_CP[troopIndex];

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


void AttackMA::battleCalculationsTwo(int &lostCombatPower, int troopsLost[5], int troopIndex) /*fix this*/
{
  Participants *playerParticipant = &participantsList[currentParticipantIndex];

  int z = abs(4 - troopIndex);

  for (int b = 0; b < CV.TROOPS_CP[z]; b++) {
    if (attackingCommander->getTroopsPresent(5) > 0) {
      b = CV.TROOPS_CP[z];
    } else {
      if (lostCombatPower > 0) {
        lostCombatPower -= CV.TROOPS_CP[troopIndex];
        troopsLost[troopIndex]++;
        attackingCommander->modifySpecificTroop(troopIndex, 1, false);
        attackingCommander->addSpecificTroopLost(troopIndex, 1);
      } else
        b = CV.TROOPS_CP[z];
    }
  }
}

void AttackMA::printResourcesGained()
{
	std::array<int,5> currentResources = attackingCommander->getAllResources();
	std::cout << "Resources gained: \n \033[;34m";

	for (int x = 0; x < 5; x++)
		std::cout << "- " << CV.RESOURCE_NAMES[x] << ": " << currentResources[x] - oldResources[x] <<  "\n\n\033[;0m";
}

void AttackMA::determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP)
{
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
	defenderLostCP = (attackerCP * (1/difference)) / 2;

	//Add functionality so that there have to be some amount of CP lost; if no CP is lost, then will just repeat forever
	if (attackerLostCP == 0)
		attackerLostCP = 1;
	if (defendingCP == 0)
		defendingCP = 1;
}

void AttackMA::casualtyReport(std::array<int,5> troopsLost, std::array<int,5> injuredTroops)
{
    std::cout << std::endl;
    std::cout << "Troops casualties: " << std::endl;
    for (int x = 0; x < 5; x++) /*print out deaths*/
    {
        std::cout << CV.TROOP_NAMES[x] << " lost: " << troopsLost[x] << std::endl;
    }
    std::cout << std::endl;
    for (int x = 0; x < 5; x++) /*print out deaths*/
    {
        std::cout << CV.TROOP_NAMES[x] << " injured: " << injuredTroops[x] << std::endl;
    }
    std::cout << std::endl;
}