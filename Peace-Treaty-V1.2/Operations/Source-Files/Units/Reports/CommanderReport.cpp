#include "..\..\..\..\Support\Paths.h"
#include COMMANDER_REPORT_HEADER

CommanderReport::CommanderReport() {
	//For debugging
	DEBUG_FUNCTION("CommanderReport", "CommanderReport");

	resourcesPresent = { 0, 0, 0, 0, 0 },
	troopsPresent = { 0, 0, 0, 0, 0 },
	troopsInjured = { 0, 0, 0, 0, 0 },
	troopsLost = { 0, 0, 0, 0, 0 },
	initialStats = { 5, 4, 3, 2, 1 };

	combatPower = 0;
	totalTroops = 0;
	foodConsumption = 0;
	participantIndex = 0;
	unitLevel = 0;
	maxTroops = 0;
	totalMaxResources = 0;
	commanderIndex = 0;
	//Implement this
}

void CommanderReport::printReport() {
	//For debugging
	DEBUG_FUNCTION("CommanderReport", "printReport");

	//Implement this

}
