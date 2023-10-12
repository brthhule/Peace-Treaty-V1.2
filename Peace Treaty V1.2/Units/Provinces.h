#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>

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

	/*Scout Stuff*/
	void completeProvinceScoutReport(int accuracy, Provinces* targetProvince, int scoutTurn);
	int getEstimate(int newAccuracy, int quantity);
	int getScoutReportTurn() { return scoutReportTurn; }
	int getScoutLogTurnLevel() { return scoutReportLogLevel; }


	void playerBuildFunction();
	void upgradeBuildings();
	void upgradeBuildings2(char option);
	void printInformation(int buildingNumber, std::array<int, 5> requiredResources, std::vector<std::string> buildingLetterList);

	void setKingdomName(std::string name) { kingdomName = name; }
	std::string getKingdomName() { return kingdomName; }
	
	void setOverallIndex(int index);
	int getOverallIndex();

private:
	bool isACapital;//stat

	bool deleteProvince;//conditional
	int overallIndex;

	std::unordered_map<std::string, CommanderProfile*> commanders;
	std::unordered_map<std::string, CommanderProfile*>::iterator it;

	int scoutReportTurn;
	int scoutReportLogLevel;
	int logAccuracy;
	double newAccuracy;
	int linkedListNumber;
	std::string kingdomName;


};

#endif