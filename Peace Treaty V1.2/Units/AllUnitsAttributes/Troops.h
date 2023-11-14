#ifndef TROOPS_H
#define TROOPS_H

#include <iostream>
#include "../Misc/INF.h"

using namespace INF;

class Troops {
public:
	Troops();

	std::array<int, 5> getAllOneTroop(INF::TROOPS type);

	//----Troop Stuff----
/*Return a troop by index or all troops-- done by type.Pass - 1 for troopIndex to return all troops of a type
type: REGULAR, INJURED, LOST
troopIndex: troop level?
data: 
use randomArray
*/
	std::array<int, 5> getTroop(INF::MutateTroopType type, int troopIndex, Quantity amount);


	//Change a troop by index or all trypes.
	void mutateTroop(INF::MutateTroopType type, int troopIndex, std::array<int,5> amount, Quantity quant, INF::MutateDirection direction);

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