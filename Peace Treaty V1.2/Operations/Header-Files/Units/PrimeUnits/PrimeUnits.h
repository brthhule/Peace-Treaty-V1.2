#ifndef PRIMEUNITS_H
#define PRIMEUNITS_H

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include COORDS_BASE_HEADER				//Base Class
/*	#include INF_HEADER*/
#include TROOP_UNITS_BASE_HEADER		//Composition
/*	#include TROOP_HEADER*/
#include TROOPS_INT_HEADER				//Interface
/*	#include TROOP_HEADER*/

using namespace INF;
using namespace TROOP;
using namespace COORD;

namespace UNIT {

enum UnitType { COMMANDER, PROVINCE };

class PrimeUnits : 
	public CoordsBASE					//Base Class
{
public:
	//----Aliases--------------------------------------------------------------	
	using unitSPTR = std::shared_ptr<PrimeUnits>;
	using unitSPTRList = std::vector<unitSPTR>;

	//----Constructors---------------------------------------------------------
	///One param overloaded Constructor
	///Use -1 for empty provinces
	PrimeUnits(int participantIndex);
	///Destructor
	~PrimeUnits(){}

	//----Getters--------------------------------------------------------------
	///Returns combat power of this unit. Implemented by derived classes
	virtual constINT getCombatPower() const = 0;
	virtual void calculateFoodConsumption() = 0;  
	///Get the food consumption of this unit. Implemented by derived class
	virtual constINT getFoodConsumption() const = 0;
	///Get the level of this unit. Implemented by derived classes
	virtual constINT getLevel() const = 0;

	///Returns the index of the Participant this belongs to
	constINT getParticipantIndex() const;
	///Returns the value of one type of resource in this unit
	constINT getResource(int resourceIndex);


	///Get this unit's name
	const std::string& getName() const;

	constArrayReference getAllResources() const;//Add implementation

	const std::string getCoords(CoordsType type) const;


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
	void mutateAllResources(constArrayReference resourcesArray,
		INF::MutateDirection direction);

	//----Printers-------------------------------------------------------------
	///Print all the resources in this unit
	void printResources() const;
	///Prints all the troops in this unit. Implemented by derived classes
	

	//Override?
	INF::ipair translateCoords(INF::ipair coords, CoordsType type);

	unitSPTRList sortVector(SortType sort, unitSPTRList list);
	unitSPTRList levelSort(unitSPTRList list);

	void printNameLevel() const;
	const std::string getNameLevel() const;

	//----Setters--------------------------------------------------------------
	///Set this unit's name
	void setName(std::string name);
	///Set the index of the participant this unit belongs to
	void setParticipantIndex(int number);

	///////////////////////////////////TroopsINT.h/////////////////////////////

protected:
	i5array resourcesPresent;
	i5array initialStats;

	int combatPower;
	int totalTroops;
	int foodConsumption;
	int participantIndex;
	int level;

	//Coordinates;

	bool canSelectThisUnit;

	UnitType type;
	std::string name;
	TroopUnitsBASE troops;
};

using unitSPTR = std::shared_ptr<PrimeUnits>;
using unitSPTRList = std::vector<unitSPTR>;

}
#endif