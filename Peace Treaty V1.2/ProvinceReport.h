#ifndef PROVINCE_REPORT_H
#define PROVINCE_REPORT_H

#include <iostream>
#include <array>
#include <vector>

#include "CommandeReport.h"

class ProvinceReport {
public:
	ProvinceReport(int scouterLevelArg,
		int targetLevelArg,
		std::array<std::array<int, 5>, 7> ListsArg, 
		std::array<int, 7> listIntArg,
		std::array<bool, 3> listBoolArg,
		std::pair<int, int> listSystemCoordsArg);

	void
		computeAccuracy(),
		attuneValues(),
		printReport();


private:
	std::array<std::array<int, 5>, 7> Lists;
	std::array<int, 7> listInt;
	std::array<bool, 3> listBool;
	std::pair<int, int> listSystemCoords;

	
	std::string kingdomName;

	int
		reportTurn,
		accuracy,
		targetLevel,
		scouterLevel;

	std::vector<CommanderReport> commandersList;
};
#endif