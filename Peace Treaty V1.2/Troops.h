#ifndef TROOPS_H
#define TROOPS_H

#include <iostream>
#include "../Peace Treaty V1.2/Misc/ConstValues.h"

using namespace CV;

class Troops {
public:
	Troops();

	std::array<int, 5> getAllOneTroop(CV::TROOPS type);
	
	void mutateTroop(CV::TROOPS type, int level, CV::MutateDirection);

	//----Troop Stuff----
/*Return a troop by index or all troops-- done by type.Pass - 1 for troopIndex to return all troops of a type
type: REGULAR, INJURED, LOST
troopIndex: troop level?
data: 
use randomArray
*/
	template<typename T>
	T getTroop(CV::MutateTroopType type, int troopIndex, T data);


	//Change a troop by index or all trypes.
	template<typename T>
	T mutateTroop(CV::MutateTroopType type, int troopIndex, T amount, CV::MutateDirection direction);

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

	std::array <std::array<int, 5>*, 5> allTroops = {
		&allGuards,
		&allInfantry,
		&allArchers,
		&allCavalry,
		&allArtillary
	};

};
#endif