//Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string.h>
#include<stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <time.h>
#include <thread>


//Player infrastructure
#include "Units/Provinces.h"
#include "Units/Participants.h"
#include "Units/CommanderProfile.h"
#include "Units/Database.h"

//Miscellaneous
#include "Misc/OF.h"
#include "Misc/CV.h"
#include "Misc/LinkedList.h"
#include "Input.h"


//Main Actions
#include "PlayerAction.h"

void resumeGame();
void startGame();
void generateNewContinent(int pNum);
void gamePlay();
void endScreen();

using namespace CV;

Database db;




int main()/*main code*/
{
	//For debugging
	OF::debugFunction("main, main");

	CV::CPUNum = std::thread::hardware_concurrency();

	//srand((unsigned int)time(0));
	OF::printFile("TxtFiles\\Synopsis.txt");
	char startOrResume = Input::getOptionPrompt(INTRODUCTION).at(0);

	switch (startOrResume)
	{
	case 'R':
		resumeGame();
		break;
	case 'S':
	{
		OF::clearScreen();
		std::cout << "New game started...\n\n";
		// std::cout << "What is your kingdom name? " << RED;
		// std::getline(std::cin, kingdomName);
		// std::cout << WHITE << "The kingdom of " << RED << kingdomName << WHITE << " has been created! \n\n";
		startGame();
		break;
	}
	case 'H':
	{
		OF::showHelp(3);
		main();
		break;
	}
	}

	OF::enterAnything();
	OF::clearScreen();

	gamePlay();
}
void resumeGame() /*download data from previous game fix this*/
{
	//For debugging
	OF::debugFunction("main, resumeGame");

	std::string gameCode;
	std::cout << "Please enter the game code of your previous game: \033[31m";
	std::getline(std::cin, gameCode);
	std::cout << "\033[0m";
	/*use global variables to figure out code*/
}
void startGame()
{
	//For debugging
	OF::debugFunction("main, startGame");

	std::string text = "What continent size do you want to play on?\n- 5 (Recommended for mobile devices)\n- 10 (Medium-sized map)\n- 15 (Full experienced, recommended for a monitor)\nEnter the number here: ";
	//"What continent size do you want to play on? (5, 10, 15) "
	std::string input = Input::getInputText(text, {"5", "10", "15" });
	CV::continentSize = std::stoi(input);
	//int *thing = db.getContinentSizePointer();
	//continentSize = *thing;
	OF::clearScreen();

	std::cout << "Continent size " << RED << CV::continentSize << WHITE << " created..\n\n";

	int pNum = std::stoi(Input::getInputText("How many AI kingdoms will you fight? (1, 2, 3) ", { "number", "1", "2", "3" }));
	std::cout << RED << pNum << WHITE << " opponent kingdoms generated... \n\n";
	OF::clearScreen();
	db.setMaxCommanders(CV::continentSize);

	CV::enemyDifficulty = std::stoi(Input::getInputText("What gameplay difficulty do you want (1-3): ", { "number","1","2","3" }));
	OF::clearScreen();
	std::cout << "Gameplay difficulty " << RED << CV::enemyDifficulty << WHITE << " selected. \n\n";

	generateNewContinent(pNum);
}

void generateNewContinent(int pNum)
{
	//For debugging
	OF::debugFunction("main, generateNewContinent");

	std::cout << "Create map...\n";
	db.createMap();

	std::vector<std::string> howManyPlayers;
	for (int x = 1; x <= 3; x++)
		howManyPlayers.push_back(std::to_string(x));

	int players = std::stoi(Input::getInputText("How many human players are there (1/2/3; 1 is recommended for single player experience): ", howManyPlayers));
	OF::clearScreen();

	std::cout << RED << players << WHITE << " players initialized...\n\n";
	pNum += players;
	std::cout << "pNum: " << pNum << std::endl;

	db.initializeParticipants(pNum, players);
	std::cout << "Created participants";
}

//Call this function when all winning condition has been met
void endScreen()
{
	//For debugging
	OF::debugFunction("main, endScreen");

	std::vector<Participants>* participantsListCopy = db.getParticipantsList();
	Participants* currentParticipant = new Participants;

	for (int x = 0; x <= participantsListCopy->size(); x++) {
		if (currentParticipant->isAlive()) {
			currentParticipant = &participantsListCopy->at(x);
		}
	}

	std::cout << "Congratulations to player " << currentParticipant->getKingdomName() << " for winning. You have successfully conquered your enemies and now reign as the Emperor! \n";

	char playAgain = Input::getInputText("Play again? (Y/N) ", { "letter", "Y", "N" }).at(0);
	
	
	if (playAgain == 'Y') {
		main();
	}
}

void gamePlay()
{
	//For debugging
	OF::debugFunction("main, gamePlay");

	bool gameEnd = false;

	//Create vector to copy the list of participants from the database
	std::vector<Participants> *copyVector = db.getParticipantsList();

	//Iterate through partiicpants by reference
	for (int x = 0; x < copyVector->size(); x++)
	{
		Participants newParticipant = copyVector->at(x);
		//If the current participant is alive
		if (newParticipant.isAlive())
		{
			//Create new PlayerAction object
			PlayerAction newPlayerAction;
			//Run through PlayerAction
			newPlayerAction.initialDecision();
		}
	}
	CV::turn++;
	db.updateTurnResources();

	//Check game end
	//If there are more than one players, keep playing
	int participantsAlive = 0;
	for (Participants newParticipant : *db.getParticipantsList()) {
		if (newParticipant.isAlive() == true) {
			participantsAlive++;
		}
	}
		
	if (participantsAlive > 1) {
		gamePlay();
	}

	endScreen();
}

