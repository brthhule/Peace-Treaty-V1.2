#include "PlayerAction.h"

extern int turn;

PlayerAction::PlayerAction() {
	OF.debugFunction("PlayerAction, PlayerAction (0)");
}

PlayerAction::PlayerAction(Participants *newP) 
{ 
	OF.debugFunction("PlayerAction, PlayerAction (1)");
	participant = newP; 
}

void PlayerAction::initialDecision() {
	OF.debugFunction("PlayerAction, initialDecision");
  bool goToNextTurn = false;
  OF.clearScreen();
  char courseOfAction = ' ';
  if (participant->isPlayer() == true)
  {
    std::cout << "Turn: " << turn << std::endl;
    std::cout << "Player " << participant->getKingdomName() << "'s move...";
    std::cout << "\n\nWelcome to the Main Action menu \n\n";
		participant->showMapCoordinates();
		std::cout << std::endl;
    db.showMap();
    
    courseOfAction = OF.getOption(4);
  }
  else // If the participant is the AI
  {
    courseOfAction = randomAction();
  }

  std::cout << std::endl;
  OF.clearScreen();

  switch (courseOfAction) {
  case 'B': {
		Provinces *newProvince = participant->getYourProvince(1);
        newProvince->playerBuildFunction();
    break;
  }
  case 'T': {
    TrainMA newTrainMA();
    break;
  }
  case 'S':
    participant->viewStats();
    break;
  case 'U': {
    MapMA newMap();
    newMap.viewPlayerMap();
    break;
  }
  case 'D': {
    ArmyOverviewMA newArmyOverview();
    newArmyOverview.armyDeploymentMF();
    break;
  }
  case 'N':
    goToNextTurn = true;
    break;
  case 'H': {
		OF.showHelp(4);
    break;
  }
  case 'P': {
    char pauseGameQuestionChar = OF.getInput(false, -1, "Pausing the game will end this session of gameplay. Proceed? (Y/N): ", {"Y", "N"}, false, false).at(0);
		
    if (pauseGameQuestionChar == 'Y') 
      pauseGame();
    
    std::cout << "Returning to the Main menu... \n";
  }
  }
  if (goToNextTurn == false)
    initialDecision();
}

char PlayerAction::randomAction() {
	OF.debugFunction("PlayerAction, randomAction");
  int randomNumber = rand() % 6; // Random number 0 to 5 (inclusive)
	std::vector<char> newVector = {'B', 'T', 'S', 'U', 'D', 'N'};
  return newVector[randomNumber];
}


void PlayerAction::pauseGame() {
	OF.debugFunction("PlayerAction, pauseGame");
  std::string gameCode;
  gameCode += continentSize;

  for (int x = 0; x < continentSize; x++) {
    for (int y = 0; y < continentSize; y++) {
      gameCode += provincesMap[x][y].getParticipantIndex();
    }
  }
  std::cout << "Game ended... \nHere is your game code (Copy this code and "
               "paste it when using the 'Resume Game' functionality): "
            << gameCode << "\n\n";
}