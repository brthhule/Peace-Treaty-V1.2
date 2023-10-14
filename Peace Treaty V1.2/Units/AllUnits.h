#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include "../Misc/ConstValues.h"
#include "../Misc/OF.h"
#include "../Coordinates.h"

/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/
using namespace CV;


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


	//----Troop Stuff----
	//Return a troop by index or all troops-- done by type. Pass -1 for troopIndex to return all troops of a type
	template<typename T>
	T getTroop(CV::MutateTroopType type, int troopIndex, T data);
	//Change a troop by index or all trypes.
	template<typename T>
	T mutateTroop(CV::MutateTroopType type, int troopIndex, T amount, CV::MutateDirection direction);




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
		changeParticipantIndex(int number);

	std::array<int, 5> getAllResources();//Add implementation


	std::string getUnitName();


protected:
	std::array<int, 5>
		resourcesPresent = { 0, 0, 0, 0, 0 },
		troopsPresent = { 0, 0, 0, 0, 0 },
		troopsInjured = { 0, 0, 0, 0, 0 },
		troopsLost = { 0, 0, 0, 0, 0 },
		initialStats = { 5, 4, 3, 2, 1 };

	int
		combatPower,
		totalTroops,
		foodConsumption,
		participantIndex,
		unitLevel;


	//Coordinates;

	bool canSelectThisUnit;

	enum UnitType { COMMANDER, PROVINCE };
	UnitType type;

	std::string
		unitName;
};

#endif