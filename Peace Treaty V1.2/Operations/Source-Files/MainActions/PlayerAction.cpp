#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER

using namespace PART;

void Participants::chooseAction() {
	INF::debugFunction("PlayerAction, chooseAction");
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
		courseOfAction = Input::getOptionPrompt(PLAYER_ACTION).at(0); 
	} 

	INF::enterAndClear(1);

	typedef void (*Actions) ();
	Actions actions[] = {
		buildAction(),
		trainMAMain(),
		viewStats(),
		viewPlayerMap(),
		armyOverviewMain(),
		INF::nothing(),
		showHelp(),
		choosePauseGame()
	};

	int actionNum = actionsMap[courseOfAction];  
	actions[actionNum](); 
	 
	//Recurse until base cass (Next turn action)
	if (actionNum != 5) { chooseAction(); } 
	return;
}

void Participants::buildAction() {
	provSPTR newProvince = pickYourProvince(1);
	newProvince->mainBuildFunction();
}
void Participants::showHelp() {
	INF::showHelp(4); 
}

void Participants::choosePauseGame() { 
	char pauseGameQuestionChar = Input::getInputText("Pausing the game will end this session of gameplay. Proceed? (Y/N): ", { "Y", "N" }).at(0); 

	if (pauseGameQuestionChar == 'Y') { pauseGame(); }
	std::cout << "Returning to the Main menu... \n";
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