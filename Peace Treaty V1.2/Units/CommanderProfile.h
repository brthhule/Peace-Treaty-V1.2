#ifndef COMMANDERPROFILE_H
#define COMMANDERPROFILE_H

#include <vector>

#include "AllUnits.h"
#include "../Misc/ConstValues.h"

extern int turn;

using namespace CV;


class CommanderProfile : public AllUnits {
public:
	// Constructors
	CommanderProfile();
	CommanderProfile(int commanderLevel, std::string name);
	// Destructor
	~CommanderProfile();



	// Stats stuff
	int
		getCommanderStat(int index),
		printCommanderScoutReport(int idex);
	void
		printCommanderStats(),
		setLocation(std::array<int, 2> pCoords),

		updateCommanderScoutReport(int index, int value),
		completeCommanderScoutReport(int accuracy),

		printCosts(std::array<int, 5> costs),
		addLevel(),
		setDelete();

	std::array<int, 5> getUpgradeCosts();
	
	bool
		getDelete(),
		hasMovedQuestion();

	// Moving
	void 
		resetCommanderMoved(),
		calculateCommanderScoutLog();

private:
	int 
		maxTroops,
		totalMaxResources, 
		commanderIndex;

	bool hasMoved;

	std::array<std::string, 5> MANDescriptions = {
		"Resources in",
		"Troops present in",
		"Troops injured in",
		"Troops lost in",
		"Other stats of"
	};

	//Check this
	std::array<std::array<std::string, 5>, 4> namesOfManOne = {
		CV::RESOURCE_NAMES, 
		CV::TROOP_NAMES
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
	int costToUpgrade[5] = { 5, 4, 3, 2, 1 };
	bool deleteCommander;
};

#endif