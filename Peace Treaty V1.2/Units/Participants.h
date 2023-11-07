#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <stdlib.h> 

#include <time.h>
#include <thread>
#include <unordered_map>
#include <vector>


#include "AllUnits.h"
#include "CommanderProfile.h"
#include "Map.h"
#include "Provinces.h"

#include "../Misc/CV.h"
#include "../Misc/LinkedList.h"
#include "../Misc/OF.h"
#include "../Mobility.h"


#define CONSTRUCTOR


using namespace CV;
using namespace OF;

class Participants : Map, Mobility
{
public:
	CONSTRUCTOR Participants();
	CONSTRUCTOR Participants(int pIndex);
	
	ARRAY
		getTrainCosts(),
		calculateEach(int option),
		getAllUnitsArray();

	static ARRAY
		allCommandersArray,
		allProvincesArray;

	std::thread th1Method();
	std::thread th2Method();

	std::unordered_map<std::string, CommanderProfile*> getCommandersMap() { return commandersMap; }

	BOOL 
		subtractCheckResources(std::string provinceName, std::array<int, 5> resourcesArray),
		hasProvince(std::string name),
		hasCommander(std::string name),
		isAlive(),
		isPlayer(),
		hasUnit(std::string unitName);

	CommanderProfile
		* getCommander(std::string name),
		* getSelectedCommander();

	INT_VECTOR calculatePlayerValues(int decision);

	INTEGER
		calculateTotals(int option),
		getRandomCoordinate(),
		provincesNum(),
		commandersNum(),
		getAllUnitsAmount(),//Create funciton
		getParticipantIndex();

	//Coordinate stuff
	Provinces
		* getYourProvince(int identifier),
		* findProvince(),
		* getProvinceByName(std::string name),
		* findProvince(std::pair<int, int> userCoords),
		* getProvince(int index),
		* getCapitalProvince(),
		* getSystemProvince(std::pair<int, int> systemCoords),
		* getCoords(int identifer);

	STRING
		getKingdomName(),
		selectCommander(),
		getNewName();

	VOID
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
		showMap(),

		getAllUnitsArrayCommanders(),
		getAllUnitsArrayProvinces(),

		updateTurnResourcesParticipant(),
		createMapParticipant();
		
	const Provinces* tempProvince = new Provinces;

	void
		printCosts(std::vector<int>costs, std::string type) = 0,
		armyDeploymentMF() = 0,
		trainCommanders() = 0,
		proceedWithTraining(std::array <int, 5> trainCosts) = 0,
		upgradeCommandersOne() = 0,
		upgradeCommandersTwo() = 0,
		viewArmyOverview() = 0,
		deployCommanderMF() = 0;


	void moveUnitOne(CommanderProfile* commander);
	std::vector <Provinces*> moveUnitTwo(CommanderProfile* commander);
	static std::pair<int, int> pickCoords();


private:
	ARRAY
		trainCosts = { 5, 4, 3, 2, 1 },
		troopsLost = { 0,0,0,0,0 };

	BOOL playerStatus;//true = player, false = AI

	CommanderProfile* selectedCommander; //For ArmyDeploymentMA

	INTEGER
		capitalIndex,
		participantIndex;

	Provinces* capitalProvince;

	STRING kingdomName = " ";

	std::unordered_map <std::string, CommanderProfile*> commandersMap;
	std::unordered_map <std::string, Provinces*> provincesMap;
	std::unordered_map<std::string, CommanderProfile*>::iterator it;

	std::vector <Provinces*> provincesVector;
	std::vector <CommanderProfile> commandersVector;
	

	

	
};
#endif
