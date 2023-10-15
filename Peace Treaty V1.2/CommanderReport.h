#ifndef COMMANDER_REPORT_H
#define COMMANDER_REPORT_H

#include <iostream>
#include <array>
#include <vector>

class CommanderReport {
public:
	CommanderReport();

	void printReport();
private:
	std::array<std::array<int, 5>, 5 > listInt;
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