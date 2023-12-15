#ifndef COMMANDERS_H
#define COMMANDERS_H

#include <vector>
#include <unordered_map>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include ALL_UNITS_HEADER
#include INF_HEADER

using namespace INF;

//Namespace for Commanders
namespace COMM {

	//Control army units
	class Commanders : public AllUnits {
	public:
		// Constructors
		Commanders();
		Commanders(int commanderLevel, std::string name);
		~Commanders();

		// Stats stuff
		const int& getCommanderStat(int index);

		void
			printCommanderStats(),

			printCosts(i5array costs),
			addLevel(),
			resetCommanderMoved(),
			calculateCommanderScoutLog();

		i5array getUpgradeCosts();

		bool hasMoved();
		const std::string& getCommanderNameLevel();

		//Print commander name and level then enter new line escape character
		void printCommanderNameLevel();

	private:
		INF::INTEGER
			maxTroops,
			totalMaxResources;

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

	//Commanders shared pointer
	using commSPTR = std::shared_ptr<Commanders>;
	/*std::unordered_map, key = commander name, value = commander shared pointer*/
	using commMAP = std::unordered_map<std::string, commSPTR>;
	using commSPTRList = std::vector<commSPTR>;
}
#endif