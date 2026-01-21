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
#include <memory>

#include "..\Peace-Treaty-V1.2\Support\Paths.h"
//#include INF_HEADER  
#include PARTICIPANTS_HEADER
#include PROVINCES_HEADER
#include INPUT_HEADER
#include COMMANDERS_HEADER
#include PLAYER_ACTION_HEADER
#include TROOP_HEADER
#include ARMY_OVERVIEW_MA_HEADER
#include INF_HEADER
#include MAP_HEADER
#include MOBILITY_HEADER
#include TUI_HEADER

using namespace std::literals::string_literals;


void startOrResumeGame();
void resumeGame();
void startNewGame();
int generateNewContinent(int pNum);
void gamePlay();
void endScreen();

int getContinentInformation();

/*main code*/
int main()
{
	DEBUG_FUNCTION("Peace-Treaty-V1.2.cpp", "int main()");
	INF::CPUNum = std::thread::hardware_concurrency();
	Tui::tui.initialize(); 
	Tui::debug("Peace Treaty V1.2.cpp, main");

	startOrResumeGame();
	gamePlay();
	DEBUG_FUNCTION_END; 
}

void startOrResumeGame() {
	DEBUG_FUNCTION("Peace-Treaty-V1.2.cpp", "void startOrResumeGame()");
	Tui::debug("Peace Treaty V1.2.cpp, startOrResumeGame");
	//std::string path = "../Peace Treaty V1.2\\Support\\TxtFiles\\Synopsis.txt";
	std::string path = "C:/Users/Brennen/Source/Repos/brthhule/Peace-Treaty-V1.2/Peace-Treaty-V1.2/Support/TxtFiles/Synopsis.txt";

	//srand((unsigned int)time(0));
	INF::printFile(path);
	Tui::tui.printScreen();
	std::cout << "\n";
	char startOrResume = Input::getPrompt(Input::INTRODUCTION).at(0);

	std::string startOrResumeString(1, startOrResume);
	LOG::DEBUG("startOrResume char: " + startOrResumeString + "\n"); 

	switch (startOrResume) {
		case 'R':
			resumeGame();
			break;
		case 'S': {
			LOG::DEBUG("Starting new game\n");
			INF::enterAndClear(1);
			std::cout << "New game started...\n\n";
			startNewGame();
			break;
		}
		case 'H': {
			INF::showHelp(3);
			main();
			break;
		}
		case '1': {
			std::cout << "Not implemented. Application will close\n";
		}
		case '2': {
			std::cout << "Not implemented. Application will close\n";
		}
		case '3': {
			std::cout << "Not implemented. Application will close\n";
		}
	}

	INF::enterAnything(1);
	INF::clearScreen();
	DEBUG_FUNCTION_END;
}
void resumeGame() /*download data from previous game fix this*/
{
	DEBUG_FUNCTION("Peace-Treaty-V1.2.cpp", "void resumeGame()");

	std::string gameCode;
	std::cout << "Please enter the game code of your previous game: \033[31m";
	std::getline(std::cin, gameCode);
	std::cout << "\033[0m";
	/*use global variables to figure out code*/
	DEBUG_FUNCTION_END;
	return;
}
void startNewGame() {
	DEBUG_FUNCTION("Peace-Treaty-V1.2.cpp", "void startNewGame()"); 
	Tui::debug("Peace Treaty V1.2.cpp, startNewGame"); 

	int humanPlayers = getContinentInformation(); 

	Participants::setHumanPlayers(humanPlayers);
	int allPlayers = generateNewContinent(humanPlayers);

	Participants::initializeParticipants(allPlayers, 0);
	LOG::DEBUGln("Created participants"); 
	
	DEBUG_FUNCTION_END;
	return;
}

