#ifndef TROOPS_H
#define TROOPS_H

#include <iostream>
#include "../Misc/INF.h"

using namespace INF;

class Troops {
public:
	Troops();

	/*Return all the tiers for one troop type for a particular condition
	Example: returns all tiers for guards present*/
	i5array getAllOneTroop(TroopCondition troopCondition, INF::TroopTypes troopType);

	/*Returns the total of all of a particular troop type's tiers for a particular condition
	Example: returns the total of all tiers for guards present*/
	int getAllOneTroop(TroopCondition troopCondition, INF::TroopTypes troopType);

	/*Returns the tier totals for all troop types for a particular condition
	Example: returns the total of all tiers of all troops presnet, as in the totals for guards, infantry, archers, etc.*/
	i5array getGenericTroops(TroopCondition type);


	//Change a troop by index or all trypes.
	void mutateTroop(
		INF::TroopCondition troopCondition, 
		TroopTypes troopType, 
		std::array<int,5> amount, 
		Quantity quant, 
		INF::MutateDirection direction, 
		int troopTier);

protected:

	/*Each row is a different troop type, each column is a different tier
	
	Rows:
	0 = guardsTiers,
	1 = infantryTiers,
	2 = archersTiers,
	3 = cavalryTiers,
	4 = artillaryTiers;

	Cols:
	0 = tier 1
	1 = tier 2
	2 = tier 3
	3 = tier 4
	4 = tier 5
		*/
	std::array<i5array, 5> 
		troopsPresent,
		troopsInjured,
		troopsLost;


	std::array<std::array<i5array, 5>*, 3> allTroopConditions = {
		&troopsPresent,
		&troopsInjured,
		&troopsLost
	};
};
#endif