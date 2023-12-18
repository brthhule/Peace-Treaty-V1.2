//TroopsINT.h
//Interface
//Implemented by AllUnits.h (Extended by Provinces and Commanders, Composed in Particiapnts)

#ifndef TROOPSINT_H
#define TROOPSINT_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include INF_HEADER

using namespace INF;

namespace TROOP {
	/*REGULAR, INJURED, LOST */
	enum TroopCondition {
		REGULAR,
		INJURED,
		LOST
	};

	/*	GUARDS,
		INFANTRY,
		ARCHERS,
		CAVALRY,
		ARTILLARY*/
	enum TroopTypes {
		GUARDS,
		INFANTRY,
		ARCHERS,
		CAVALRY,
		ARTILLARY
	};

	extern i5array TROOPS_COST, Troops_CP;
	extern int maxCommanders;

class TroopsINT {
public:
	//----Constructors---------------------------------------------------------
	TroopsINT() {}	//Default constructor
	~TroopsINT() {}	//Destructor
	//----Printers-------------------------------------------------------------
	///Print all troops here
	virtual void printTroopsPresent() = 0;

	//----Getters--------------------------------------------------------------
	/*Return all the tiers for one troop type for a particular condition
	Example: returns all tiers for guards present*/
	constI5array getAllOneTroopArray(TroopCondition troopCondition, TROOP::TroopTypes type);

	/*Returns the total of all of a particular troop type's tiers for a particular condition
	Example: returns the total of all tiers for guards present*/
	constINT getAllOneTroopInt(TroopCondition troopCondition, TROOP::TroopTypes type);

	/*Returns the tier totals for all troop types for a particular condition
	Example: returns the total of all tiers of all troops presnet, as in the totals for guards, infantry, archers, etc.*/
	constI5array getGenericTroops(TroopCondition type);


	/*Change a troop by index or all trypes.
	TroopCondition: REGULAR, INJURED, LOST
	TROOP::TroopTypes: GUARDS, INFANTRY, ARCHERS, CAVALRY, ARTILLARY
	amount: {a,b,c,d,e} or {a}
	Quantitiy: SINGLE, ALL
	MutateDirection: DECREASE, INCREASE
	troopTier: 1/2/3/3/4/5*/
	void mutateTroop(
		TROOP::TroopCondition troopCondition,
		TROOP::TroopTypes type,
		i5array amount,
		Quantity quant,
		INF::MutateDirection direction,
		int troopTier);


	///Set the battle formation for... battle
	void setBattleFormation(troopConditionArray troopArray);
};

#endif

}