//Participants.h

//Interfaces/Inheritance: Map, Mobility, ArmyOverviewMA, TrainMA, PlayerAction
//Composition: Provinces, Commanders

#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include "stdafx.h"

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

//Players
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
	static std::vector<Participants*> playersList;
	static std::vector<Participants*> botsList;
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

	VOID setCapital(Provinces* newProvince);
	VOID showMapOld();

	VOID addCommander();
	VOID addProvince(Provinces* newProvince);
	VOID printListOfProvinces();

	VOID createAsPlayer(bool status);
	VOID viewAllStatsFunction();
	VOID viewStats();
	VOID scoutProvince(Provinces* targetProvince, int accuracy);
	VOID displayCommanders();
	VOID initialCapRSS();

	VOID setParticipantIndex(int num);
	VOID setKingdomName(std::string newName);
	VOID showMap();

	VOID getAllUnitsArrayCommanders();
	VOID getAllUnitsArrayProvinces();

	VOID updateTurnResourcesParticipant();
	VOID createMapParticipant();
		
	const Provinces* tempProvince = new Provinces;

	//ArmyOverviewMA.h
	void printCosts(std::vector<int>costs, std::string type);
	void armyDeploymentMF();
	void trainCommanders();
	void proceedWithTraining(i5array trainCosts);
	void upgradeCommandersOne();
	void upgradeCommandersTwo();
	void viewArmyOverview();
	void deployCommanderMF();

	//PlayerAction.h
	
	char randomAction();
	void initialDecision();
	void pauseGame();

	//TrainMA.h
	void TrainMAFunction();
	void TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops);

	void moveUnitOne(Commanders* commander);
	std::vector <Provinces*> moveUnitTwo(Commanders* commander);
	static std::pair<int, int> pickCoords();


	//MapMA.h
	void viewPlayerMap();
	void selectUnitOriginal(Provinces* selectedProvince);
	void selectPlayerProvince(Provinces* province);

	void playerUnitAction(Provinces* province);
	void playerUnitActionP(Provinces* province);
	void selectEnemyAction();
	void selectEnemyProvince(Provinces* province);

	//ScoutMA.h
	void mainScoutMA (Provinces* provinceArg);

	std::pair<AllUnits, int> playerScoutStepTwo(scoutTypes canScout, Provinces* targetProvince);
	void scoutLogCalculationsProvince(int accuracy);
	void getCanScoutTwo(
			int targetX, 
			int targetY, 
			int a, 
			int b, 
			scoutTypes& canScout);

	AllUnits* selectUnitToScout(scoutTypes canScout);
	AllUnits* *selectUnitToScoutTwo(scoutTypes canScout);

	scoutTypes selectTarget(Provinces* targetProvince);
	scoutTypes getCanScout();

	/////////AttackMA.h///////////////////
	class AttackMAInfo {
		AttackMAInfo();
		AttackMAInfo(Provinces* defendingProvinceArg);
		AttackMAInfo(Provinces* defenderProvinceArg, Commanders* commanderArg);

		Provinces* defendingProvince;
		//Participants* attackingParticipant; is this object
		Commanders* commander;
		bool defenseCanRetreat;
	};
	void mainAttackMA(
		Provinces* defendingProvince,
		Commanders* attackingCommander);

	std::vector<Commanders*> getCommandersCanAttack(std::pair<int, int> defenderSYstemCoords);
	Commanders* pickCommanderAttack(std::vector<Commanders*>);
	void playerCommitAttack(Provinces* defendingProvince, Commanders* attackingCommander);


	Commanders* pickCommanderAttack(std::vector<Commanders*> commandersCanAttack);


	void printResourcesGained();
	void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP);

	void calculateTroopsLost(Commanders* commander, int lostCombatPower, i5array& troopsLost, int troopIndex);
	void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex);
	void casualtyReport(i5array troopsLost, i5array injuredTroops);

	//////////End AttackMA.h//////////////

private:
	using CommandersPtrMap = std::unordered_map<std::string, Commanders*>;

	static i5array trainCosts;

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
