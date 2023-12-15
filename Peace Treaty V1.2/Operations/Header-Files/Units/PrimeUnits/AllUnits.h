#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include COORDS_BASE_HEADER
#include INF_HEADER
#include TROOP_UNITS_BASE_HEADER

using namespace INF;

namespace UNIT {
	BASE_CLASS
		class AllUnits : public CoordsBASE
	{
	public:
		

		//----Constructors----
		//One param overloaded Constructor
		AllUnits(int index);
		//Default Constructor
		AllUnits();

		const int& getCP();
		const int& getParticipantIndex();
		const int& getLevel();
		const int& getFoodConsumption();
		const int& getResource(int resourceIndex);


		//resources
		void modifySpecificResource(int index, int amount, bool isAdd);
		void modifyResources(i5array resourcesArray, INF::MutateDirection direction);

		void printResources();
		void changeUnitName(std::string name);
		void changeParticipantIndex(int number);
		void printTroopsPresent();

		i5array getAllResources();//Add implementation


		std::string getUnitName();
		void printResources(i5array resourcesArray);

		/*Return all the tiers for one troop type for a particular condition
		Example: returns all tiers for guards present*/
		i5array getAllOneTroopArray(TroopCondition troopCondition, TroopUnitsBASE::TroopTypes type);

		/*Returns the total of all of a particular troop type's tiers for a particular condition
		Example: returns the total of all tiers for guards present*/
		int getAllOneTroopInt(TroopCondition troopCondition, TroopUnitsBASE::TroopTypes type);

		/*Returns the tier totals for all troop types for a particular condition
		Example: returns the total of all tiers of all troops presnet, as in the totals for guards, infantry, archers, etc.*/
		i5array getGenericTroops(TroopCondition type);


		/*Change a troop by index or all trypes.
		TroopCondition: REGULAR, INJURED, LOST
		TroopUnitsBASE::TroopTypes: GUARDS, INFANTRY, ARCHERS, CAVALRY, ARTILLARY
		amount: {a,b,c,d,e} or {a}
		Quantitiy: SINGLE, ALL
		MutateDirection: DECREASE, INCREASE
		troopTier: 1/2/3/3/4/5*/
		void mutateTroop(
			INF::TroopCondition troopCondition,
			TroopUnitsBASE::TroopTypes type,
			i5array amount,
			Quantity quant,
			INF::MutateDirection direction,
			int troopTier);

		void setBattleFormation(troopConditionArray troopArray);

		//Override?
		INF::ipair translateCoords(INF::ipair coords, CoordsType type);

		std::vector<unitSPTR > sortVector(SortType sort, std::vector<unitSPTR > list);
		std::vector<unitSPTR > levelSort(unitSPTR  list);

	protected:
		i5array resourcesPresent;
		i5array initialStats;

		int combatPower;
		int totalTroops;
		int foodConsumption;
		int participantIndex;
		int unitLevel;


		troopConditionArray troopsPresent;
		troopConditionArray troopsInjured;
		troopConditionArray troopsLost;


		std::array<troopConditionArray*, 3> allTroopConditions;

		std::array<std::vector<TroopUnitsBASE>, 5> battleFormation;


		//Coordinates;

		bool canSelectThisUnit;

		UnitType type;
		std::string unitName;
		TroopUnitsBASE troops;
	};

	enum UnitType { COMMANDER, PROVINCE };
	using T5array = INF::Array5<TroopUnitsBASE>;
	using unitSPTR = std::shared_ptr<AllUnits>;
	using troopConditionArray = INF::Array5<T5array>;
	using unitSPTR = std::shared_ptr<AllUnits>;
}
#endif