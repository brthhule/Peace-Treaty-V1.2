//Provinces.h
//Inherits: AllUnits, BuildMA, Buildings

#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>
#include <random>

#include "AllUnits.h"
#include "Commanders.h"
#include "Misc/INF.h"
#include "ProvincesAttributes/MABuildINT.h"
#include "Misc/Input.h"
#include "AllUnitsAttributes/Coords.h"
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\ProvincesAttributes\BuildingAttributesINT.h"
#include "Reports/ProvinceReport.h"


#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

using namespace INF;
using namespace Input;

extern const int BARRACKS_PRODUCTION;
const int LOG_SIZE = 20;

class Provinces : public AllUnits, public MABuildINT, public BuildingAttributesINT
{
public:
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
		
	
	std::array<int, 5> getTotalResources();

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
	void printInformation(BUILD::BuildingType type, i5array requiredresources, int buildingindex),
		playerBuildFunction(),
		upgradeBuildings(),
		upgradeBuildings2(char optionchar);

	void upgradeBuildings3(BUILD::BuildingType type, INF::i5array* listArg, int name);
		
	//////////////End MABuildINT///
	//type (resource, other), other/resourceLevels, name of object in Levels list
	

	std::string getKingdomName() { return kingdomName; }
	
	std::array<std::array<int, 5>, 7> getLists();
	std::array<int, 7> getListInt();
	std::array<bool, 3> getListBool();
	std::array< std::pair<int, int>, 2> getListCoords();

protected:
	enum LISTS {RESOURCE_BUILDINGS_LEVELS, OTHER_BUILDINGS_LEVELS, RESOURCES_PRESENT, TROOPS_PRESENT, TROOPS_INJURED, TROOPS_LOST, INITIAL_STATS};

	enum LISTS_INT{CP, TOTAL_TROOPS, FOOD_CONSUMPTION, PARTICIPANT_INDEX, UNIT_LEVEL, TROOPS_TRAINED_THIS_TURN, OVRALL_INDEX};

	enum LIST_BOOL {CAN_SELECT_THIS_UNIT, IS_CAPITAL, DELETE_PROVINCE};

	enum LIST_COORDS {SYSTEM_COORDS, USER_COORDS};

	enum REPORT {REPORT_TURN, REPORT_LOG};
	
private:
	std::array<std::array<int, 5>*, 7> Lists;

	std::array<std::array<i5array, 5>, 3> troopsLists;

	//Have to derive unitLevel
	std::array<int*, 7> listInt;

	std::array<bool*, 2> listBool = {
		&canSelectThisUnit, 
		&isACapital,
	};

	bool isACapital;

	int overallIndex;

	std::unordered_map<std::string, Commanders*> commanders;
	std::unordered_map<std::string, Commanders*>::iterator it;

	double newAccuracy;
	std::string kingdomName;

	
	//Index within reports is the report. Index of report object is the participant the report belongs to
	typedef std::vector<std::pair<int, ProvinceReport >> reports;
	std::vector<reports> scoutReports;
};
#endif