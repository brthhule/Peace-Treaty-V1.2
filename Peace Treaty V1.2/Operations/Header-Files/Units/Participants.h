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

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

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
	EXTENDS_
		BASE_CLASS public BASE,
		BASE_CLASS public Map,
		BASE_CLASS public Mobility,
	IMPLEMENTS_
		INTERFACE public ArmyOverviewMA,
		INTERFACE public TrainMA,
		INTERFACE public PlayerAction,
		INTERFACE public MapMA,
		INTERFACE public ScoutMA,
		INTERFACE public AttackMA
	COMPRISES_
		ALL_UNITS_
		COMMANDERS_
		PROVINCES_
	USES_
		INF_
{
public:
	using partSPTR = std::shared_ptr<Participants>;
	static std::vector<partSPTR> playersList;
	static std::vector<partSPTR> botsList;
	using commSPTR = Commanders::commSPTR;
	using provSPTR = Provinces::provSPTR;

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

	GETTER std::unordered_map<std::string, commSPTR> getCommandersMap();

	BOOL
		subtractCheckResources(String provinceName, INF::i5array resourcesArray);

	CHECK BOOL
		hasProvince(std::string name),
		//Overloading
		hasProvince(int pIndex),
		hasProvince(provSPTR province),
		hasCommander(std::string name),
		isAlive(),
		isPlayer(),
		hasUnit(std::string unitName),
		hasUnit(AllUnits unit);

	GETTER 
	commSPTR
		getCommander(std::string name),
		getSelectedCommander();

	ivector calculatePlayerValues(int decision);

	INTEGER calculateTotals(int option);

	GETTER INTEGER
		getRandomCoordinate(),
		getProvincesNum(),
		getCommandersNum(),
		getAllUnitsAmount(),//Create funciton
		getParticipantIndex();

	//Coordinate stuff
	provSPTR
		pickYourProvince(int identifier),
		pickProvince(int identifer),

		getProvince(std::string name),
		getProvince(int index),

		getCapitalProvince(),
		getSystemProvince(ipair systemCoords);
		

	STRING
		getKingdomName(),
		getNewName();

	commSPTR pickCommander();

	VOID setCapital(provSPTR newProvince);
	VOID showMapOld();

	VOID addCommander();
	VOID addProvince(provSPTR newProvince);
	VOID printListOfProvinces();

	VOID createAsPlayer(bool status);
	VOID viewAllStatsFunction();
	VOID viewStats();
	VOID scoutProvince(provSPTR targetProvince, int accuracy);
	VOID displayCommanders();
	VOID initialCapRSS();

	VOID setParticipantIndex(int num);
	VOID setKingdomName(std::string newName);
	VOID showMap();

	VOID getAllUnitsArrayCommanders();
	VOID getAllUnitsArrayProvinces();

	VOID updateTurnResourcesParticipant();
	VOID createMapParticipant();
		
	const provSPTR tempProvince = new Provinces;

ARMY_OVERVIEW_MA_ START
	void printCosts(std::vector<int>costs, std::string type);
	/** armyDeploymentMF
		Compare two Types

		@param l Type lhs
		@param r Type rhs
		@return boolean result
	*/


	//void armyDeploymentMF();
	void trainCommanders();
	void proceedWithTraining(i5array trainCosts);
	void upgradeCommander();
	void upgradeCommander();
	void viewArmyOverview();
	void deployCommanderMF();
	ARMY_OVERVIEW_MA_ END

PLAYER_ACTION START
	char randomAction(); 
	void initialDecision();
	void pauseGame();
	PLAYER_ACTION END

TRAIN_MA_ START
	//TrainMA.h
	void TrainMAFunction();
	void TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops);

	void moveUnitOne(commSPTR commander);
	std::vector <provSPTR> moveUnitTwo(commSPTR commander);
	static ipair pickCoords();
	TRAIN_MA_ END

MAP_MA_ START
	void viewPlayerMap();
	void selectUnitOriginal(provSPTR selectedProvince);
	void selectPlayerProvince(provSPTR province);

	void playerUnitAction(provSPTR province);
	void playerUnitActionP(provSPTR province);
	void selectEnemyAction();
	void selectEnemyProvince(provSPTR province);
	MAP_MA_ END
	
SCOUT_MA START
	void mainScoutMA (provSPTR provinceArg); 

	std::pair<unitSPTR, int> playerScoutStepTwo(scoutTypes canScout, provSPTR targetProvince);
	void scoutLogCalculationsProvince(int accuracy);
	void getCanScoutTwo(
			int targetX, 
			int targetY, 
			int a, 
			int b, 
			scoutTypes& canScout);

	unitSPTR selectUnitToScout(scoutTypes canScout);
	unitSPTR selectUnitToScoutTwo(scoutTypes canScout);

	scoutTypes selectTarget(provSPTR targetProvince);
	scoutTypes getCanScout(provSPTR targetProvince);
	SCOUT_MA END

ATTACK_MA START
	class AttackMAInfo {
		AttackMAInfo();
		AttackMAInfo(provSPTR defendingProvinceArg);
		AttackMAInfo(provSPTR defenderProvinceArg, commSPTR commanderArg);

		provSPTR defendingProvince;
		//partSPTR attackingParticipant; is this object
		commSPTR commander;
		bool defenseCanRetreat;
	};
	void mainAttackMA(
		provSPTR defendingProvince,
		commSPTR attackingCommander);

	GETTER
	std::vector<commSPTR> getCommandersCanAttack(provSPTR defendingProvince);
	commSPTR pickCommanderAttack(std::vector<commSPTR>);
	void playerCommitAttack(provSPTR defendingProvince, commSPTR attackingCommander);
	commSPTR pickCommanderAttack(std::vector<commSPTR> commandersCanAttack);

	GETTER
	void printResourcesGained();
	void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP);

	CALCULATE
	void calculateTroopsLost(commSPTR commander, int lostCombatPower, i5array& troopsLost, int troopIndex);
	void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex);
	void casualtyReport(i5array troopsLost, i5array injuredTroops);
	ATTACK_MA END

private:
	static i5array trainCosts;

	COMM::commSPTR selectedCommander; //For ArmyDeploymentMA

	INTEGER
		capitalIndex,
		participantIndex;

	provSPTR capitalProvince;

	STRING kingdomName = " ";

	std::unordered_map <std::string, commSPTR> commandersMap;
	std::unordered_map <std::string, provSPTR> provincesMap;
	std::unordered_map<std::string, commSPTR>::iterator commIt;

	std::vector <provSPTR> provincesVector;
	std::vector <commSPTR> commandersVector;
	

	

	
};
#endif
