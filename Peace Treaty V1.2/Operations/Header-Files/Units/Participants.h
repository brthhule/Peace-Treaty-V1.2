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

#include BASE_HEADER					//Base Class
#include MOBILITY_HEADER				//Base Class
#include MAP_HEADER						//Base Class

#include PRIME_UNITS_HEADER				//Composition
#include COMMANDERS_HEADER				//Composition
#include PROVINCES_HEADER				//Composition

#include INF_HEADER						//Utility

#include ARMY_OVERVIEW_MA_HEADER		//Interface
#include ATTACK_MA_HEADER				//Interface
#include MAP_MA_HEADER					//Interface
#include PLAYER_ACTION_HEADER			//Interface
#include SCOUT_MA_HEADER				//Interface
#include TRAIN_MA_HEADER				//Interface
#include TROOPS_INT_HEADER				//Interface

using namespace INF;
using namespace PROV;
using namespace UNIT;

/*TODO
* Check if hasProvince/hasUnit needs to use a shared pointer as param
*	use const Province& address = *ptr
*/
namespace PART {
//Represent players, both human and AI
class Participants : 
		public BASE, 
		public Map,
		public Mobility,
		public ArmyOverviewMA,
		public TrainMA,
		public PlayerAction,
		public MapMA,
		public ScoutMA,
		public AttackMA
{
public:
	//----Aliases----------------------------------------------------------
	using partSPTR = std::shared_ptr<Participants>;
	using partSPTRList = std::vector<partSPTR>;
	static partSPTRList playersList;
	static partSPTRList botsList;
		
	//----Constructors-----------------------------------------------------
	Participants();
	Participants(int pIndex);
	~Participants(){}

	//----Getters----------------------------------------------------------
	///Get the costs needed to train a new Commander?
	constI5array getTrainCosts(); 
	i5array calculateEach(int option);
	///Returns all units in a participant, uses threading
	i5array getAllUnitsArray();//???
	/*Check out the return types of the bottom two funtions-
	Are they supposed to return anything? Currently call to global variables
	I deleted, can probably use a return type as a substitute*/
	void Participants::getAllUnitsArrayProvinces();
	void getAllUnitsArrayCommanders();


	///Returns a commander this Participant owns by name
	commSPTR getCommander(std::string name);
	///Return the unordered_map of Commander shared pointers
	std::unordered_map<std::string, commSPTR> getCommandersMap();

	///Got total number of Provinces in this participant
	int getProvincesNum();
	///Get total number of Commanders in this participant
	int getCommandersNum();
	///Return total number of Commanders + Provinces in this Participant
	int getAllUnitsAmount();
	///Get the index of this participant in the vector of all participants
	int getParticipantIndex();

	///Returns participant statistics?
	ivector calculatePlayerValues(int decision);

	//Coordinate stuff
	provSPTR
		pickYourProvince(int identifier),
		pickProvince(int identifer),

		getProvince(std::string name),
		getProvince(int index),

		getCapitalProvince(),
		getSystemProvince(ipair systemCoords);

	std::string
		getKingdomName(),
		getNewName();

	commSPTR pickCommander();

	//----Threads----------------------------------------------------------
	///Experimental
	std::thread th1Method();
	std::thread th2Method();

	//----Checkers---------------------------------------------------------
	/** subtractCheckResources__ subtracts resources from a unit. If any resources go into the negative from subtractions, reverse the subtraction and return false. Otherwise, return true
	* 
	* @param unit__ the unit being modified
	* @param resources__ the array of resources being subtracted
	* @return bool__ true or false
	*/
	bool subtractCheckResources(unitSPTR unit, INF::i5array resourcesArray);

	///Check if this participant has a province by name/participant index/province
	bool hasProvince(std::string name);
	bool hasProvince(int pIndex);
	bool hasProvince(provSPTR province);

	///Check if this participant has a particular commander
	bool hasCommander(std::string name);
	///Check if this participant is alive
	bool isAlive();
	///Check if this participant is a bot or a player
	bool isPlayer();

	///Check if this participant has a particular unit, not optimal (string param)
	bool hasUnit(const std::string& unitName);
	//Kinda sketch, look at this??
	bool hasUnit(const PrimeUnits& unit);

	int calculateTotals(int option);

		

	void setCapital(provSPTR newProvince);
	void addCommander();
	void addProvince(provSPTR newProvince);
	void printListOfProvinces();

	void createAsPlayer(bool status);
	void viewAllStatsFunction();
	void viewStats();
	void scoutProvince(provSPTR targetProvince, int accuracy);
	void displayCommanders();
	void initialCapRSS();

	void setParticipantIndex(int num);
	void setKingdomName(std::string newName);
	void showMap();

	void updateTurnResourcesParticipant();
	void createMapParticipant();

	/////////////////////////////////////ArmyOverviewMA.h//////////////////////
	//-----Printers------------------------------------------------------------
	void printCosts(constI5array, int phrase) override;

	//----Methods--------------------------------------------------------------
	void armyOverviewMain() override;
	void trainCommanders() override;
	void proceedWithTraining(i5array trainCosts) override;
	void upgradeCommander() override;
	void viewArmyOverview() override;
	void deployCommanderMF() override;

	///////////////////////////////////PlayerAction.h//////////////////////////
	char randomAction() override;
	void chooseAction() override;
	void pauseGame() override;
	void choosePauseGame() override;
	void showHelp() override;
	void buildAction() override;

	///////////////////////////////////TrainMA/////////////////////////////////
	void trainMAMain() override;
	void trainMALoop(int troopTier, int amountOfTroops) override;

	///////////////////////////////////Mobility.h//////////////////////////////
	void moveUnitOne(commSPTR commander) override;
	std::vector <provSPTR> moveUnitTwo(commSPTR commander) override;
	static ipair pickCoords();

	///////////////////////////////////MapMA.h/////////////////////////////////
	void viewPlayerMap();
	void selectUnitOriginal(provSPTR selectedProvince);
	void selectPlayerProvince(provSPTR province);

	void playerUnitAction(provSPTR province);
	void playerUnitActionP(provSPTR province);
	void selectEnemyAction();
	void selectEnemyProvince(provSPTR province);
	

	///////////////////////////////////ScoutMA.h///////////////////////////////
	void mainScoutMA(provSPTR provinceArg);
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
	
	///////////////////////////////////AttackMA.h//////////////////////////////
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


	//----Getter Auxiliary Methods---------------------------------------------
	std::vector<commSPTR> getCommandersCanAttack(provSPTR defendingProvince);
	commSPTR pickCommanderAttack(std::vector<commSPTR> commandersCanAttack);

	
	void playerCommitAttack(provSPTR defendingProvince, commSPTR attackingCommander);
	void printResourcesGained();
	void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP);

	void calculateTroopsLost(commSPTR commander, int lostCombatPower, i5array& troopsLost, int troopIndex);
	void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex);
	void casualtyReport(i5array troopsLost, i5array injuredTroops);

private:
	static i5array trainCosts;

	commSPTR selectedCommander; //For ArmyDeploymentMA

	int
		capitalIndex,
		participantIndex;

	provSPTR capitalProvince;

	std::string kingdomName = " "; 

	std::unordered_map <std::string, commSPTR> commandersMap;
	std::unordered_map <std::string, provSPTR> provincesMap;
	std::unordered_map<std::string, commSPTR>::iterator commIt;

	std::vector <provSPTR> provincesVector;
	std::vector <commSPTR> commandersVector;

	static std::unordered_map<char, int> actionsMap;
};

using partUPTR = std::unique_ptr<Participants>;
using partSPTR = std::shared_ptr<Participants>;
using partSPTRList = std::vector<partSPTR>;
}
#endif
