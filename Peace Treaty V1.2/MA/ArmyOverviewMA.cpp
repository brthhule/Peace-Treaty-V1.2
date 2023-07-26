#include "ArmyOverviewMA.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

ArmyOverviewMA::ArmyOverviewMA(Participants *newP) {
  participant = newP;
  commandersNum = participant->commandersNum();
}

void ArmyOverviewMA::armyDeploymentMF() {
  println("Welcome to the Army Deployment action menun\n");

  switch (getOption(5)) {
  case 'T':
    trainCommanders();
    break;
  case 'U':
    upgradeCommandersOne();
    break;
  case 'V':
    viewArmyOverview();
    break;
  case 'D': {
    deployCommanderMF();
    break;
  }
  case 'H': {
    showHelp(5);
    break;
  }
  case 'M':
    return;
    break;
  }
  armyDeploymentMF();
}

void ArmyOverviewMA::upgradeCommandersOne() /*fix this-- finish making it*/
{
  if (commandersNum > 0)
	{
		if (participant->selectCommander() != "-1")
			upgradeCommandersTwo();
	}
  else 
    std::cout << "No commanders available, can not upgrade\n";
  
  OF.enterAnything();
}
void ArmyOverviewMA::upgradeCommandersTwo() 
{
	std::array<int,5> costsArray = participant->getCommanderByName(commanderName)->getUpgradeCosts();
	
  participant->getCommanderByName(commanderName)->printCosts(costsArray);

	char proceedWithUpgradeQuestion =
      OF.getInput("\nProceed with upgrade? ", {"Y", "N"}, false, false).at(0);
  if (proceedWithUpgradeQuestion == 'Y') {

    std::array<int, 5> commanderCosts = costsArray;
		bool commanderUpgradeIsSuccess = participant->getCapital()->subtractCheckResources(commanderCosts);

    if (commanderUpgradeIsSuccess == true) {
      participant->getCommanderByName(commanderName)->addLevel();
      std::cout << "Upgrade successful; Commander " + commanderName + "is now level " << participant->getCommanderByName(commanderName)->getLevel() << std::endl;
    } else {
      participant->getCapital()->modifyResources(commanderCosts, true);
      std::cout << "Upgrade failed. " << std::endl;
    }
  }
}

void ArmyOverviewMA::viewArmyOverview() {
	commanderName = participant->selectCommander();
if (commanderName != "-1")
	{
		std::cout << "Commander " << commanderName << " selected... " << std::endl;
    std::cout << "The coordinates of this Commander: ";
		participant->getCommanderByName(commanderName)->printCoordinates();
		std::cout << "\n\n";

    participant->getCommanderByName(commanderName)->printCommanderStats();
	}
	OF.enterAnything();	
}

void ArmyOverviewMA::trainCommanders() {
  std::string yesOrNoString;
  std::cout << "You have " << commandersNum << "/" << participant->getMaxCommanders() << " total army commanders. \n";
  std::cout << "Do you want to train a commander? (Y/N) ";

  std::array<int, 5> trainCosts = participant->getTrainCosts();

  if (OF.getInput("Proceed with training", {"Y", "N"}, false, false).at(0) == 'Y') 	{
    if (commandersNum < participant->getMaxCommanders()) /*if amount of commanders is less than max (not at max capacity)*/
        proceedWithTraining(trainCosts);
    else 
      std::cout << "At maximum army commander amount. Training failed, returning to menu \n";
  } 
	else 
    OF.enterAnything();
}

void ArmyOverviewMA::proceedWithTraining(std::array<int,5> trainCosts) {
  bool trainingSuccess = participant->getCapital()->subtractCheckResources(trainCosts);

  if (trainingSuccess == true) 
	{
    participant->addCommander();
		
		println("Commander training successful ");
    std::cout << "Current commanders: " << commandersNum << std::endl;
  } 
	else 
	{
    std::cout << "Commander training failed (Not enough resources)... \n\n";
    participant->getCapital()->modifyResources(trainCosts, true);
  }
}

void ArmyOverviewMA::deployCommanderMF() 
{
	commanderName = participant->selectCommander();
  if (commanderName != "-1")
		return;
	
  participant->getCommanderByName(commanderName)->printCommanderStats();

  std::cout << "Deploy commander " + commanderName + "? (Y/N) ";
  char confirmDeploy = OF.getInput("Replacement", {"Y", "N"}, false, false).at(0);

  if (confirmDeploy == 'Y') 
	{
    if (participant->getCommanderByName(commanderName)->hasMovedQuestion() == false) {
      Mobility newMobility(commanderName, participant);
      newMobility.moveUnitOne();
    } 
		else 
		{
			std::cout << "This unit has already moved... please pick another unit \n";
			deployCommanderMF();
		}

	  OF.enterAnything();
	}
}

void ArmyOverviewMA::printCosts(std::vector<int> costs, std::string type) {
  std::cout << "The following are the " << type << " costs: \n";
  for (int x = 0; x < 5; x++)
    std::cout << CV.RESOURCE_NAMES[x] << ": " << costs[x];

  std::cout << "The following are the resources currently in your capital: \n";
  participant->getCapital()->printResources();
}

