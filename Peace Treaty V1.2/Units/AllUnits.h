#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include "Misc/CV.h"
#include "Misc/CV.h"
#include "AllUnitsAttributes/Coords.h"
#include "AllUnitsAttributes/Troops.h"

/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/
using namespace CV;


class AllUnits : public Coords, public Troops
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
		changeParticipantIndex(int number);

	std::array<int, 5> getAllResources();//Add implementation


	std::string getUnitName();
	void printResources(std::array<int, 5> resourcesArray);

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


	//Coordinates;

	bool canSelectThisUnit;

	enum UnitType { COMMANDER, PROVINCE };
	UnitType type;

	std::string
		unitName;

	Troops troops;
};

#endif