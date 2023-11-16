#ifndef COMMANDERPROFILE_H
#define COMMANDERPROFILE_H

#include <vector>

#include "AllUnits.h"
#include "Misc/INF.h"

using namespace INF;


class Commanders : public AllUnits {
public:
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
	
	bool
		getDelete(),
		hasMoved();

private:
	INTEGER 
		maxTroops,
		totalMaxResources, 

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