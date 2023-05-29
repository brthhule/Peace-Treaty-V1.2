#include "Mobility.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

Mobility::Mobility(std::string commanderName, Participants *newP)
{
	selectedCommander = participant->getCommanderByName(commanderName);
	selectedCommanderProvince = &provincesMap[selectedCommander->getCoordinate('X')][selectedCommander->getCoordinate('Y')];
	participant = newP;
}

std::vector<Provinces *> Mobility::moveUnitTwo() {
  std::vector<Provinces *> vectorThingy;
  for (int x = -1; x <= 1;
       x++) /*Identify all the provinces that the player can move a unit to*/
  {
    for (int y = -1; y <= 1; y++) {
      // Check to see if the coordinates are in bounds (not outside of the map
      // size)
      if (/*X coordinate stuff*/ x >= 0 && x < continentSize &&
          /*Y coordinate stuff*/ y >= 0 && y < continentSize) {
        // Make sure province isn't the starting province
        if (x != 0 || y != 0) {
          // Add province to list of provinces can move to
          vectorThingy.push_back(
              &provincesMap[x + selectedCommanderProvince->getCoordinate('X')][y + selectedCommanderProvince->getCoordinate('Y')]);
        }
      }
    }
  }
	return vectorThingy;
}

void Mobility::moveUnitOne() {
	OtherFunctions OF;
  std::vector<Provinces *> provincesCanSelect;
  if (selectedCommander->hasMovedQuestion() == false) {
		std::array<int, 2> newCoordinates = selectedCommander->getCoordinates();
    std::cout<<"The coordinates of the chosen unit unit are: " << OF.printCoordinates(newCoordinates);
		println("\n\nYou can only move this unit to one of the provinces adjacent to the province it is in");
		
    provincesCanSelect = moveUnitTwo();

    // The participant slects coordiantes
    Provinces* moveTwo = participant->getCoords(2);

    int provinceIndexSelected = 0;
    char provinceIsInList = 'N';
    for (int x = 0; x < provincesCanSelect.size(); x++) {
      if (moveTwo == provincesCanSelect[x]) {
        provinceIndexSelected = x;
        provinceIsInList =
            'Y';
      }
    }

    // For display
    int moveToX = moveTwo->translateX(false);
    int moveToY = moveTwo->translateY(false);

    std::string confirmMove;
    char attackScenario = 'P'; /*P is for peace, A is for attack*/
    // If province is in the list
    if (provinceIsInList == 'Y') {
      Provinces *attackProvince = provincesCanSelect[provinceIndexSelected];
			
      if (attackProvince->getParticipantIndex() !=
          participant->getParticipantIndex()) {
        attackScenario = 'A';
        println ("Moving here will cause your unit to attack any enemy units stationed at this province.");
      }
      std::cout << "Confirm moving your unit to (" << moveToX << ", " << moveToY
                << ")? (Y/N) ";

      // If participants confirms movement
      if (OF.getInput("Replacement", {"Y", "N"}, false).at(0) == 'Y') {
        // If it's peaceful (moving to one of their own provinces)
        if (attackScenario == 'P') {
					std::array<int, 2> coordinates = moveTwo->getCoordinates();
          selectedCommander->setLocation(coordinates);
          attackProvince->addCommander(selectedCommander);
        }
        // If scenario is attack
        else 
          AttackMA newAttackMA(selectedCommanderProvince, attackProvince, participant, selectedCommander);
      }
    } else {
      std::cout << "Invalid province selected... please try again. " << std::endl;
      // Recursion until suitable coordinates are chosen
      moveUnitOne();
    }
  } else {
    std::cout
        << "This unit has already moved this turn. Please pick another unit. "
        << std::endl;
  }
  std::cout << "Returning to previous menu... " << std::endl << std::endl;
} /* unfinished*/