#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include COORDS_BASE_HEADER				//Base Class
#include INF_HEADER						//Utility
#include TROOP_UNITS_BASE_HEADER		//Composition

using namespace INF;

namespace UNIT {

enum UnitType { COMMANDER, PROVINCE };

class AllUnits : 
	public CoordsBASE					//Base Class
{
public:
	//----Aliases--------------------------------------------------------------	
	using T5array = INF::Array5<TroopUnitsBASE>;
	using unitSPTR = std::shared_ptr<AllUnits>;
	using troopConditionArray = INF::Array5<T5array>;
	using unitSPTRList = std::vector<unitSPTR>;

	//----Constructors---------------------------------------------------------
	///Default Constructor
	AllUnits();
	///One param overloaded Constructor
	AllUnits(int index);
	///Destructor
	~AllUnits(){}

	//----Getters--------------------------------------------------------------
	///Returns combat power of this unit. Implemented by derived classes
	virtual constINT getCP() = 0;
	///Get the food consumption of this unit. Implemented by derived class
	virtual constINT getFoodConsumption();
	///Get the level of this unit. Implemented by derived classes
	virtual constINT getLevel();

	///Returns the index of the Participant this belongs to
	constINT getParticipantIndex();
	///Returns the value of one type of resource in this unit
	constINT getResource(int resourceIndex);

	///Returns the amount of resources currently in this unit
	constI5array getTotalResources();
	///Get this unit's name
	const std::string& getUnitName();


	//----Mutators-------------------------------------------------------------
	/** mutateResource__
			Changes the value of a particular resource in this unit

			@param resource__ 
				This resource type
			@param amount__
				The amount this resource changes by.
			@param direction__
				Does the mutation occur in an increasing/decreasing manner
	*/
	void mutateResource(ResourceType resource, constINT amount, 
		MutateDirection direction);
	/** mutateAllResources__
			Changes all the values of this unit's resources by an array

			@param resourcesArray__
				The set of values this unit's resources changes by
			@param direction__
				Does the mutation occur in an increasing/decreasing manner
	*/
	void mutateAllResources(constI5array resourcesArray, 
		INF::MutateDirection direction);
	///Change this unit's name
	void changeUnitName(std::string name);
	void changeParticipantIndex(int number);

	//----Printers-------------------------------------------------------------
	void printResources();
	void printTroopsPresent();

	i5array getAllResources();//Add implementation


	void printResources(i5array resourcesArray);

	/*Return all the tiers for one troop type for a particular condition
	Example: returns all tiers for guards present*/
	i5array getAllOneTroopArray(TroopCondition troopCondition, TroopUnitsBASE::TroopTypes type);

	/*Returns the total of all of a particular troop type's tiers for a particular condition
	Example: returns the total of all tiers for guards present*/
	int getAllOneTroopInt(TroopCondition troopCondition, TroopUnitsBASE::TroopTypes type);

	/*Returns the tier totals for all troop types for a particular condition
	Example: returns the total of all tiers of all troops presnet, as in the totals for guards, infantry, archers, etc.*/
	i5array getGenericTroops(TroopCondition type);


	/*Change a troop by index or all trypes.
	TroopCondition: REGULAR, INJURED, LOST
	TroopUnitsBASE::TroopTypes: GUARDS, INFANTRY, ARCHERS, CAVALRY, ARTILLARY
	amount: {a,b,c,d,e} or {a}
	Quantitiy: SINGLE, ALL
	MutateDirection: DECREASE, INCREASE
	troopTier: 1/2/3/3/4/5*/
	void mutateTroop(
		INF::TroopCondition troopCondition,
		TroopUnitsBASE::TroopTypes type,
		i5array amount,
		Quantity quant,
		INF::MutateDirection direction,
		int troopTier);

	void setBattleFormation(troopConditionArray troopArray);

	//Override?
	INF::ipair translateCoords(INF::ipair coords, CoordsType type);

	unitSPTRList sortVector(SortType sort, unitSPTRList list);
	unitSPTRList levelSort(unitSPTRList list);

protected:
	i5array resourcesPresent;
	i5array initialStats;

	int combatPower;
	int totalTroops;
	int foodConsumption;
	int participantIndex;
	int unitLevel;


	troopConditionArray troopsPresent;
	troopConditionArray troopsInjured;
	troopConditionArray troopsLost;


	std::array<troopConditionArray*, 3> allTroopConditions;

	std::array<std::vector<TroopUnitsBASE>, 5> battleFormation;


	//Coordinates;

	bool canSelectThisUnit;

	UnitType type;
	std::string unitName;
	TroopUnitsBASE troops;
};

using unitSPTR = std::shared_ptr<AllUnits>;
using unitSPTRList = std::vector<unitSPTR>;

}
#endif