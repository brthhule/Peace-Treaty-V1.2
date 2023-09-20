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
#include <unordered_map>


//Player infrastructure
#include "Units/Provinces.h"
#include "Units/Participants.h"
#include "Units/CommanderProfile.h"
#include "Units/Database.h"

//Miscellaneous
#include "Misc/OtherFunctions.h"
#include "Misc/ConstValues.h"
#include "Misc/LinkedList.h"


//Main Actions
#include "PlayerAction.h"



//Linked lsit number, province address

#define UNIT_AMOUNT 5
#define RED "\033[31m"
#define WHITE "\033[0m"

char introduction();
void resumeGame();
void startGame();
void generateNewContinent(int pNum);
void gamePlay();
void endScreen();

void AITurn();
/*Miscellaneous*/
OtherFunctions OF;

/*other important stuff*/
int *continentSize;
int enemyDifficulty = 0;


using namespace CV;

Database db;



int main()/*main code*/
{
	OF.debugFunction("main, main");
	srand((unsigned int)time(0));
	char startOrResume = introduction();

	switch (startOrResume)
	{
	case 'R':
		resumeGame();
		break;
	case 'S':
	{
		OF.clearScreen();
		std::cout << "New game started...\n\n";
		// std::cout << "What is your kingdom name? " << RED;
		// std::getline(std::cin, kingdomName);
		// std::cout << WHITE << "The kingdom of " << RED << kingdomName << WHITE << " has been created! \n\n";
		startGame();
		break;
	}
	case 'H':
	{
		OF.showHelp(3);
		main();
		break;
	}
	}

	// for (Participants thingy: participantsList)
	//   std::cout << "Participant index: " << thingy.getParticipantIndex() << std::endl;

	OF.enterAnything();
	OF.clearScreen();

	gamePlay();
}
char introduction()/*introduce player to game synopsis*/
{
	OF.debugFunction("main, introduction");
	OF.printFile("TxtFiles\\Synopsis.txt");
	return OF.getOption(3);
}
void resumeGame() /*download data from previous game fix this*/
{
	OF.debugFunction("main, resumeGame");
	std::string gameCode;
	std::cout << "Please enter the game code of your previous game: \033[31m";
	std::getline(std::cin, gameCode);
	std::cout << "\033[0m";
	/*use global variables to figure out code*/
}
void startGame()
{
	OF.debugFunction("main, startGame");
	std::string text = "What continent size do you want to play on?\n- 5 (Recommended for mobile devices)\n- 10 (Medium-sized map)\n- 15 (Full experienced, recommended for a monitor)\nEnter the number here: ";
	//"What continent size do you want to play on? (5, 10, 15) "
	std::string input = OF.getInput(false, -1, text, {"5", "10", "15" }, true, false);
	db.setContinentSize(std::stoi(input));
	continentSize = db.getContinentSizePointer();
	OF.clearScreen();

	std::cout << "Continent size " << RED << db.getContinentSize() << WHITE << " created..\n\n";

	int pNum = std::stoi(OF.getInput(false, -1, "How many AI kingdoms will you fight? (1, 2, 3) ", { "number", "1", "2", "3" }, true, false));
	std::cout << RED << pNum << WHITE << " opponent kingdoms generated... \n\n";
	OF.clearScreen();
	db.setMaxCommanders(continentSize);

	enemyDifficulty = std::stoi(OF.getInput(false, -1, "What gameplay difficulty do you want (1-3): ", { "number","1","2","3" }, true, false));
	OF.clearScreen();
	std::cout << "Gameplay difficulty " << RED << enemyDifficulty << WHITE << " selected. \n\n";

	generateNewContinent(pNum);
}
void generateNewContinent(int pNum)
{
	OF.debugFunction("main, generateNewContinent");
	std::cout << "Create map...\n";
	db.createMap();

	std::vector<std::string> howManyPlayers;
	for (int x = 1; x <= 3; x++)
		howManyPlayers.push_back(std::to_string(x));

	int players = std::stoi(OF.getInput(false, -1, "How many human players are there (1/2/3; 1 is recommended for single player experience): ", howManyPlayers, true, false));
	OF.clearScreen();

	std::cout << RED << players << WHITE << " players initialized...\n\n";
	pNum += players;
	std::cout << "pNum: " << pNum << std::endl;

	db.initializeParticipants(pNum, players);
	std::cout << "Created participants";
}


void endScreen()
{
	OF.debugFunction("main, endScreen");
	for (int x = 0; x <= (int)participantsList.size(); x++)
	{
		if (participantsList[x].isAlive())
		{
			std::cout << "Congratulatios to player " << participantsList[x].getKingdomName() << " for winning. You have successfully conquered your enemies and now reign as the Emperor! \n";

		}
	}
	char playAgain = OF.getInput(false, -1, "Play again? (Y/N) ", { "letter", "Y", "N" }, false, false).at(0);
	
	
	if (playAgain == 'Y')
	{
		main();
	}
}

void gamePlay()
{
	OF.debugFunction("main, gamePlay");
	bool gameEnd = false;

	//Create vector to copy the list of participants from the database
	std::vector<Participants*> copyVector = db.getParticipantsList();

	//Iterate through partiicpants by reference
	for (Participants* newParticipant : copyVector)
	{
		//If the current participant is alive
		if (newParticipant->isAlive())
		{
			//Create new PlayerAction object
			PlayerAction newPlayerAction(newParticipant);
			//Run through PlayerAction
			newPlayerAction.initialDecision();
		}
	}
	turn++;
	db.updateTurnResources();

	//Check game end
	//If there are more than one players, keep playing
	int participantsAlive = 0;
	for (Participants newParticipant : participantsList)
		if (newParticipant.isAlive() == true)
			participantsAlive++;

	(participantsAlive > 1) ? gamePlay() : OF.nothing();

	endScreen();
}

