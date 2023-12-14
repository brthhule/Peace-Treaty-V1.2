#ifndef COMMANDER_REPORT_H
#define COMMANDER_REPORT_H

#include <iostream>
#include <array>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include INF_HEADER

using namespace INF;

class CommanderReport {
public:
	CommanderReport();

	void printReport();
private:
	std::array<i5array, 5 > listInt;

	//Check these later
	i5array resourcesPresent; 
	i5array troopsPresent,
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