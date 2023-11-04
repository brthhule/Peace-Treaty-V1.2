#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>
#include <random>

#include "AllUnits.h"
#include "CommanderProfile.h"
#include "../Misc/CV.h"
#include "../Interfaces/BuildMA.h"
#include "../Input.h"
#include "../Coords.h"
#include "../Buildings.h"
#include "../ProvinceReport.h"


#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

using namespace CV;
using namespace Input;

extern const int BARRACKS_PRODUCTION;
const int LOG_SIZE = 20;

class Provinces : public AllUnits, public BuildMA, public Buildings
{
public:
	/*Constructors*/

	Provinces();
	Provinces(int overallIndexArg);

	/*Initialization*/
	bool 
		isCapital(),
		deleteStatus(),
		hasCommander(std::string name),
		subtractCheckResources(std::array<int, 5> resourcesArray);

	// Commanders
	CommanderProfile* getCommander(std::string name);
	std::vector <CommanderProfile*> getAllCommanders();

	int 
		commandersNum(),
		getTotalCP(),
		getOverallIndex();
		
	
	std::array<int, 5> getTotalResources();

	void
		makeCapital(int participantIndexArg),
		initializeCapitalStats(),

		addCommander(CommanderProfile* newCommander),
		removeCommander(CommanderProfile* newCommander),
		printCommanders(),
		printInformation(Build::BuildingType type, std::array<int, 5> requiredresources, int buildingindex),
		updateProvinceResources(),
		playerBuildFunction(),
		upgradeBuildings(),
		upgradeBuildings2(char optionchar),
		setKingdomName(std::string name),
		setOverallIndex(int index),


		createReport(int scouterLevelArg, int targetLevelArg);


		

	//type (resource, other), other/resourceLevels, name of object in Levels list
	void upgradeBuildings3(Build::BuildingType type, std::array<int, 5>* listArg, int name);

	std::string getKingdomName() { return kingdomName; }
	
	std::array<std::array<int, 5>, 7> getLists();
	std::array<int, 7> getListInt();
	std::array<bool, 3> getListBool();
	std::array< std::pair<int, int>, 2> getListCoords();

	std::pair<int, int> translateToSystemCoords(std::pair<int, int> userCoordsArg);

protected:
	enum LISTS {RESOURCE_BUILDINGS_LEVELS, OTHER_BUILDINGS_LEVELS, RESOURCES_PRESENT, TROOPS_PRESENT, TROOPS_INJURED, TROOPS_LOST, INITIAL_STATS};

	enum LISTS_INT{CP, TOTAL_TROOPS, FOOD_CONSUMPTION, PARTICIPANT_INDEX, UNIT_LEVEL, TROOPS_TRAINED_THIS_TURN, OVRALL_INDEX};

	enum LIST_BOOL {CAN_SELECT_THIS_UNIT, IS_CAPITAL, DELETE_PROVINCE};

	enum LIST_COORDS {SYSTEM_COORDS, USER_COORDS};

	enum REPORT {REPORT_TURN, REPORT_LOG};
	
private:
	std::array<std::array<int, 5>*, 12> Lists = {
		&resourceBuildingsLevels, 
		&otherBuildingsLevels,
		&resourcesPresent,
		&troopsPresent, 
		&troopsInjured, 
		&troopsLost,
		&initialStats,
		&allGuards,
		&allInfantry,
		&allArchers,
		&allCavalry,
		&allArtillary
	};

	//Have to derive unitLevel
	std::array<int*, 7> listInt = {
		&combatPower, 
		&totalTroops,
		&foodConsumption, 
		&participantIndex, 
		&unitLevel, 
		&troopsTrainedThisTurn, 
		&overallIndex
	};

	std::array<bool*, 2> listBool = {
		&canSelectThisUnit, 
		&isACapital,
	};

	bool isACapital;

	int overallIndex;

	std::unordered_map<std::string, CommanderProfile*> commanders;
	std::unordered_map<std::string, CommanderProfile*>::iterator it;

	double newAccuracy;
	std::string kingdomName;

	
	//Index within reports is the report. Index of report object is the participant the report belongs to
	typedef std::vector<std::pair<int, ProvinceReport >> reports;
	std::vector<reports> scoutReports;
};
#endif