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


using namespace CV;

class Participants
{
public:
	//constructors
	Participants(int pIndex);
	
	std::array<int, 5> 
		getTrainCosts(),
		calculateEach(int option);

	std::unordered_map<std::string, CommanderProfile*> getCommandersMap() { return commandersList; }

	

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
		showMapCoordinates(),

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
		createCapital(),
		setParticipantIndex(int num),
		setKingdomName(std::string newName);


	bool 
		isAlive(),
		isPlayer();

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
		*getCoords(int identifier),
		*getYourProvince(int identifier),
		*findProvince(),
		*getProvinceByName(std::string name),
		*getErrorProvince(),
		*findProvince(int x, int y),
		*getProvince(int index),
		*getCapital();


	CommanderProfile
		* getCommander(std::string name),
		* getSelectedCommander();


private:
	std::string kingdomName = " ";
	bool playerStatus;//true = player, false = AI

	std::vector <Provinces*> provincesList;
	std::unordered_map <std::string, CommanderProfile*> commandersList;

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
	CommanderProfile* selectedCommander; //For ArmyDeploymentMA
};
#endif
