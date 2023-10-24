#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <iostream>
#include <vector>

#include <string.h>
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>  
#include <ctime>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <map>
#include <unordered_map>

#include "AllUnits.h"
#include "Provinces.h"
#include "CommanderProfile.h"

#include "../Misc/OF.h"
#include "../Misc/ConstValues.h"
#include "../Misc/LinkedList.h"

#include "Map.h"


using namespace CV;

class Participants : Map
{
public:
	//constructors
	Participants(int pIndex);
	
	std::array<int, 5> 
		getTrainCosts(),
		calculateEach(int option);

	std::unordered_map<std::string, CommanderProfile*> getCommandersMap() { return commandersMap; }

	

	bool 
		subtractCheckResources(std::string provinceName, std::array<int, 5> resourcesArray),
		hasProvince(std::string name),
		hasCommander(std::string name);

	std::string 
		getKingdomName(),
		selectCommander(),
		getNewName();

	//AI
	void
		setCapital(Provinces* newProvince),
		showMapOld(),

		addCommander(),
		addProvince(Provinces* newProvince),
		printListOfProvinces(),

		createAsPlayer(bool status),
		setPlayerStatus(bool status),
		viewAllStatsFunction(),
		viewStats(),
		scoutProvince(Provinces* targetProvince, int accuracy),
		displayCommanders(),
		initialCapRSS(),

		setParticipantIndex(int num),
		setKingdomName(std::string newName),
		showMap();
		


	bool 
		isAlive(),
		isPlayer(),
		hasUnit (std::string unitName);

	//Stats
	std::vector<int> calculatePlayerValues(int decision);

	int 
		calculateTotals(int option),
		getRandomCoordinate(),
		provincesNum(),
		commandersNum(),

		findAllUnits(),//Create funciton
		getParticipantIndex();


	//Coordinate stuff
	Provinces 
		*getYourProvince(int identifier),
		*findProvince(),
		*getProvinceByName(std::string name),
		*findProvince(std::pair<int, int> userCoords),
		*getProvince(int index),
		*getCapitalProvince();


	CommanderProfile
		* getCommander(std::string name),
		* getSelectedCommander();

	Provinces *getSystemProvince(std::pair<int, int> systemCoords),
			  *getCoords(int identifer);


private:
	std::string kingdomName = " ";
	bool playerStatus;//true = player, false = AI

	std::vector <Provinces*> provincesVector;
	std::unordered_map <std::string, CommanderProfile*> commandersMap;
	std::unordered_map <std::string, Provinces*> provincesMap;
	std::vector <CommanderProfile> commandersVector;

	int 
		capitalIndex,
		participantIndex;

	//Figure out sizes later
	int AIMainAction[5];
	int AIBuildMA[2];
	int AITroopMA[3];
	std::array <int, 5> 
		trainCosts = { 5, 4, 3, 2, 1 },
		troopsLost = { 0,0,0,0,0 };

	std::unordered_map<std::string, CommanderProfile*>::iterator it;
	Provinces* capitalProvince;

	CommanderProfile* selectedCommander; //For ArmyDeploymentMA
};
#endif
