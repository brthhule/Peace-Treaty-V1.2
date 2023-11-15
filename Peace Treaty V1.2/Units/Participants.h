//Participants.h

//Interfaces/Inheritance: Map, Mobility, ArmyOverviewMA, TrainMA, PlayerAction
//Composition: Provinces, Commanders

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
#include "Commanders.h"
#include "Map.h"
#include "Provinces.h"

#include "Misc/INF.h"
#include "Misc/LinkedList.h"
#include "Misc/INF.h"
#include "CommandersAttributes/Mobility.h"
#include "../MA/ArmyOverviewMA.h"


#define CONSTRUCTOR


using namespace INF;


class Participants : public Map, public Mobility, public ArmyOverviewMA, public TrainMA, public PlayerAction
{
public:
	CONSTRUCTOR Participants();
	CONSTRUCTOR Participants(int pIndex);
	
	i5array
		getTrainCosts(),
		calculateEach(int option),
		getAllUnitsArray();

	static i5array
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

	ivector calculatePlayerValues(int decision);

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

	//ArmyOverviewMA.h
	void
		printCosts(std::vector<int>costs, std::string type),
		armyDeploymentMF(),
		trainCommanders(),
		proceedWithTraining(std::array <int, 5> trainCosts),
		upgradeCommandersOne(),
		upgradeCommandersTwo(),
		viewArmyOverview(),
		deployCommanderMF();

	//PlayerAction.h
	
	char randomAction();
	void 
		initialDecision(),
		pauseGame();

	//TrainMA.h
	void TrainMAFunction();
	void TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops);

	void moveUnitOne(CommanderProfile* commander);
	std::vector <Provinces*> moveUnitTwo(CommanderProfile* commander);
	static std::pair<int, int> pickCoords();


private:
	i5array
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
