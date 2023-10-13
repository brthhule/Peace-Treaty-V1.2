#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>
#include <random>

#include "AllUnits.h"
#include "CommanderProfile.h"
#include "../Misc/ConstValues.h"
#include "../Interfaces/BuildMA.h"
#include "../Input.h"
#include "../Coordinates.h"
#include "../Buildings.h"


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
	Provinces(int overallIndexArg);

	/*Initialization*/
	bool isCapital() { return isACapital; }
	void makeCapital(int participantIndexArg); // provinceIsACapital

	/*Province Identity*/
	bool deleteStatus();
	void setDeleteProvince() { deleteProvince = true; }

	/*Garrisons*/
	void initializeCapitalStats();

	// Commanders
	CommanderProfile* getCommander(std::string name);
	void addCommander(CommanderProfile* newCommander);
	void removeCommander(CommanderProfile* newCommander);
	std::vector <CommanderProfile*> getAllCommanders();
	int commandersNum() { return (int) commanders.size(); }
	void printCommanders();
	bool hasCommander(std::string name);

	/*Training*/
	
	void addTroopsTrainedThisTurn(int amount);
	void resetTroopsTrainedThisTurn();

	/*Resources*/
	bool subtractCheckResources(std::array<int, 5> resourcesArray);
	std::array<int, 5> getTotalResources();

	/*Stats*/
	int getTotalCP();
	void updateBuildingsProduction();
	void updateProvinceResources();

	


	void playerBuildFunction();
	void upgradeBuildings();
	void upgradeBuildings2(char optionChar);
	template<typename T>
	T upgradeBuildings3(std::array<int, 5>* arrayArg, T name);
	void printInformation(int buildingNumber, std::array<int, 5> requiredResources, std::vector<std::string> buildingLetterList);

	void setKingdomName(std::string name) { kingdomName = name; }
	std::string getKingdomName() { return kingdomName; }
	
	void setOverallIndex(int index);
	int getOverallIndex();

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

	int b;
	int* a = &b;


	
private:
	std::array<std::array<int, 5>*, 7> Lists = {&resourceBuildingsLevels, &otherBuildingsLevels,&resourcesPresent, &troopsPresent, &troopsInjured, &troopsLost, &initialStats};

	//Have to derive unitLevel
	std::array<int*, 7> listInt = {&combatPower, &totalTroops, &foodConsumption, &participantIndex, &unitLevel, &troopsTrainedThisTurn, &overallIndex};

	std::array<bool*, 3> listBool = {&canSelectThisUnit, &isACapital, &deleteProvince};

	bool isACapital;//stat

	bool deleteProvince;//conditional
	int overallIndex;

	std::unordered_map<std::string, CommanderProfile*> commanders;
	std::unordered_map<std::string, CommanderProfile*>::iterator it;

	double newAccuracy;
	std::string kingdomName;
	std::vector<Report> scoutReports;

	friend class Report;

};

class Report {
public:
	Report(int scouterLevelArg, int targetLevelArg, Provinces &province);

	/*Scout Stuff*/
	int getEstimate(int newAccuracy, int quantity);
	int getScoutValue(Provinces::REPORT report);

	void computeAccuracy();
	void attuneValues();
	void getCommanders();
	

private:
	std::array<std::array<int, 5>, 7> Lists;
	std::array<int, 7> listInt;
	std::array<bool, 3> listBool;
	std::array< std::pair<int, int>, 2> listCoords;

	std::vector<CommanderProfile*> commandersPtr;
	std::vector<CommanderProfile> commanders;

	std::string kingdomName;
	int reportTurn;
	int accuracy;
	int targetLevel;
	int scouterLevel;
};
#endif