#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <vector>
#include <iostream>
#include <array>

#include "Misc/INF.h"
#include "AllUnitsAttributes/Coords.h"
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\AllUnitsAttributes\Troops\Troops.h"

/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/
using namespace INF;


class AllUnits : public Coords
{
public:
	//----Constructors----
	//One param overloaded Constructor
	AllUnits(int index);
	//Default Constructor
	AllUnits();


	int
		getCP(),
		getParticipantIndex();

	//Provinces & Commanders
	int
		getLevel(),
		getFoodConsumption(),
		getResource(int resourceIndex);


	//resources
	void
		modifySpecificResource(int index, int amount, bool isAdd),
		modifyResources(std::array<int, 5> resourcesArray, bool isAdd),

		printResources(),
		changeUnitName(std::string name),
		changeParticipantIndex(int number),
		printTroopsPresent();

	std::array<int, 5> getAllResources();//Add implementation


	std::string getUnitName();
	void printResources(std::array<int, 5> resourcesArray);

		/*Return all the tiers for one troop type for a particular condition
	Example: returns all tiers for guards present*/
	i5array getAllOneTroopArray(TroopCondition troopCondition, INF::TroopTypes troopType);

	/*Returns the total of all of a particular troop type's tiers for a particular condition
	Example: returns the total of all tiers for guards present*/
	int getAllOneTroopInt(TroopCondition troopCondition, INF::TroopTypes troopType);

	/*Returns the tier totals for all troop types for a particular condition
	Example: returns the total of all tiers of all troops presnet, as in the totals for guards, infantry, archers, etc.*/
	i5array getGenericTroops(TroopCondition type);


	/*
	Change a troop by index or all trypes.
	TroopCondition: REGULAR, INJURED, LOST
	TroopTypes: GUARDS, INFANTRY, ARCHERS, CAVALRY, ARTILLARY
	amount: {a,b,c,d,e} or {a}
	Quantitiy: SINGLE, ALL
	MutateDirection: DECREASE, INCREASE
	troopTier: 1/2/3/3/4/5
	*/
	void mutateTroop(
		INF::TroopCondition troopCondition,
		TroopTypes troopType,
		std::array<int, 5> amount,
		Quantity quant,
		INF::MutateDirection direction,
		int troopTier);

	void setBattleFormation(std::array<);

protected:
	std::array<int, 5>
		resourcesPresent = { 0, 0, 0, 0, 0 },
		initialStats = { 5, 4, 3, 2, 1 };

	int
		combatPower,
		totalTroops,
		foodConsumption,
		participantIndex,
		unitLevel;

	using T5array = std::array<Troops, 5>;
	std::array<T5array, 5>
		troopsPresent,
		troopsInjured,
		troopsLost;


	std::array<std::array<T5array, 5>*, 3> allTroopConditions = {
		&troopsPresent,
		&troopsInjured,
		&troopsLost
	};

	std::array<std::vector<Troops>, 5> battleFormation;


	//Coordinates;

	bool canSelectThisUnit;

	enum UnitType { COMMANDER, PROVINCE };
	UnitType type;

	std::string
		unitName;

	Troops troops;
};

#endif