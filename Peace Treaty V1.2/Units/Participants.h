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


#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\AllUnits.h"
#include "C:\Users\Brennen\source\repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Commanders.h"
#include "Map.h"
#include "Provinces.h"

#include "Misc/INF.h"
#include "CommandersAttributes/Mobility.h"

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\MA\AttackMA.h"
#include "../MA/ArmyOverviewMA.h"
#include "../MA/MapMA.h"
#include "../PlayerAction.h"
#include "../MA/ScoutMA.h"


#define CONSTRUCTOR
#define VARIABLE
#define SETTER
#define GETTER
#define CHECK
#define CALCULATE

//Interface stuff
#define INTERFACE
#define TRAIN_MA
#define PLAYER_ACTION
#define MAP_MA
#define SCOUT_MA

#define BASE_CLASS
#define MAP
#define MOBILITY

Provinces* newProv;
using namespace INF;


class Participants :
	BASE_CLASS public Map,
	BASE_CLASS public Mobility,
	INTERFACE public ArmyOverviewMA,
	INTERFACE public TrainMA,
	INTERFACE public PlayerAction,
	INTERFACE public MapMA,
	INTERFACE public ScoutMA,
	INTERFACE public AttackMA
{
public:
	static std::vector<Participants*> participantsList;
	CONSTRUCTOR Participants();
	CONSTRUCTOR Participants(int pIndex);
	
	VARIABLE i5array
		getTrainCosts(),
		calculateEach(int option),
		getAllUnitsArray();

	VARIABLE static i5array
		allCommandersArray,
		allProvincesArray;

	std::thread th1Method();
	std::thread th2Method();

	GETTER std::unordered_map<std::string, Commanders*> getCommandersMap();

	BOOL
		subtractCheckResources(String provinceName, i5array resourcesArray);

	CHECK BOOL
		hasProvince(std::string name),
		//Overloading
		hasProvince(int pIndex),
		hasProvince(Provinces* province),
		hasCommander(std::string name),
		isAlive(),
		isPlayer(),
		hasUnit(std::string unitName),
		hasUnit(AllUnits unit);

	GETTER Commanders
		* getCommander(std::string name),
		* getSelectedCommander();

	ivector calculatePlayerValues(int decision);

	INTEGER calculateTotals(int option);

	GETTER INTEGER
		getRandomCoordinate(),
		getProvincesNum(),
		getCommandersNum(),
		getAllUnitsAmount(),//Create funciton
		getParticipantIndex();

	//Coordinate stuff
	Provinces
		* pickYourProvince(int identifier),
		* pickProvince(int identifer),

		* getProvince(std::string name),
		* getProvince(int index),

		* getCapitalProvince(),
		* getSystemProvince(std::pair<int, int> systemCoords);
		

	STRING
		getKingdomName(),
		getNewName();

	Commanders *pickCommander();

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
		proceedWithTraining(i5array trainCosts),
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

	void moveUnitOne(Commanders* commander);
	std::vector <Provinces*> moveUnitTwo(Commanders* commander);
	static std::pair<int, int> pickCoords();


	//MapMA.h
	void
		viewPlayerMap(),
		selectUnitOriginal(Provinces* selectedProvince),
		selectPlayerProvince(Provinces* province),

		playerUnitAction(Provinces* province),
		playerUnitActionP(Provinces* province),
		selectEnemyAction(),
		selectEnemyProvince(Provinces* province);

	//ScoutMA.h
	void mainScoutMA (Participants* newParticipant, Provinces* newProvince);

	class ScoutInfo {
	public:
		ScoutInfo(Provinces *provinceArg);
		Participants* participant, * targetParticipant;
		Provinces* yourProvince, * targetProvince;
		enum TargetTypes { PROVINCE, COMMANDER };
	};
	ScoutInfo scoutInfo;

	void
		playerScoutStepTwo(scoutTypes canScout),
		scoutLogCalculationsProvince(int accuracy),
		getCanScoutTwo(
			int targetX, 
			int targetY, 
			int a, 
			int b, 
			scoutTypes& canScout);

	AllUnits
		* selectUnitToScout(scoutTypes canScout),
		* selectUnitToScoutTwo(scoutTypes canScout);
	scoutTypes
		selectTarget(), 
		getCanScout();

	/////////AttackMA.h///////////////////
	class AttackMAInfo {
		AttackMAInfo(
			Provinces* defendingProvinceArg,
			Participants* attackingParticipantArg);
		AttackMAInfo(
			Provinces* attackerProvinceArg, 
			Provinces* defenderProvinceArg, 
			Participants* attackingParticipantArg, 
			Commanders* commanderArg);

		Provinces* defendingProvince;
		Participants* attackingParticipant;
		Provinces* attackerProvinceArg;
		Participants* defenderParticipant;
		Commanders* commander;
	};
	void mainAttackMA(
		Provinces* defendingProvince,
		Commanders* attackingCommander);
	std::vector<Commanders*> getCommandersCanAttack(std::pair<int, int> defenderSYstemCoords);
	Commanders* pickCommanderAttack(std::vector<Commanders*>);
	void playerCommitAttack(Provinces* defendingProvince, Commanders* attackingCommander);
	//////////End AttackMA.h//////////////

private:
	using CommandersPtrMap = std::unordered_map<std::string, Commanders*>;

	i5array
		trainCosts = { 5, 4, 3, 2, 1 },
		troopsLost = { 0,0,0,0,0 };

	BOOL playerStatus;//true = player, false = AI

	Commanders* selectedCommander; //For ArmyDeploymentMA

	INTEGER
		capitalIndex,
		participantIndex;

	Provinces* capitalProvince;

	STRING kingdomName = " ";

	std::unordered_map <std::string, Commanders*> commandersMap;
	std::unordered_map <std::string, Provinces*> provincesMap;
	std::unordered_map<std::string, Commanders*>::iterator commIt;

	std::vector <Provinces*> provincesVector;
	std::vector <Commanders> commandersVector;
	

	

	
};
#endif
