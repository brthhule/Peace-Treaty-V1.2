#ifndef TROOPS_H
#define TROOPS_H

#include <iostream>
#include "../Peace Treaty V1.2/Misc/ConstValues.h"

using namespace CV;

class Troops {
public:
	Troops();

	std::array<int, 5> getAllOneTroop(CV::TROOPS type);

	//----Troop Stuff----
/*Return a troop by index or all troops-- done by type.Pass - 1 for troopIndex to return all troops of a type
type: REGULAR, INJURED, LOST
troopIndex: troop level?
data: 
use randomArray
*/
	std::array<int, 5> getTroop(CV::MutateTroopType type, int troopIndex, Quantity amount);


	//Change a troop by index or all trypes.
	void mutateTroop(CV::MutateTroopType type, int troopIndex, std::array<int,5> amount, Quantity quant, CV::MutateDirection direction);

protected:
	//Keeps tracks of how much of each unit, each index is a higher level
	std::array<int, 5> 
		allGuards,
		allInfantry,
		allArchers,
		allCavalry,
		allArtillary,

		troopsPresent = { 0, 0, 0, 0, 0 },
		troopsInjured = { 0, 0, 0, 0, 0 },
		troopsLost = { 0, 0, 0, 0, 0 };

		std::array<std::array<int, 5>*, 3> allTroopTypes = {
			&troopsPresent,
			&troopsInjured,
			&troopsLost
		};

	std::array <std::array<int, 5>*, 5> allTroops = {
		&allGuards,
		&allInfantry,
		&allArchers,
		&allCavalry,
		&allArtillary
	};

};
#endif