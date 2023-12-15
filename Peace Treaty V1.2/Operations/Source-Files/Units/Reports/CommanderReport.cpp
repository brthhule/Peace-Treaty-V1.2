#include "CommanderReport.h"

CommanderReport::CommanderReport() {
	//For debugging
	INF::debugFunction("CommanderReport, CommanderReport");

	resourcesPresent = { 0, 0, 0, 0, 0 },
	troopsPresent = { 0, 0, 0, 0, 0 },
	troopsInjured = { 0, 0, 0, 0, 0 },
	troopsLost = { 0, 0, 0, 0, 0 },
	initialStats = { 5, 4, 3, 2, 1 };

	//Implement this
}

void CommanderReport::printReport() {
	//For debugging
	INF::debugFunction("CommanderReport, printReport");

	//Implement this

}
