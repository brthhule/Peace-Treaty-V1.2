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

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"

#include ALL_UNITS_HEADER
#include ARMY_OVERVIEW_MA_HEADER
#include ATTACK_MA_HEADER
#include BASE_HEADER
#include COMMANDERS_HEADER
#include INF_HEADER
#include MOBILITY_HEADER
#include MAP_HEADER
#include MAP_MA_HEADER
#include PLAYER_ACTION_HEADER
#include PROVINCES_HEADER
#include SCOUT_MA_HEADER

//Players
class Participants :
	BASE_CLASS public BASE,
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
	
	CALCULATE GETTER
	i5array
		getTrainCosts(),
		calculateEach(int option),
		getAllUnitsArray();

	VARIABLE 
	static i5array
		allCommandersArray,
		allProvincesArray;

	std::thread th1Method();
	std::thread th2Method();

	GETTER std::unordered_map<std::string, Commanders*> getCommandersMap();

	BOOL
		subtractCheckResources(String provinceName, INF::i5array resourcesArray);

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

	GETTER 
	Commanders
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

	std::shared_ptr<Commanders> pickCommander();

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

ARMY_OVERVIEW_MA START
	void printCosts(std::vector<int>costs, std::string type);
	void armyDeploymentMF();
	void trainCommanders();
	void proceedWithTraining(i5array trainCosts);
	void upgradeCommander();
	void upgradeCommander();
	void viewArmyOverview();
	void deployCommanderMF();
	ARMY_OVERVIEW_MA END

PLAYER_ACTION START
	char randomAction();
	void initialDecision();
	void pauseGame();
	PLAYER_ACTION END

TRAIN_MA START
	//TrainMA.h
	void TrainMAFunction();
	void TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops);

	void moveUnitOne(Commanders* commander);
	std::vector <Provinces*> moveUnitTwo(Commanders* commander);
	static std::pair<int, int> pickCoords();
	TRAIN_MA END

MAP_MA START
	void viewPlayerMap();
	void selectUnitOriginal(Provinces* selectedProvince);
	void selectPlayerProvince(Provinces* province);

	void playerUnitAction(Provinces* province);
	void playerUnitActionP(Provinces* province);
	void selectEnemyAction();
	void selectEnemyProvince(Provinces* province);
	MAP_MA END
	
SCOUT_MA START
	void mainScoutMA (Provinces* provinceArg);

	std::pair<AllUnits*, int> playerScoutStepTwo(scoutTypes canScout, Provinces* targetProvince);
	void scoutLogCalculationsProvince(int accuracy);
	void getCanScoutTwo(
			int targetX, 
			int targetY, 
			int a, 
			int b, 
			scoutTypes& canScout);

	AllUnits* selectUnitToScout(scoutTypes canScout);
	AllUnits* selectUnitToScoutTwo(scoutTypes canScout);

	scoutTypes selectTarget(Provinces* targetProvince);
	scoutTypes getCanScout(Provinces* targetProvince);
	SCOUT_MA END

ATTACK_MA START
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

	GETTER
	std::vector<Commanders*> getCommandersCanAttack(std::pair<int, int> defenderSYstemCoords);
	Commanders* pickCommanderAttack(std::vector<Commanders*>);
	void playerCommitAttack(Provinces* defendingProvince, Commanders* attackingCommander);
	Commanders* pickCommanderAttack(std::vector<Commanders*> commandersCanAttack);

	GETTER
	void printResourcesGained();
	void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP);

	CALCULATE
	void calculateTroopsLost(Commanders* commander, int lostCombatPower, i5array& troopsLost, int troopIndex);
	void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex);
	void casualtyReport(i5array troopsLost, i5array injuredTroops);
	ATTACK_MA END

private:
	static i5array trainCosts;

	COMM::commSPTR selectedCommander; //For ArmyDeploymentMA

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
