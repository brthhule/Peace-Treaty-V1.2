#ifndef PROVINCE_REPORT_H
#define PROVINCE_REPORT_H

#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
#include COMMANDER_REPORT_HEADER
#include COMMANDERS_HEADER 

class ProvinceReport {
public:
	using commSPTR = COMM::commSPTR;

	ProvinceReport(
		int scouterLevelArg,
		int targetLevelArg,
		std::array<INF::i5array, 7> ListsArg,
		std::array<int, 7> listIntArg,
		std::array<bool, 3> listBoolArg,
		INF::ipair listSystemCoordsArg);

	void
		computeAccuracy(),
		attuneValues(),
		printReport();

	const int
		getReportTurn() const,
		getAccuracy() const,
		getTargetLevel() const,
		getScouterLevel() const;


private:
	std::array<INF::i5array, 7> Lists;
	std::array<int, 7> listInt;
	std::array<bool, 3> listBool;
	INF::ipair listSystemCoords;

	
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