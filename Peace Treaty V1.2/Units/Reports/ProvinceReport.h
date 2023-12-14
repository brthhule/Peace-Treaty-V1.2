#ifndef PROVINCE_REPORT_H
#define PROVINCE_REPORT_H

#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>

#include "../Reports/CommanderReport.h"
#include "../Commanders.h"

class ProvinceReport {
public:
	using commSPTR = Commanders::commSPTR;

	ProvinceReport(int scouterLevelArg,
		int targetLevelArg,
		std::array<i5array, 7> ListsArg, 
		std::array<int, 7> listIntArg,
		std::array<bool, 3> listBoolArg,
		ipair listSystemCoordsArg);

	void
		computeAccuracy(),
		attuneValues(),
		printReport();

	int
		getReportTurn(),
		getAccuracy(),
		getTargetLevel(),
		getScouterLevel();


private:
	std::array<i5array, 7> Lists;
	std::array<int, 7> listInt;
	std::array<bool, 3> listBool;
	ipair listSystemCoords;

	
	std::string kingdomName;

	int
		reportTurn,
		accuracy,
		targetLevel,
		scouterLevel;

	std::vector<CommanderReport> commandersVector;
	std::unordered_map<std::string, commSPTR> commandersMap;
};
#endif