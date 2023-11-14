#include "MapMA.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

MapMA::MapMA() { 
	//For debugging
	CV::debugFunction("MapMA, MapMA");

	participant = db.getCurrentParticipant();
	
	//Default
	pIndex = -1;
}

//View the map
void MapMA::viewPlayerMap() {
	//For debugging
	CV::debugFunction("MapMA, viewPlayerMap");

	char whatToDo = ' ';

	//If the participant is a player
	if (participant->isPlayer()) {
		Participants* tempParticipant = new Participants();
		tempParticipant->showMap();
		println("Welcome to the View Map action menu");
		whatToDo = Input::getOptionPrompt(VIEW_PLAYER_MAP).at(0);
		delete tempParticipant;
	} 
	//If the participant is an AI
	else {

	}

	/*- Pick a province (P)
	Options:P*/
	switch (whatToDo) {
		case 'P': {
			CV::clearScreen();
			std::cout << "Selecting a province...\n";
			//The user selects a province
			Provinces* province = participant->getYourProvince(1);

			if (province != NULL){
				selectUnitOriginal(province);
			}

			//Recurse
			viewPlayerMap();
			break;
		}
		case 'H': {
			CV::showHelp(8);

			//Recurse
			viewPlayerMap();
			break;
		}
		default: {
			//Return to previous menu
			println("Returning to the previous menu.\n");
			break;
		}
	}
}

Participants* MapMA::getParticipant() { 
	//For debugging
	CV::debugFunction("MapMA, getParticipant");

	return participant; 
}

void MapMA::selectUnitOriginal(Provinces* province) {
	//For debugging
	CV::debugFunction("MapMA, selectUnitOriginal");

	int participantIndex = province->getParticipantIndex();

	// If belongs to current participant
	if (participantIndex == participant->getParticipantIndex()) {
		selectPlayerProvince(province);
	}
	// If empty province
	else if (participantIndex == -1) {
		// If there are more than 0 commnaders

		//if (province->fogofWar) Add implementation
		if (province->commandersNum() > 0) 
		{
			//Add scout information, fog of war
			//If the commander here is yours
			if (province->commandersNum() > 0) {
				if (province->getCommander(0)->getParticipantIndex() == participant->getParticipantIndex()) {
					playerUnitAction(province);
				}
				//If the commander here is an enemy
				else {
					selectEnemyAction();
				}
			}
		}

	}
	// If enemy province
	else {
		selectEnemyProvince(province);
	}
}

//You selected one of your provinces
void MapMA::selectPlayerProvince(Provinces *province) {
	//For debugging
	CV::debugFunction("MapMA, selectPlayerProvince");

	if (province->isCapital()) {
		print("This is your capital province ");
	}
	else {
		print("This is one of your provinces ");
	}
	std::cout << "\n\n";

	//Get option
	char selectPlayerCapitalAction = Input::getOptionPrompt(SELECT_PLAYER_PROVINCE).at(0);

	/*- Build infrastructure (B)
		- Train Troops (T)
		Options:B,T*/
	switch (selectPlayerCapitalAction) {
	case 'B': {
		province->playerBuildFunction();
		break;
	}
	case 'T': {
		TrainMA newTrainMA;
		break;
	}
	case 'M':
		std::cout << "Returning to the map...\n\n";
		break;
	}
}

//You selected an enemy province
void MapMA::selectEnemyProvince(Provinces* newP) {
	//For debugging
	CV::debugFunction("MapMA, selectEnemyProvince");

	Provinces* enemyProvince = newP;
	if (enemyProvince->isCapital()) {
		println("This is an enemy capital province ");
	}
	else {
		println("This is one of the enemy's provinces");
	}

	println("\n\nWelcome to the Enemy Provinces Action Selection menu ");

	char selectUnitEnemyProvinceChar = Input::getOptionPrompt(SELECT_ENEMY_PROVINCE).at(0);

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
		//ask whether or not to view scout log
		break;
	}
	case 'M':
		std::cout << "Returning to the menu... " << std::endl;
		break;
	}
}


/*
You selected an empty province that your commander is in
- Move this unit (P)
- Capture this province (C)*/
void MapMA::playerUnitAction(Provinces* newP) {
	//For debugging
	CV::debugFunction("MapMA, playerUnitAction");

	Provinces* newProvince = newP;
	println("This is one of your armies ");

	switch (Input::getOptionPrompt(PLAYER_UNIT_ACTION).at(0)) {
		//Move this unit 
	case 'P': {
		playerUnitActionP(newProvince);
		break;
	}
	case 'C': {
		//Add implementation
	}
	case 'H': {
		CV::showHelp(2);
		playerUnitAction(newProvince);
		break;
	}
	case 'M':
		std::cout << "Returning to menu... \n";
		break;
	}
}

//Selected 
void MapMA::playerUnitActionP(Provinces* newP)
{
	//For debugging
	CV::debugFunction("MapMA, playerUnitActionP");

	Provinces* newProvince = newP;
	std::cout << "The following commanders are at this province: \n";
	newProvince->printCommanders();
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
		participant->moveUnitOne(participant->getCommander(commanderName));
		playerUnitAction(newProvince);
	}
	else
	{
		println("This unit has already moved this turn... returning to the View Map action menu \n");
	}
}




void MapMA::selectEnemyAction() /*Add implementation*/
{
	//For debugging
	CV::debugFunction("MapMA, selectEnemyAction");

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

/*void MapMA::provinceReportLog(char whatReportChar, Provinces* enemyProvince) {
  int totalGarrisonedCP = 0;
  switch (whatReportChar) {
  case 'G': {
	std::cout << "Garrisoned troops: " << std::endl;
	for (int x = 0; x < 5; x++) {
		std::cout << "-" << CV::TROOP_NAMES[x] << ": "
			<< enemyProvince->getTroop(REGULAR, x, -1)
				<< std::endl;
	  totalGarrisonedCP +=
		  (enemyProvince-> getTroop(REGULAR, x, -1) *
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
*/