int getContinentInformation() {
	DEBUG_FUNCTION("Peace-Treaty-V1.2.cpp", "int getContinentInformation()");
	Tui::debug("Peace Treaty V1.2.cpp, getContinentInformation");

	std::string text = INF::getText("WhatContinentSize");
	//"What continent size do you want to play on? (5, 10, 15) "

	std::string input = Input::getInputText(text, { "5", "10", "15" });
	INF::continentSize = std::stoi(input);
	//int *thing = db.getContinentSizePointer();
	//continentSize = *thing;
	INF::enterAnything(1);
	INF::clearScreen();

	std::string sizeString = std::to_string(INF::continentSize);


	std::cout << "Continent size "s + LOG::EMBED(sizeString, LOG::RED) + 
		" created..\n\n"s;

	text = "How many AI kingdoms will you fight? (1, 2, 3) ";
	std::string pNumString = Input::getInputText(text, { "number", "1", "2", "3" });
	int aiOpponents = std::stoi(pNumString);
	std::cout << LOG::EMBED(pNumString, LOG::RED) + " opponent kingdoms generated... \n\n"; 
	INF::enterAndClear(1);

	TROOP::maxCommanders = INF::continentSize;

	INF::enemyDifficulty = std::stoi(Input::getInputText("What gameplay difficulty do you want (1-3): ", { "number","1","2","3" }));
	INF::enterAndClear(1);

	std::cout << "Gameplay difficulty "s +
		LOG::EMBED(INF::str(INF::enemyDifficulty), LOG::RED) << " selected. \n\n"; 
	
	DEBUG_FUNCTION_END;
	return aiOpponents;
}

/// <summary>
///		Initialies the Map object
/// </summary>
/// <param name="pNum">Number of participants/players</param>
/// <returns>
///		int - number of human players
/// </returns>
int generateNewContinent(int aiOpponents) {
	Tui::debug("Peace Treaty V1.2.cpp, int generateNewContinent(int)");
	//For debugging
	DEBUG_FUNCTION("Peace-Treaty-V1.2.cpp", "generateNewContinent");

	std::cout << "Create map...\n";
	Map::setMap();

	std::vector<std::string> howManyPlayers;
	for (int x = 1; x <= 3; x++) {
		howManyPlayers.push_back(std::to_string(x));
	}


	int players = std::stoi(Input::getInputText(INF::getText("HowManyPlayers"), howManyPlayers));

	INF::clearScreen();

	std::cout << LOG::getColor(LOG::RED) << players << LOG::getColor(LOG::WHITE) << " players initialized...\n\n";
	aiOpponents += players; 
	std::cout << "aiOpponents: " << aiOpponents << std::endl; 
	
	DEBUG_FUNCTION_END;
	return players;
}


void gamePlay() {
	DEBUG_FUNCTION("Peace-Treaty-V1.2.cpp", "void gamePlay()");

	bool gameEnd = false;

	//Iterate through partiicpants by reference
	int participantsNum = Participants::getParticipantsNum();
	for (int index = 0; index < participantsNum; index++) {
		Participants& participant = Participants::getParticipant(index);
		if (!participant.isAlive()) { break; } 

		try { participant.chooseAction(); }  
		catch (...) { LOG::ERROR("Error occurred in player turn"); }
	}

	INF::turn++;
	Map::updateTurnResources(); 

	//Check game end
	//If there are more than one players, keep playing

	if (Participants::getParticipantsAlive() > 1) { 
		try { gamePlay(); } 
		catch (...) { println("Didn't work, try agian");}
	}

	endScreen();
	DEBUG_FUNCTION_END;
}



//Call this function when all winning condition has been met
void endScreen() {
	DEBUG_FUNCTION("Peace-Treaty-V1.2.cpp", "void endScreen()");
	std::string kingdomName = Participants::getRemainingParticipant().getKingdomName();

	std::cout << "Congratulations to player " << kingdomName << " for winning. You have successfully conquered your enemies and now reign as the Emperor! \n"; 

	char playAgain = Input::getInputText("Play again? (Y/N) ", { "letter", "Y", "N" }).at(0);
	Participants::clearParticipantsVector(); 
	if (playAgain == 'Y') { main();}
	DEBUG_FUNCTION_END;
}

