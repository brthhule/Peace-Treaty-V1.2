///Commanders.h
///Derived Class
/// Extends PrimeUnits (Extends Coords)

#ifndef COMMANDERS_H
#define COMMANDERS_H

#include <vector>
#include <unordered_map>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"


#include PRIME_UNITS_HEADER					//Base Class
#include COORDS_BASE_HEADER				//Base Class
#include INF_HEADER
#include TROOP_UNITS_BASE_HEADER		//Composition
#include TROOP_HEADER
#include TROOPS_INT_HEADER				//Interface
#include TROOP_HEADER



///Namespace for Commanders
namespace COMM {
	extern INF::s5array statsOne;

	//Check this
	extern std::array<INF::s5array, 4> namesOfManOne;
	extern std::array<std::string, 6> namesOfManTwo;

	//Control army units
	class Commanders : public UNIT::PrimeUnits, public TroopsINT {

		
	public:
		//----Constructors-----------------------------------------------------
		Commanders();
		Commanders(int commanderLevel, std::string name, int participantIndex);
		~Commanders();

		//----Getters----------------------------------------------------------
		int getCommanderStat(int index);
		bool hasMoved() const;
		const INF::i5array getUpgradeCosts();
		const int& getIndexInProvince() const;
		

		//----Printers---------------------------------------------------------
		void printCommanderStats();
		//Print commander name and level then enter new line escape character

		void addLevel();
		void resetCommanderMoved();
		void calculateCommanderScoutLog();

		void setIndexInProvince(int index);

		///////////////////////////////PrimeUnits.h////////////////////////////
		INF::constINT getCombatPower() const override;
		void calculateFoodConsumption() override;
		INF::constINT getFoodConsumption() const override;
		INF::constINT getLevel() const override;

		///////////////////////////////TroopsINT.h/////////////////////////////
		void printTroopsPresent() ;
		std::array<troopsArray, 3>& getTroopConditions();
		//----Getters--------------------------------------------------------------
	
		tiersArray& getAllTiersOfTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes type);
		int getSumOfTiersOfTroop(TROOP::TroopCondition troopCondition, TROOP::TroopTypes type);

		INF::i5array getArrayOfSumsOfTiersOfAllTroops(TROOP::TroopCondition type);

		//----Mutators-------------------------------------------------------------
		void mutateTroop(
			TROOP::TroopCondition troopCondition,
			TROOP::TroopTypes type,
			troopsArray amount,
			INF::Quantity quant,
			INF::MutateDirection direction,
			int troopTier);

		///Set the battle formation for... battle
		void setBattleFormation(troopsArray troopArray);

	private:
		int maxTroops;
		int totalMaxResources;

		bool moved;
		// check
		INF::i5array costToUpgrade = { 5, 4, 3, 2, 1 };
		bool deleteCommander;

		///PRESENT = 0, INJURED = 1, LOST = 2
		std::array<troopsArray, 3> troopConditions;
		std::array<std::array<std::vector<TroopUnitsBASE>, 5>, 5> battleFormation;

		int indexInProvince;
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