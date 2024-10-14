//TroopsINT.h
//Interface
//Implemented by Commanders.h

#ifndef TROOPSINT_H
#define TROOPSINT_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
#include INF_HEADER
#include TROOP_HEADER
#include TROOP_UNITS_BASE_HEADER
#include INPUT_HEADER

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
	virtual tiersArray& getAllTiersOfTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes type) = 0;

	/*Returns the total of all of a particular troop type's tiers for a particular condition
	Example: returns the total of all tiers for guards present*/
	virtual int getSumOfTiersOfTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes type) = 0;

	/*Returns the tier totals for all troop types for a particular condition
	Example: returns the total of all tiers of all troops presnet, as in the totals for guards, infantry, archers, etc.*/
	virtual INF::i5array getArrayOfSumsOfTiersOfAllTroops(TROOP::TroopCondition type) = 0;

	//----Mutators-------------------------------------------------------------
	/*Change a troop by index or all trypes.
	TroopCondition: REGULAR, INJURED, LOST
	TROOP::TroopTypes: GUARDS, INFANTRY, ARCHERS, CAVALRY, ARTILLARY
	amount: {a,b,c,d,e} or {a}
	Quantitiy: SINGLE, ALL
	MutateDirection: DECREASE, INCREASE
	troopTier: 1/2/3/3/4/5*/
	virtual void mutateTroop(
		TROOP::TroopCondition troopCondition,
		TROOP::TroopTypes type,
		troopsArray amount,
		INF::Quantity quant,
		INF::MutateDirection direction,
		int troopTier) = 0;

	virtual std::array<troopsArray, 3>& getTroopConditions() = 0;

	///Set the battle formation for... battle
	virtual void setBattleFormation(troopsArray troopArray) = 0;
};

#endif