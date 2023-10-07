#include "MapMA.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
#define part() getParticipantIndex()



MapMA::MapMA() { participant = db.getCurrentParticipant();}

void MapMA::viewPlayerMap() {
  char whatToDo = ' ';
	
  if (participant->isPlayer())
  {
    db.showMap();
    println("Welcome to the View Map action menu");

		whatToDo = Input::getOptionPrompt(VIEW_PLAYER_MAP).at(0);
  }
  else
    whatToDo = 'P';
  

  switch (whatToDo) {
  case 'P': {
		OF::clearScreen();
		std::cout << "Selecting a province...\n";
    Provinces *province = participant->getYourProvince(1);
		
    if (province->deleteStatus() != true) {
      selectUnitOriginal(province);
    }
    viewPlayerMap();
    break;
  }
  case 'H': {
    OF.showHelp(8);
    viewPlayerMap();
    break;
  }
  default:
    println("Returning to the previous menu.");
    std::cout << std::endl;
    break;
  }
}

Participants *MapMA::getParticipant() { return participant; }

void MapMA::selectUnitOriginal(Provinces *selectedProvince) {
	prov = selectedProvince;
  if (prov->part() == participant->getParticipantIndex()) // If belongs to participant
  {
    selectPlayerProvince();
  }
	else if (prov->part() == -1) // If empty province
  {
    if (prov->commandersNum() >
        0) // If there are more than 0 commnaders
    {
			//If the commander here is yours
      if (prov->getCommander(0)->getParticipantIndex() == participant->getParticipantIndex())
      {
        playerUnitAction(prov);
      } 
			//If the commander here is an emey
			else {
        selectEnemyAction();
      }
    }
		
  } 
	else // If enemy province
  {
    selectEnemyProvince(prov);
  }
}
void MapMA::selectPlayerProvince() {
  if (prov->isCapital()) {
    print("This is your capital province ");
  } else {
    print ("This is one of your provinces ");
    ;
  }
  std::cout << std::endl << std::endl;

  char selectPlayerCapitalAction = Input::getOptionPrompt(SELECT_PLAYER_PROVINCE).at(0);

  switch (selectPlayerCapitalAction) {
  case 'B': {
    prov->playerBuildFunction();
    break;
  }
  case 'T': {
    TrainMA newTrainMA;
    break;
  }
  case 'M':
    std::cout << "Returning to the map..." << std::endl;
    std::cout << std::endl;
    break;
  }
}


void MapMA::selectEnemyProvince(Provinces *newP) {
  Provinces *enemyProvince = newP;
	if (enemyProvince->isCapital()) {
    println("This is an enemy capital province ");
  } else {
    println("This is one of the enemy's provinces");
  }

  println("\n\nWelcome to the Enemy Provinces Action Selection menu ");
	
  char selectUnitEnemyProvinceChar = OF.getOption(10);

  switch (selectUnitEnemyProvinceChar) {
  case 'A': {
    AttackMA newAttackMA(enemyProvince, participant);
		//selectEnemyProvince(enemyProvince);
    break;
  }
  case 'S': {
    ScoutMA newScout(participant, enemyProvince);
    newScout.selectTarget();
		//selectEnemyProvince(enemyProvince);
    break;
  }
  case 'V': {
    if (enemyProvince->getScoutReportTurn() != -1)
      if (OF.getInput(false, -1, "View scout log for this province? (Y/N) ", {"Y", "N"}, false, false).at(0) ==
          'Y')
        scoutLogFunction(enemyProvince);
		
		selectEnemyProvince(enemyProvince);
    break;
  }
  case 'M':
    std::cout << "Returning to the menu... " << std::endl;
    break;
  }
}

//Get the commander that's here 
void MapMA::playerUnitAction(Provinces *newP) {
	Provinces *newProvince = newP;
  println("This is one of your armies ");
	
	switch (Input::getOptionPrompt(PLAYER_UNIT_ACTION).at(0)) {
	case 'P': //Move this unit
	{
		playerUnitActionP(newProvince);
		break;
	}
	case 'H':
	{
		OF.showHelp(2);
		playerUnitAction(newProvince);
		break;
	}
	case 'M':
		std::cout << "Returning to menu... \n" ;
		break;
	}
}

void MapMA::playerUnitActionP(Provinces *newP)
{
	Provinces *newProvince = newP;
	std::cout << "The following commanders are at this province: \n";
	newProvince -> printCommanders();
	// find index of commander unit, fix this
	std::string commanderName = " ";
	std::cout << "\nEnter the name of the commander you would like to select: ";
	getline(std::cin, commanderName);
	if (newProvince->hasCommander(commanderName) == false)
	{
		std::cout << "Invalid name entered; please try again...";
		playerUnitAction(newProvince);
	}
	
	if (participant->getCommander(commanderName)->hasMovedQuestion() == false) {
		Mobility newMobility (commanderName, participant);
		newMobility.moveUnitOne(); /*fix this*/
		playerUnitAction(newProvince);
	} 
	else
	{
		println("This unit has already moved this turn... returning to the View Map action menu \n");
	}
}




void MapMA::selectEnemyAction() /*Add implementation*/
{
  std::cout << "This is an enmy army. \n";

	switch (Input::getOptionPrompt(SELECT_ENEMY_ACTION).at(0))
	{
		case 'A':
			break;
		case 'S':
			break;
		case 'H':
			break;
		case 'M':
			break;
	}
}

void MapMA::scoutLogFunction(Provinces* enemyProvince) {
  char repeatScoutLog = 'N';
  char whatReportChar;

  std::cout << "Turn of scout report: " << enemyProvince->getScoutReportTurn() << "; Level of report: " << enemyProvince -> getScoutLogTurnLevel() << "\n\n";
  do 
	{
    whatReportChar = Input::getOptionPrompt(WHAT_REPORT).at(0);//add functionality for WHAT_REPORT
    provinceReportLog(whatReportChar, enemyProvince);
  } while (repeatScoutLog == 'Y');
}
void MapMA::provinceReportLog(char whatReportChar, Provinces* enemyProvince) {
  int totalGarrisonedCP = 0;
  switch (whatReportChar) {
  case 'G': {
    std::cout << "Garrisoned troops: " << std::endl;
    for (int x = 0; x < 5; x++) {
      std::cout << "-" << CV::TROOP_NAMES[x] << ": "
                << enemyProvince->getTroopsPresent(x)
                << std::endl;
      totalGarrisonedCP +=
          (enemyProvince->getTroopsPresent(x) *
           CV::TROOPS_CP[x]);
    }
    std::cout << "Total Garrison Combat Power: " << totalGarrisonedCP << std::endl
              << std::endl;
    break;
  }
  case 'R':
    enemyProvince->printResources();
    break;
  case 'B':
    enemyProvince->printBuildingStats();
    break;
  case 'M':
    break;
  }
}
