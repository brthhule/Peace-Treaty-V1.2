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

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER
#include PARTICIPANTS_HEADER
#include COMMANDERS_HEADER
#include DATABASE_HEADER
#include INF_HEADER
#include INPUT_HEADER
#include PLAYER_ACTION_HEADER

void startOrResumeGame();
void resumeGame();
void startGame();
int generateNewContinent(int pNum);
void gamePlay();
void endScreen();

int getContinentInformation();

using namespace INF;

Database db;

int main()/*main code*/
{
	//For debugging
	INF::debugFunction("main, main");

	INF::CPUNum = std::thread::hardware_concurrency();

	startOrResumeGame();
	gamePlay();
}
void startOrResumeGame() {
	std::string path = "C:\\Users\\Brennen\\Source\\Repos\\brthhule\\Peace-Treaty-V1.2\\Peace Treaty V1.2\\Units\\Misc\\TxtFiles\\Synopsis.txt";

	//srand((unsigned int)time(0));
	INF::printFile(path);
	char startOrResume = Input::getOptionPrompt(INTRODUCTION).at(0);

	switch (startOrResume) {
		case 'R':
			resumeGame();
			break;
		case 'S': {
			INF::enterAnything(1);
			INF::clearScreen();
			std::cout << "New game started...\n\n";
			// std::cout << "What is your kingdom name? " << RED;
			// std::getline(std::cin, kingdomName);
			// std::cout << WHITE << "The kingdom of " << RED << kingdomName << WHITE << " has been created! \n\n";
			startGame();
			break;
		}
		case 'H':
		{
			INF::showHelp(3);
			main();
			break;
		}
	}

	INF::enterAnything(1);
	INF::clearScreen();
}
void resumeGame() /*download data from previous game fix this*/
{
	//For debugging
	INF::debugFunction("main, resumeGame");

	std::string gameCode;
	std::cout << "Please enter the game code of your previous game: \033[31m";
	std::getline(std::cin, gameCode);
	std::cout << "\033[0m";
	/*use global variables to figure out code*/
}
void startGame() {
	//For debugging
	INF::debugFunction("main, startGame");
	int pNum = getContinentInformation();
	int players = generateNewContinent(pNum);
	db.initializeParticipants(pNum, players);
	std::cout << "Created participants";
}
int getContinentInformation() {
	//For debugging
	debugFunction("main, getContinentInformation");

	std::string text = "What continent size do you want to play on?\n- 5 (Recommended for mobile devices)\n- 10 (Medium-sized map)\n- 15 (Full experienced, recommended for a monitor)";
	//"What continent size do you want to play on? (5, 10, 15) "
	std::string input = Input::getInputText(text, { "5", "10", "15" });
	INF::continentSize = std::stoi(input);
	//int *thing = db.getContinentSizePointer();
	//continentSize = *thing;
	INF::enterAnything(1);
	INF::clearScreen();

	std::cout << "Continent size " << getColor(RED) << INF::continentSize << getColor(RESET) << " created..\n\n";

	int pNum = std::stoi(Input::getInputText("How many AI kingdoms will you fight? (1, 2, 3) ", { "number", "1", "2", "3" }));
	std::cout << getColor(RED) << pNum << getColor(WHITE) << " opponent kingdoms generated... \n\n";
	INF::enterAnything(1);
	INF::clearScreen();

	maxCommanders = continentSize;

	INF::enemyDifficulty = std::stoi(Input::getInputText("What gameplay difficulty do you want (1-3): ", { "number","1","2","3" }));
	INF::enterAnything(1);
	INF::clearScreen();
	std::cout << "Gameplay difficulty " << getColor(RED) << INF::enemyDifficulty << getColor(WHITE) << " selected. \n\n";

	return pNum;
}
int generateNewContinent(int pNum) {
	//For debugging
	INF::debugFunction("main, generateNewContinent");

	std::cout << "Create map...\n";
	db.createMap();

	std::vector<std::string> howManyPlayers;
	for (int x = 1; x <= 3; x++) {
		howManyPlayers.push_back(std::to_string(x));
	}


	int players = std::stoi(Input::getInputText("How many human players are there (1/2/3); 1 is recommended for single player experience): ", howManyPlayers));

	INF::clearScreen();

	std::cout << getColor(RED) << players << getColor(WHITE) << " players initialized...\n\n";
	pNum += players;
	std::cout << "pNum: " << pNum << std::endl;
}


void gamePlay() {
	//For debugging
	INF::debugFunction("main, gamePlay");

	bool gameEnd = false;

	//Create vector to copy the list of participants from the database
	std::vector<Participants>* participantsPtr = db.getParticipantsList();
	std::vector <partSPTR> participantsPtr = db.getParticipantsList();

	//Iterate through partiicpants by reference
	for (int x = 0; x < (signed)participantsPtr->size(); x++)
	{
		partSPTR newParticipant = participantsPtr->at(x);
		//If the current participant is alive
		if (newParticipant->isAlive())
		{
			try {
				newParticipant->initialDecision();
			} catch (...) {
				std::cout << "Something went wrong, error occurred. Restarting player turn.";
				x--;
			}

		}
	}
	INF::turn++;
	db.updateTurnResources();

	//Check game end
	//If there are more than one players, keep playing
	int participantsAlive = 0;
	std::vector<Participants>* list = db.getParticipantsList();
	for (Participants newParticipant : *list) {
		if (newParticipant.isAlive() == true) {
			participantsAlive++;
		}
	}

	if (participantsAlive > 1) {
		try {
			gamePlay(); 
		} catch (...) {
			println("Didn't work, try agian");
		}
		
	}

	endScreen();
}

//Call this function when all winning condition has been met
void endScreen() {
	//For debugging
	INF::debugFunction("main, endScreen");

	std::vector<Participants>* participantsListCopy = db.getParticipantsList();
	partSPTR currentParticipant = new Participants;

	for (int x = 0; x <= (signed)participantsListCopy->size(); x++) {
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

