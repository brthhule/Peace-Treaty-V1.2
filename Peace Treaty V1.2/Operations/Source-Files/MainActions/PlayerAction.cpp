#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER

using namespace PART;
using namespace Input;

void Participants::chooseAction() {
	DEBUG_FUNCTION("PlayerAction", "chooseAction");
	INF::enterAndClear(1);

	bool goToNextTurn = false;

	//For AI
	char courseOfAction = randomAction();

	//If player
	if (isPlayer()) {
		std::cout << "Turn: " << INF::turn << std::endl;
		std::cout << "Player " << getKingdomName() << "'s move...";
		std::cout << "\n\nWelcome to the Main Action menu \n\n\n";

		showMap();
		courseOfAction = Input::getPrompt(PLAYER_ACTION).at(0); 
	} 

	switch (courseOfAction) {
		case 'B':
			buildAction(); 
			break;
		case 'T':
			trainMAMain();
			break;
		case 'S':
			viewStats();
			break;
		case 'U':
			viewPlayerMap();
			break;
		case 'D':
			armyOverviewSelectAction();
			break;
		case 'N':
			BASE::nothing();
			break;
		case 'H':
			playerActionShowHelp();
			break;
		case 'P':
			choosePauseGame();
			break;
	}
	 
	//Recurse until base cass (Next turn action)
	if (courseOfAction != 'N') { chooseAction(); }
	return;
}

void Participants::buildAction() {
	pickYourProvince(1)->upgradeBuildingPrompt(); 
}

void Participants::playerActionShowHelp() { INF::showHelp(4); }

void Participants::choosePauseGame() { 
	char pauseGameQuestionChar = Input::getInputText("Pausing the game will end this session of gameplay. Proceed? (Y/N): ", { "Y", "N" }).at(0); 

	if (pauseGameQuestionChar == 'Y') { pauseGame(); }
	std::cout << "Returning to the Main menu... \n";
}

char Participants::randomAction() {
	//For debugging
	DEBUG_FUNCTION("PlayerAction", "randomAction");

	std::vector<char> newVector = { 'B', 'T', 'S', 'U', 'D', 'N' };
	return newVector.at(rand() % 6);
}


void Participants::pauseGame() {
	//For debugging
	DEBUG_FUNCTION("PlayerAction", "pauseGame");

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

/*
typedef void (Participants::* Actions)(void);
typedef std::unordered_map<char, Actions> ActionFunctions;
ActionFunctions actionsMap;

actionsMap['B'] = &buildAction;
actionsMap['T'] = &trainMAMain;
actionsMap['S'] = &viewStats;
actionsMap['U'] = &viewPlayerMap;
actionsMap['D'] = &armyOverviewSelectAction;
actionsMap['N'] = &BASE::nothing;
actionsMap['H'] = &playerActionShowHelp;
actionsMap['P'] = &choosePauseGame;

actionsMap.at(courseOfAction); */