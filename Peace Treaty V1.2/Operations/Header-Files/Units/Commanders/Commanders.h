///Commanders.h
///Derived Class
/// Extends AllUnits (Extends Coords)

#ifndef COMMANDERS_H
#define COMMANDERS_H

#include <vector>
#include <unordered_map>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PRIME_UNITS_HEADER				//Base Class

using namespace UNIT;

///Namespace for Commanders
namespace COMM {

	//Control army units
	class Commanders : public AllUnits {
	public:
		//----Constructors-----------------------------------------------------
		Commanders();
		Commanders(int commanderLevel, std::string name);
		~Commanders();

		//----Getters----------------------------------------------------------
		constINT getCommanderStat(int index);
		bool hasMoved();
		const std::string& getCommanderNameLevel();
		constI5array getUpgradeCosts();

		//----Printers---------------------------------------------------------
		void printCommanderStats();
		//Print commander name and level then enter new line escape character
		void printCommanderNameLevel();
		void printCosts(i5array costs);

		void addLevel();
		void resetCommanderMoved();
		void calculateCommanderScoutLog();

	private:
		int
			maxTroops,
			totalMaxResources;

		bool moved;

		/*	"Resources:      ",
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

	/*Commanders shared pointer 
	Expanded: std::shared_ptr<Commanders>*/
	using commSPTR = std::shared_ptr<Commanders>;
	/*Commanders unordered map; key: name, value: Commander
	Expanded: std::unordered_map<std::string, commSPTR>*/
	using commMAP = std::unordered_map<std::string, commSPTR>;
	/*Vector of Commanders shared pointers
	Expanded: std::vector<commSPTR>*/
	using commSPTRList = std::vector<commSPTR>;
}
#endif