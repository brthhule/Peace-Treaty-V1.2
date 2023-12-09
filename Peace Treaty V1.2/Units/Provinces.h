//Provinces.h
//Inherits: AllUnits, BuildMA, Buildings

#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>
#include <random>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"

#include ALL_UNITS_HEADER
#include COMMANDERS_HEADER
#include INF_HEADER
#include MA_BUILD_INT_HEADER
#include INPUT_HEADER


#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include PROVINCES_HEADER
#include INF_HEADER
#include COORDS_HEADER
#include BUILDING_ATTRIBUTES_INT_HEADER
#include PROVINCE_REPORT_HEADER
#include RESOURCE_BUILDINGS_BASE_HEADER

using namespace INF;
using namespace Input;

extern const int BARRACKS_PRODUCTION;
const int LOG_SIZE = 20;

class Provinces : public AllUnits, public MABuildINT, public BuildingAttributesINT
{
public:
	using CommandersSPtr = std::shared_ptr<Commanders>;
	using commandersMapType = std::unordered_map<std::string, CommandersSPtr>;
	using ProvinceSPtr = std::shared_ptr<Provinces>;
	/*Constructors*/
	Provinces();
	Provinces(int overallIndexArg);

	/*Initialization*/
	bool 
		isCapital(),
		hasCommander(std::string name),
		subtractCheckResources(std::array<int, 5> resourcesArray);

	// Commanders
	Commanders* getCommander(std::string name);
	std::vector <Commanders*> getAllCommanders();

	int 
		getCommandersNum(),
		getTotalCP(),
		getOverallIndex();
		
	
	i5array getTotalResources();

	void
		makeCapital(int participantIndexArg),
		initializeCapitalStats(),

		addCommander(Commanders* newCommander),
		removeCommander(Commanders* newCommander),
		printCommanders(),
		updateProvinceResources(),
		
		setKingdomName(std::string name),
		setOverallIndex(int index),


		createReport(int scouterLevelArg, int targetLevelArg);

	////////////////MABuildINT///
	void printBuildingUpgradeCosts(i5array requiredresources, int buildingindex),
		mainBuildFunction(),
		selectUpgradeBuilding(),
		upgradeBuilding(char optionchar);
		
	//////////////End MABuildINT///
	//type (resource, other), other/resourceLevels, name of object in Levels list

	void setCommandersSortStatus(SortType status);
	SortType getCommandersSortStatus();

	std::string getKingdomName();
	
	std::array<i5array, 7> getLists();
	std::array<int, 7> getListInt();
	std::array<bool, 3> getListBool();
	std::array< std::pair<int, int>, 2> getListCoords();

	//Scout/report stuff
	std::array<std::array<int, 5>, 7> getGeneralLists();
	std::array<Provinces::troopConditionArray, 3> getTroopsLists();
	std::array<int, 5> getListsInt() {


protected:
	enum LISTS {RESOURCE_BUILDINGS_LEVELS, OTHER_BUILDINGS_LEVELS, RESOURCES_PRESENT, TROOPS_PRESENT, TROOPS_INJURED, TROOPS_LOST, INITIAL_STATS};

	enum LISTS_INT{CP, TOTAL_TROOPS, FOOD_CONSUMPTION, PARTICIPANT_INDEX, UNIT_LEVEL, TROOPS_TRAINED_THIS_TURN, OVRALL_INDEX};

	enum LIST_BOOL {CAN_SELECT_THIS_UNIT, IS_CAPITAL, DELETE_PROVINCE};

	enum LIST_COORDS {SYSTEM_COORDS, USER_COORDS};

	enum REPORT {REPORT_TURN, REPORT_LOG};
	
private:
	SortType commandersSortType;

	std::array<bool*, 2> listBool = {
		&canSelectThisUnit, 
		&isACapital,
	};

	bool isACapital;

	int overallIndex;


	commandersMapType commandersMap;
	std::vector<CommandersSPtr> commandersVector;

	double newAccuracy;
	std::string kingdomName;

	
	//Index within reports is the report. Index of report object is the participant the report belongs to
	typedef std::vector<std::pair<int, ProvinceReport >> reports;
	std::vector<reports> scoutReports;
};
#endif