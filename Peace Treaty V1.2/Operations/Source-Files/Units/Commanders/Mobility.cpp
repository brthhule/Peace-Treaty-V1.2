#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include PARTICIPANTS_HEADER 

using namespace PART;
using namespace COORD;
using namespace PROV;
using namespace COMM;
using namespace Input;
using namespace INF;

#include PROVINCES_HEADER


void Participants::moveUnitOne(commSPTR commander) { 
	//For debugging
	DEBUG_FUNCTION("Mobility.cpp", "moveUnitOne");

	if (commander->hasMoved() == true) {
		std::cout << "This unit has already moved this turn. Please pick another unit. \nReturning to previous menu... \n\n";
	}

	provSPTR selected = std::make_shared<Provinces>(pickProvinceToMoveTo(*commander)); 
	std::string confirmMove;

	ProvinceRelation relation = FRIENDLY_PROVINCE;
	// If province is in the list

	if (selected->getParticipantIndex() !=
		commander->getParticipantIndex()) {
		relation = ENEMY_PROVINCE; 
		println("This is an enemy province. Moving here will attack the enemy garrison stationed here.");
	} else {
		std::cout << "This is a friendly province.\n";
	}

	std::string prompt = "Confirm moving your unit to " + selected->getCoords(COORD::USER) + "? (Y / N) ";

	// If participants confirms movement
	if (Input::getInputText(prompt, { "Y", "N" }).at(0) == 'N') {
		std::cout << "Cancelling action...\n";
		return;
	}

	if (relation == ENEMY_PROVINCE) {
		//Have to work this out
		//AttackMA newAttackMA(selectedCommanderProvince, attackProvince, participant, selectedCommander);
	}

	// If it's peaceful (moving to one of their own Provinces::)
	//Remove commander from previous province
	provSPTR formerProvince = Map::getProvince(SYSTEM, commander->CoordsBASE::getCoords(SYSTEM)); 
	formerProvince->removeCommander(commander);
	selected->addCommander(*commander); 
	std::cout << "Returning to previous menu... \n\n";

} /* unfinished*/


Provinces& Participants::pickProvinceToMoveTo(Commanders& commander_ref) {
	//This will have the list of Provinces:: that can be moved to
	LOG::PRINT("The coordinates of the chosen unit unit are: ");
	commander_ref.printCoords(COORD::USER); 
	println("\n\nYou can only move this unit to one of the Provinces:: adjacent to the province it is in");

	//Get list of Provinces:: that can be moved to
	provSPTRList selectableProvinces = getSurroundingProvinces(commander_ref);

	// The participant slects coordinates
	ipair pickUserCoords = Map::pickCoords();

	if (pickUserCoords.first == -1) {
		std::cout << "Cancelling action...\n";
		INF::enterAndClear(1);
		nullptr;
	}
	Provinces& selected = *Map::getProvince(USER, pickUserCoords).get();
	bool validProvince = false;
	for (provSPTR provincePtr : selectableProvinces) {
		if (provincePtr.get() == &selected) {
			validProvince = true;
		}
	}

	if (validProvince) { return selected; }


	std::cout << "Invalid province selected... please choose a valid province\n";
	return pickProvinceToMoveTo(commander_ref); 
	

}

provSPTRList Participants::getSurroundingProvinces(Commanders& commander_ref) {
	//For debugging
	DEBUG_FUNCTION("Mobility.cpp", "getSurroundingProvinces::");

	std::vector<provSPTR> selectableProvinces;
	ipair systemCoords = commander_ref.CoordsBASE::getCoords(COORD::SYSTEM);

	/*Identify all the Provinces:: that the player can move a unit to*/
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			// Check if coords are within map bounds
			// size)
			int firstCoordinate = systemCoords.first + x;
			int secondCoordinate = systemCoords.second + y;

			bool checkFirst = (
				firstCoordinate >= 0 &&
				firstCoordinate < INF::continentSize);
			bool checkSecond = (
				secondCoordinate >= 0 &&
				secondCoordinate < INF::continentSize);
			//Returns true if the changed coordinates != original
			bool checkBoth = (
				firstCoordinate != systemCoords.first ||
				secondCoordinate != systemCoords.second);


			if (checkFirst && checkSecond && checkBoth){ 
				ipair pushCoords(firstCoordinate, secondCoordinate);
				provSPTR province = Map::getProvince(SYSTEM, pushCoords);  
				selectableProvinces.push_back(province);
			}
		}
	}
	return selectableProvinces;
}
