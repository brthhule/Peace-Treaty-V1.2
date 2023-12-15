//Provinces.h
//Inherits: AllUnits, BuildMA, Buildings

#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>
#include <random>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include ALL_UNITS_HEADER 
#include COMMANDERS_HEADER
#include INF_HEADER
#include BUILD_MA_HEADER
#include INPUT_HEADER

#include INF_HEADER
#include COORDS_BASE_HEADER
#include BUILDING_ATTRIBUTES_INT_HEADER
#include PROVINCE_REPORT_HEADER
#include RESOURCE_BUILDINGS_BASE_HEADER

using namespace INF;
using namespace Input;
using namespace COMM;

namespace PROV {
	class Provinces :
		EXTENDS_
		BASE_CLASS public AllUnits,
		BASE_CLASS public CoordsBASE,
		IMPLEMENTS_
		INTERFACE public MABuildINT,
		INTERFACE public BuildingAttributesINT
		COMPRISES_
		COMMANDERS_
		PROVINCE_REPORT_
		RESOURCES_BUILDINGS_BASE_
		USES_
		INF_
		INPUT_
	{
	public:
		CONSTRUCTOR
			Provinces(int overallIndexArg);

			/*Initialization*/
		bool
			isCapital(), 
			hasCommander(std::string name),
			subtractCheckResources(i5array resourcesArray);

		// Commanders
		commSPTR getCommander(std::string name);
		commSPTRList getAllCommanders();

		const int&
			getCommandersNum(),
			getTotalCP(),
			getOverallIndex();


		i5array getTotalResources();

		void
			makeCapital(int participantIndexArg),
			initializeCapitalStats(),

			addCommander(commSPTR newCommander),
			removeCommander(commSPTR newCommander),
			printCommanders(),
			updateProvinceResources(),

			setKingdomName(std::string name),
			setOverallIndex(int index),


			createReport(int scouterLevelArg, int targetLevelArg);

		BUILD_MA_ INTERFACE START
			void
			printBuildingUpgradeCosts(i5array requiredresources, int buildingindex) override,
			mainBuildFunction() override,
			selectUpgradeBuilding() override,
			upgradeBuilding(char optionchar) override;
		BUILD_MA_ INTERFACE END

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
	};

	using provSPTR = std::shared_ptr<Provinces>;
	using provMAP = std::unordered_map<std::string, provSPTR>;
	using provSPTRList = std::vector<provSPTR>;

}
#endif
