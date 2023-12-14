#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include PARTICIPANTS_HEADER

void Participants::initialDecision() {
	//For debugging
	INF::debugFunction("PlayerAction, initialDecision");

	bool goToNextTurn = false;

	INF::enterAnything(1);
	INF::clearScreen();

	char courseOfAction = ' ';

	if (this->isPlayer() == true)
	{
		std::cout << "Turn: " << INF::turn << std::endl;
		std::cout << "Player " << participant->getKingdomName() << "'s move...";
		std::cout << "\n\nWelcome to the Main Action menu \n\n\n";

		this->showMap();

		courseOfAction = Input::getOptionPrompt(PLAYER_ACTION).at(0);
	} else {
		// If the participant is the AI
		courseOfAction = randomAction();
	}

	INF::enterAnything(1);
	INF::clearScreen();

	switch (courseOfAction) {
		case 'B': {
			provSPTR newProvince = participant->pickYourProvince(1);
			newProvince->playerBuildFunction();
			break;
		}
		case 'T': {
			this->TrainMAFunction();
			break;
		}
		case 'S':
			this->viewStats();
			break;
		case 'U': {
			this->viewPlayerMap();
			break;
		}
		case 'D': {
			this->armyDeploymentMF();
			break;
		}
		case 'N':
			goToNextTurn = true;
			break;
		case 'H': {
			INF::showHelp(4);
			break;
		}
		case 'P': {
			char pauseGameQuestionChar = Input::getInputText("Pausing the game will end this session of gameplay. Proceed? (Y/N): ", { "Y", "N" }).at(0);

			if (pauseGameQuestionChar == 'Y')
				pauseGame();

			std::cout << "Returning to the Main menu... \n";
		}
	}
	if (goToNextTurn == false)
		initialDecision();
}

char Participants::randomAction() {
	//For debugging
	INF::debugFunction("PlayerAction, randomAction");

	int randomNumber = rand() % 6; // Random number 0 to 5 (inclusive)
	std::vector<char> newVector = { 'B', 'T', 'S', 'U', 'D', 'N' };
	return newVector[randomNumber];
}


void Participants::pauseGame() {
	//For debugging
	INF::debugFunction("PlayerAction, pauseGame");

	std::string gameCode;
	gameCode += INF::continentSize;

	for (int x = 0; x < INF::continentSize; x++) {
		for (int y = 0; y < INF::continentSize; y++) {
			//gameCode += participant->getSystemProvince({x, y}).getParticipantIndex();
		}
	}
	std::cout << "Game ended... \nHere is your game code (Copy this code and "
		"paste it when using the 'Resume Game' functionality): "
		<< gameCode << "\n\n";
}