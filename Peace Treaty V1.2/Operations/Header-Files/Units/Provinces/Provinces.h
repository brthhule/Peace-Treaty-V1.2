//Provinces.h
//Inherits: AllUnits, BuildMA, Buildings

#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>
#include <random>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include ALL_UNITS_HEADER				//Base Class
#include COORDS_BASE_HEADER				//Base Class

#include BUILD_MA_HEADER				//Interface
#include BUILDING_ATTRIBUTES_INT_HEADER	//Interface

#include COMMANDERS_HEADER				//Composition
#include PROVINCE_REPORT_HEADER			//Composition
#include RESOURCE_BUILDINGS_BASE_HEADER	//Composition 

#include INF_HEADER						//Utility
#include INPUT_HEADER					//Utility


using namespace INF;
using namespace Input;
using namespace COMM;
using namespace UNIT;

namespace PROV {
	class Provinces :
		public AllUnits,				//Base Class
		public MABuildINT,				//Interface
		public BuildingAttributesINT	//Interface
	{
	public:
		///////////////////////////////This Class//////////////////////////////
		//----Constructors-----------------------------------------------------
		Provinces(){}
		Provinces(int overallIndexArg);
		~Provinces() {}

		//----Initialization---------------------------------------------------
		bool isCapital();
		bool hasCommander(std::string name);
		bool subtractCheckResources(i5array resourcesArray);

		///Initializes this province as a capital
		void makeCapital(int participantIndexArg);
		/*///Sets this provinces' stats to capital when generating game.
		Sets all buildings to level 1*/
		void initializeCapitalStats();

		///Set the name of this kingdom
		void setKingdomName(std::string name);
		///Set map index of this province
		void setOverallIndex(int index);

		//----Getters----------------------------------------------------------
		///Return shared pointer of commander by name
		commSPTR getCommander(std::string name);
		//Returns vector of commanders in this province
		commSPTRList getAllCommanders();

		///Returns the total amount of Commanders this unit has
		constINT getCommandersNum();
		///Calculates the combat power of this province
		constINT getTotalCP();
		///Get the index of this unit in its Participant's vector?
		constINT getOverallIndex();

		//----Setters----------------------------------------------------------
		
		///Add Commander to this province
		void addCommander(commSPTR newCommander);
		///Remove Commander from this province
		void removeCommander(commSPTR newCommander);
		/*//Update this province's resources at the end of the round.
		Adds the resource production amounts to the resource totals*/
		void updateProvinceResources();

		///Create scout report for this province
		void createReport(int scouterLevelArg, int targetLevelArg);


		///////////////////////////////BuildMA/////////////////////////////////
		//----Printers---------------------------------------------------------
		void printBuildingUpgradeCosts(i5array requiredresources, int buildingindex) override;
		void mainBuildFunction() override,
			selectUpgradeBuilding() override,
			upgradeBuilding(char optionchar) override;

		void setCommandersSortStatus(SortType status);
		SortType getCommandersSortStatus();

		std::string getKingdomName();

		std::array<i5array, 7> getLists();
		std::array<int, 7> getListInt();
		std::array<bool, 3> getListBool();
		std::array< ipair, 2> getListCoords();

		//Scout/report stuff
		std::array<i5array, 4> getGeneralLists();
		std::array<Provinces::troopConditionArray, 3> getTroopsLists();
		std::array<int, 7> getListsInt();

		int getCommanderIndex(commSPTR commander);


		///////////////////////////////BuildingAttributesINT///////////////////
		
		//----Getters----------------------------------------------------------
		i5array& getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount) = 0;
	//Returns an array of Resource/Other buildings levels
		i5array& getTypeLevels(BUILD::BuildingType type) = 0;


		int& getCapacity(BUILD::BuildingsEnum name) = 0;
		/** getTroopsTrainedThisTurn__
			returns the amount of troops trained this turn

				@param void
				@return void
		*/
		int& getTroopsTrainedThisTurn() = 0;
		/** getProvinceLevel__ 
			returns the level of this province by averaging all building levels

				@param void
				@return void
		*/
		int& getProvinceLevel() = 0;

		virtual std::shared_ptr<BuildingsBASE> getBuilding(BUILD::BuildingsEnum name) = 0;
		BuildingsBASE& getBuildingConst(BUILD::BuildingsEnum name) = 0;

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
		virtual void mutateLevel(BuildingsEnum name, MutateDirection direction, int amount) = 0;
		virtual void addTroopsTrainedThisTurn(int amount) = 0;
		virtual void resetTroopsTrainedThisTurn() = 0;
		virtual void initiailizeCapitalBuildings() = 0;
		virtual void initializeEmptyBuildings() = 0;

		//----Printers---------------------------------------------------------
		virtual void printBuildingStats() = 0;
		virtual void printListOfBuildings() = 0;


	protected:
		enum LISTS { RESOURCE_BUILDINGS_LEVELS, OTHER_BUILDINGS_LEVELS, RESOURCES_PRESENT, TROOPS_PRESENT, TROOPS_INJURED, TROOPS_LOST, INITIAL_STATS };

		enum LISTS_INT { CP, TOTAL_TROOPS, FOOD_CONSUMPTION, PARTICIPANT_INDEX, UNIT_LEVEL, TROOPS_TRAINED_THIS_TURN, OVRALL_INDEX };

		enum LIST_BOOL { CAN_SELECT_THIS_UNIT, IS_CAPITAL, DELETE_PROVINCE };

		enum LIST_COORDS { SYSTEM_COORDS, USER_COORDS };

		enum REPORT { REPORT_TURN, REPORT_LOG };

	private:
		SortType commandersSortType;

		std::array<bool*, 2> listBool = {
			&canSelectThisUnit,
			&isACapital,
		};

		bool isACapital;

		int overallIndex;

		commMAP::iterator it;
		commMAP commandersMap;
		commSPTRList commandersVector;

		double newAccuracy;
		std::string kingdomName;

		//Index within reports is the report. Index of report object is the participant the report belongs to
		typedef std::vector<std::pair<int, ProvinceReport >> reports;
		std::vector<reports> scoutReports;
		std::array<BuildingsBASE, 10> buildings;
	};

	using provSPTR = std::shared_ptr<Provinces>;
	using provMAP = std::unordered_map<std::string, provSPTR>;
	using provSPTRList = std::vector<provSPTR>;
	
}
#endif
