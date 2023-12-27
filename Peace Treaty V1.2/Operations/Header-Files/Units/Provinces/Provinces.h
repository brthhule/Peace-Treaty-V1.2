//Provinces.h
//Inherits: PrimeUnits, BuildMA, Buildings

#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>
#include <random>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"


#include BUILD_MA_HEADER				//Interface
#include BUILDING_ATTRIBUTES_INT_HEADER	//Interface

#include COMMANDERS_HEADER				//Composition
/*	#include PRIME_UNITS_HEADER					//Base Class
		#include COORDS_BASE_HEADER				//Base Class
			#include INF_HEADER
		#include TROOP_UNITS_BASE_HEADER		//Composition
			#include TROOP_HEADER
		#include TROOPS_INT_HEADER				//Interface
			#include TROOP_HEADER
*/

#include PROVINCE_REPORT_HEADER			//Composition
#include RESOURCE_BUILDINGS_BASE_HEADER	//Composition 

#include INPUT_HEADER					//Utility

#include FARM_HEADER
#include MILL_HEADER
#include MINE_HEADER
#include QUARRY_HEADER
#include CHURCH_HEADER

#include BARRACKS_HEADER
#include INFIRMARY_HEADER
#include LIBRARY_HEADER
#include RESIDENCES_HEADER 
#include WALL_HEADER

using namespace INF;
using namespace Input;
using namespace COMM;
using namespace UNIT;

namespace PROV {
	class Provinces :
		public PrimeUnits,				//Base Class
		public BuildMA,				//Interface
		public BuildingAttributesINT	//Interface
	{
	public:
		///////////////////////////////This Class//////////////////////////////
		//----Constructors-----------------------------------------------------
		Provinces(int mapIndex, int participantIndex);
		~Provinces() {}

		//----Initialization---------------------------------------------------
		bool isCapital() const;
		bool hasCommander(std::string name);
		/*Subtracts the necessary resources from capital province. If resources left over are all positive (there were enough resources), return true. If any resources are negative, return false*/
		bool subtractCheckResources(constArrayReference resourcesArray);

		///Initializes this province as a capital
		void makeCapital(int participantIndexArg);
		/*///Sets this provinces' stats to capital when generating game.
		Sets all buildings to level 1*/
		void initializeCapitalStats();

		///Set the name of this kingdom
		void setKingdomName(std::string name);
		///Set map index of this province

		//----Getters----------------------------------------------------------
		///Return shared pointer of commander by name
		commSPTR getCommander(std::string name) const;
		//Returns vector of commanders in this province
		commSPTRList getAllCommanders() const;

		///Returns the total amount of Commanders this unit has
		int getCommandersNum() const;
		///Calculates the combat power of this province
		int getTotalCP() const;
		///Get the index of this unit in its Participant's vector?
		constINT getMapIndex() const;

		Commanders& getProvinceCommander() const;
		constINT getLevel() const override;

		//----Setters----------------------------------------------------------
		
		///Add Commander to this province and change Commander corods to here
		void addCommander(Commanders newCommander);
		///Remove Commander from this province
		void removeCommander(commSPTR newCommander);
		/*//Update this province's resources at the end of the round.
		Adds the resource production amounts to the resource totals*/
		void updateProvinceResources();

		///Create scout report for this province
		void createReport(int scouterLevelArg, int targetLevelArg);

		void printCommanders();


		///////////////////////////////BuildMA/////////////////////////////////
		//----Printers---------------------------------------------------------
		void printBuildingUpgradeCosts(i5array requiredresources, int buildingindex) override;
		void upgradeBuildingPrompt() override,
			selectBuildingToUpgrade() override,
			upgradeBuilding(int buildingNumber) override;

		void setCommandersSortStatus(SortType status);
		SortType getCommandersSortStatus() const;

		std::string getKingdomName();

		std::array<i5array, 7> getLists();
		std::array<int, 7> getListInt();
		std::array<bool, 2> getListBool();
		std::array< ipair, 2> getListCoords();

		//Scout/report stuff
		std::array<i5array, 4> getGeneralLists();
		std::array<int, 7> getListsInt();

		int getCommanderIndex(commSPTR commander);

		//Implement these, add them to PrimeUnits later on
		void calculateCombatPower();
		void calculateFoodConsumption();
		///////////////////////////////PrimeUnits.h////////////////////////////
		constINT getCombatPower() const override;
		constINT getFoodConsumption() const override;
		///////////////////////////////BuildingAttributesINT///////////////////
		
		//----Getters----------------------------------------------------------
		i5array& getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount);
	//Returns an array of Resource/Other buildings levels
		i5array getTypeLevels(BUILD::BuildingType type);


		constINT getCapacity(BUILD::BuildingsEnum name);
		/** getTroopsTrainedThisTurn__
			returns the amount of troops trained this turn

				@param void
				@return void
		*/
		constINT getTroopsTrainedThisTurn();
		/** getProvinceLevel__ 
			returns the level of this province by averaging all building levels

				@param void
				@return void
		*/
		constINT getProvinceLevel();

		std::shared_ptr<BuildingsBASE> getBuilding(BUILD::BuildingsEnum name);

		//----Setters----------------------------------------------------------
		/** mutateLevel__
			Changes the level of a building

				@param name__
			the name of the building being changed
				@param direction__
			changing the level in an increasing/decreasing direction
				@param amount__
			the amount the level is being changed by, usually 1, always positive
				@return void
		*/
		void mutateLevel(BuildingsEnum name, MutateDirection direction, int amount);
		void addTroopsTrainedThisTurn(int amount);
		void resetTroopsTrainedThisTurn();
		void initiailizeCapitalBuildings();
		void initializeEmptyBuildings();

		//----Printers---------------------------------------------------------
		void printBuildingStats();
		void printListOfBuildings();

	protected:
		enum LISTS { RESOURCE_BUILDINGS_LEVELS, OTHER_BUILDINGS_LEVELS, RESOURCES_PRESENT, TROOPS_PRESENT, TROOPS_INJURED, TROOPS_LOST, INITIAL_STATS };

		enum LISTS_INT { CP, TOTAL_TROOPS, FOOD_CONSUMPTION, PARTICIPANT_INDEX, UNIT_LEVEL, TROOPS_TRAINED_THIS_TURN, OVRALL_INDEX };

		enum LIST_bool{ CAN_SELECT_THIS_UNIT, IS_CAPITAL, DELETE_PROVINCE };

		enum LIST_COORDS { SYSTEM_COORDS, USER_COORDS };

		enum REPORT { REPORT_TURN, REPORT_LOG };

	private:
		SortType commandersSortType;
		bool isACapital;

		int mapIndex;

		commMAP::iterator it;
		commMAP commandersMap;
		std::vector<Commanders> commandersVector; //Commanders live here
		///The main commander at this province
		commSPTR provinceCommander;

		double newAccuracy;
		std::string kingdomName;

		//Index within reports is the report. Index of report object is the participant the report belongs to
		typedef std::vector<std::pair<int, ProvinceReport >> reports;
		std::vector<reports> scoutReports;
		std::array<std::unique_ptr<BuildingsBASE>, 10> buildings;

		Farm farm;
		Mill mill;
		Quarry quarry;
		Mine mine;
		Church church;
		Barracks barracks;
		Infirmary infirmary;
		Library library;
		Residences residences;
		Wall wall;
	};

	using provSPTR = std::shared_ptr<Provinces>;
	using provMAP = std::unordered_map<std::string, provSPTR>;
	using provSPTRList = std::vector<provSPTR>;
	
}
#endif
