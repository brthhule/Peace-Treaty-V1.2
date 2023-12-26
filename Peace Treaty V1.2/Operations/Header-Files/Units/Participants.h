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

//Includes INF.h, Commanders.h, PrimeUnits.h
#include PROVINCES_HEADER				//Composition

/*	#include ARMY_OVERVIEW_MA_HEADER		//Composition (Action)
		#include TRAIN_MA_HEADER
		#include INF_HEADER
	#include MAP_MA_HEADER					//Composition (Action)
		#include ATTACK_MA_HEADER
		#include INF_HEADER
		#include INPUT_HEADER
		#include SCOUT_MA_HEADER
		#include TRAIN_MA_HEADER
*/
#include PLAYER_ACTION_HEADER			//Interface

using namespace INF;
using namespace PROV;
using namespace UNIT;
using namespace ScoutMANamespace;

/*TODO
*Check if hasProvince/hasUnit needs to use a shared pointer as param
*		use const Province& address = *ptr
* Add functionality to initialCapRESS, depending on the difficulty, AI participants get more or less resources to start off with
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

	static void initializeParticipants(int totalPlayers, int humanPlayers, int count); 
	void createCapital();
	static partSPTR getCurrentParticipant();

	//----Getters----------------------------------------------------------
	///Get the costs needed to train a new Commander?
	constArrayReference getTrainCosts();

	i5array calculateEach(int option);
	///Returns all units in a participant, uses threading
	i5array getPrimeUnitsArray() const;//???
	/*Check out the return types of the bottom two funtions-
	Are they supposed to return anything? Currently call to global variables
	I deleted, can probably use a return type as a substitute*/
	void getPrimeUnitsArrayProvinces() const;
	void getPrimeUnitsArrayCommanders() const;


	///Returns a commander this Participant owns by name
	commSPTR getCommander(std::string name);
	///Return the unordered_map of Commander shared pointers
	std::unordered_map<std::string, commSPTR> getCommandersMap() const;

	///Got total number of Provinces in this participant
	int getProvincesNum() const;
	///Get total number of Commanders in this participant
	int getCommandersNum() const;
	///Return total number of Commanders + Provinces in this Participant
	int getPrimeUnitsAmount() const;
	///Get the index of this participant in the vector of all participants
	constINT getParticipantIndex() const;

	partSPTR getParticipant(int listIndex) const;

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

	commSPTR pickCommander() const;
	static const std::vector<Participants>& getParticipants();

	//----Threads----------------------------------------------------------
	///Experimental
	std::thread th1Method() const;
	std::thread th2Method() const;

	//----Checkers---------------------------------------------------------
	/** subtractCheckResources__ subtracts resources from a unit. If any resources go into the negative from subtractions, reverse the subtraction and return false. Otherwise, return true
	* 
	* @param unit__ the unit being modified
	* @param resources__ the array of resources being subtracted
	* @return bool__ true or false
	*/
	bool subtractCheckResources(unitSPTR unit, INF::i5array resourcesArray);

	///Check if this participant has a province by name/participant index/province
	const bool hasProvince(std::string name) const;
	const bool hasProvince(int pIndex) const;
	const bool hasProvince(provSPTR province) const;

	///Check if this participant has a particular commander
	const bool hasCommander(std::string name) const;
	///Check if this participant is alive
	
	bool isAlive() const;
	///Check if this participant is a bot or a player
	bool isPlayer() const;

	///Check if this participant has a particular unit, not optimal (string param)
	bool hasUnit(const std::string& unitName) const;
	//Kinda sketch, look at this??
	bool hasUnit(PrimeUnits& unit) const;

	int calculateTotals(int option);

		
	static void setHumanPlayers(int num);
	void setCapital(provSPTR newProvince); 
	void addProvince(provSPTR newProvince);
	void printListOfProvinces();

	void createAsPlayer(bool status);
	void viewAllStatsFunction();
	void viewStats();
	void scoutProvince(provSPTR targetProvince, int accuracy);
	/*Display this participant's list of commSPTR*/
	void displayCommanders() const;

	void setParticipantIndex(int num);
	void setKingdomName(std::string newName);
	void showMap();

	void nothingArmyOverview() override;

	/////////////////////////////////////ArmyOverviewMA.h//////////////////////
	//----Methods--------------------------------------------------------------
	void armyOverviewSelectAction() override;
	void armyOverviewSelectActionShowHelp() override;
	void trainCommanderPrompt() override;
	void proceedWithTraining(constArrayReference trainCosts) override;
	void upgradeCommander() override;
	sPTR<Commanders> pickCommanderToUpgrade() override;
	void viewCommanderStats() override;
	void deployCommanderPrompt() override;
	///Adds a Commander to the capital province
	void addCommander();

	///////////////////////////////////PlayerAction.h//////////////////////////
	char randomAction() override;
	void chooseAction() override;
	void pauseGame() override;
	void choosePauseGame() override;
	void playerActionShowHelp() override; 
	void buildAction() override;

	///////////////////////////////////TrainMA/////////////////////////////////
	void trainMAMain() override;
	void trainMALoop(int troopTier, int amountOfTroops) override;

	///////////////////////////////////Mobility.h//////////////////////////////
	void moveUnitOne(commSPTR commander) override;
	std::vector <provSPTR> getSurroundingProvinces(commSPTR commander) override;
	Provinces& pickProvinceToMoveTo(Commanders& commanderReference) override;
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
	void mainAttackMA( provSPTR defendProv, commSPTR attackComm) override;

	//----Getter Auxiliary Methods---------------------------------------------
	commSPTRList getCommandersCanAttack(provSPTR defendingProvince) override;
	commSPTR pickCommanderAttack(std::vector<commSPTR> commandersCanAttack) override;

	void playerCommitAttack(provSPTR defendingProvince, commSPTR attackingCommander) override;
	void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP) override;

	void calculateTroopsLost(commSPTR commander, int lostCombatPower, constArrayReference troopsLost, int troopIndex) override;
	void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex, commSPTR attackingCommander) override;
	void casualtyReport(i5array troopsLost, i5array injuredTroops) override;

private:
	static std::vector<Participants> participantsList;
	static i5array trainCosts;
	static int humanPlayers;

	i5array allCommandersArray;
	i5array allProvincesArray;

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

};

using partUPTR = std::unique_ptr<Participants>;
using partSPTR = std::shared_ptr<Participants>;
using partSPTRList = std::vector<partSPTR>;
}
#endif
