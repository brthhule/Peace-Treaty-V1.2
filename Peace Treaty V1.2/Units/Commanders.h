#ifndef COMMANDERS_H
#define COMMANDERS_H

#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include ALL_UNITS_HEADER
#include INF_HEADER

using namespace INF;

//Control army units
class Commanders : public AllUnits {
public:
	using CommanderSPtr = std::shared_ptr<Commanders>;
	// Constructors
	Commanders();
	Commanders(int commanderLevel, std::string name);
	// Destructor
	~Commanders();



	// Stats stuff
	int
		getCommanderStat(int index);

	void
		printCommanderStats(),

		printCosts(std::array<int, 5> costs),
		addLevel(),
		resetCommanderMoved(),
		calculateCommanderScoutLog();

	std::array<int, 5> getUpgradeCosts();
	
	bool hasMoved();

private:
	INF::INTEGER
		maxTroops,
		totalMaxResources;

	/*Each row is a different troop type, each column is a different tier

	Rows:
	0 = guardsTiers,
	1 = infantryTiers,
	2 = archersTiers,
	3 = cavalryTiers,
	4 = artillaryTiers;

	Cols:
	0 = tier 1
	1 = tier 2
	2 = tier 3
	3 = tier 4
	4 = tier 5
		*/
	

	bool moved;

	/*
		"Resources:      ",
		"Troops present: ",
		"Troops injured: ",
		"Troops lost:    ",
		"Other stats:    "
	*/
	s5array statsOne = {
		"Resources:      ",
		"Troops present: ",
		"Troops injured: ",
		"Troops lost:    ",
		"Other stats:    "
	};

	//Check this
	std::array<s5array, 4> namesOfManOne = {
		INF::RESOURCE_NAMES, 
		INF::TROOP_NAMES
	};

	std::array<std::string, 6> namesOfManTwo{
		 "Total Troops",
		 "Total Army CP",
		 "Commander Level",
		 "Max Troops this army can have",
		 "Army Food consumption",
		 "Max Resources this army can have"
	};

	// check
	i5array costToUpgrade = { 5, 4, 3, 2, 1 };
	bool deleteCommander;
};

#endif