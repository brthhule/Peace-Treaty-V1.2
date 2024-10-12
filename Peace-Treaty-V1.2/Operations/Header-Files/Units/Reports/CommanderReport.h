#ifndef COMMANDER_REPORT_H
#define COMMANDER_REPORT_H

#include <iostream>
#include <array>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include INF_HEADER

class CommanderReport {
public:
	CommanderReport();

	void printReport();
private:
	std::array<INF::i5array, 5 > listInt;

	//Check these later
	INF::i5array resourcesPresent; 
	INF::i5array troopsPresent,
		troopsInjured,
		troopsLost,
		initialStats;

	int
		combatPower,
		totalTroops,
		foodConsumption,
		participantIndex,
		unitLevel,
		maxTroops,
		totalMaxResources,
		commanderIndex;


	//Coordinates;

	bool canSelectThisUnit;

	enum UnitType { COMMANDER, PROVINCE };
	UnitType type;

	std::string
		unitName;
};

#endif