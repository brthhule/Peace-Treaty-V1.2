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
#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include BASE_HEADER					//Base Class
#include MOBILITY_HEADER				//Base Class
#include MAP_HEADER						//Base Class

#include PROVINCES_HEADER				//Composition
#include COMMANDERS_HEADER
#include PRIME_UNITS_HEADER

#include ARMY_OVERVIEW_MA_HEADER		//Composition (Action)
#include TRAIN_MA_HEADER
#include INF_HEADER
#include MAP_MA_HEADER					//Composition (Action)
#include ATTACK_MA_HEADER
#include INPUT_HEADER
#include SCOUT_MA_HEADER

#include PLAYER_ACTION_HEADER			//Interface

/*TODO
*Check if hasProvince/hasUnit needs to use a shared pointer as param
*		use const Province& address = *ptr
* Add functionality to initialCapRESS, depending on the difficulty, AI participants get more or less resources to start off with
*/
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
	~Participants();

	static void initializeParticipants(int totalPlayers, int humanPlayers, int count); 
	void createCapital();
	static partSPTR getCurrentParticipant();

	//----Getters----------------------------------------------------------
	///Get the costs needed to train a new Commander?
	INF::constArrayRef getTrainCosts();

	INF::i5array calculateEach(int option);
	///Returns all units in a participant, uses threading
	INF::i5array getPrimeUnitsArray() const;//???
	/*Check out the return types of the bottom two funtions-
	Are they supposed to return anything? Currently call to global variables
	I deleted, can probably use a return type as a substitute*/
	void getPrimeUnitsArrayProvinces() const;

	//Need to implement this
	void getPrimeUnitsArrayCommanders() const;


	///Returns a commander this Participant owns by name
	COMM::commSPTR getCommander(std::string name);
	///Return the unordered_map of Commander shared pointers
	std::unordered_map<std::string, COMM::commSPTR> getCommandersMap() const;

	///Got total number of Provinces in this participant
	int getProvincesNum() const;
	///Get total number of Commanders in this participant
	int getCommandersNum() const;
	///Return total number of Commanders + Provinces in this Participant
	int getPrimeUnitsAmount() const;
	///Get the index of this participant in the vector of all participants
	INF::constINT getParticipantIndex() const;

	partSPTR getParticipant(int listIndex) const;

	///Returns participant statistics?
	INF::ivector calculatePlayerValues(int decision);

	//Coordinate stuff
	PROV::provSPTR
		pickYourProvince(int identifier),
		pickProvince(int identifer),

		getProvince(std::string name),
		getProvince(int index),

		getCapitalProvince(),
		getSystemProvince(INF::ipair systemCoords);

	std::string
		getKingdomName(),
		getNewName();

	COMM::commSPTR pickCommander() const;
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
	bool subtractCheckResources(UNIT::unitSPTR unit, INF::i5array resourcesArray);

	///Check if this participant has a province by name/participant index/province
	const bool hasProvince(std::string name) const;
	const bool hasProvince(int pIndex) const;
	const bool hasProvince(PROV::provSPTR province) const;

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
	void setCapital(PROV::provSPTR newProvince); 
	void addProvince(PROV::provSPTR newProvince);
	void printListOfProvinces();

	void createAsPlayer(bool status);
	void viewAllStatsFunction();
	void viewStats();
	void scoutProvince(PROV::provSPTR targetProvince, int accuracy);
	/*Display this participant's list of commSPTR*/
	void displayCommanders() const;

	void setParticipantIndex(int num);
	void setKingdomName(std::string newName);

	/////////////////////////////////////ArmyOverviewMA.h//////////////////////
	//----Methods--------------------------------------------------------------
	void armyOverviewSelectAction() override;
	void armyOverviewSelectActionShowHelp() override;
	void trainCommanderPrompt() override;
	void proceedWithTraining(INF::constArrayRef trainCosts) override;
	void upgradeCommander() override;
	COMM::commSPTR pickCommanderToUpgrade() override;
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
	void moveUnitOne(COMM::commSPTR commander) override;
	std::vector <PROV::provSPTR> getSurroundingProvinces(Commanders& commander_ref) override;
	Provinces& pickProvinceToMoveTo(Commanders& commanderReference) override;
	///////////////////////////////////MapMA.h/////////////////////////////////
	void viewPlayerMap();
	void selectUnitOriginal(PROV::provSPTR selectedProvince);
	void selectPlayerProvince(PROV::provSPTR province);

	void playerUnitAction(PROV::provSPTR province);
	void playerUnitActionP(PROV::provSPTR province);
	void selectEnemyAction();
	void selectEnemyProvince(PROV::provSPTR province);
	

	///////////////////////////////////ScoutMA.h///////////////////////////////
	void mainScoutMA(PROV::provSPTR provinceArg);
	std::pair<UNIT::unitSPTR, int> playerScoutStepTwo(PROV::scoutTypes canScout, PROV::provSPTR targetProvince);
	void scoutLogCalculationsProvince(int accuracy);
	void getCanScoutTwo(
		int targetX,
		int targetY,
		int a,
		int b,
		PROV::scoutTypes& canScout);

	UNIT::unitSPTR selectUnitToScout(PROV::scoutTypes canScout);
	UNIT::unitSPTR selectUnitToScoutTwo(PROV::scoutTypes canScout);

	PROV::scoutTypes selectTarget(PROV::provSPTR targetProvince);
	PROV::scoutTypes getCanScout(PROV::provSPTR targetProvince);
	
	///////////////////////////////////AttackMA.h//////////////////////////////
	void mainAttackMA( PROV::provSPTR defendProv, COMM::commSPTR attackComm) override;

	//----Getter Auxiliary Methods---------------------------------------------
	COMM::commSPTRList getCommandersCanAttack(PROV::provSPTR defendingProvince) override;
	COMM::commSPTR pickCommanderAttack(COMM::commSPTRList commandersCanAttack) override;

	void playerCommitAttack(PROV::provSPTR defendingProvince, COMM::commSPTR attackingCommander) override;
	INF::ipair determineLostCP(int attackerCP, int defendingCP) override;

	void calculateTroopsLost(COMM::commSPTR commander, int lostCombatPower, INF::constArrayRef troopsLost, int troopIndex) override;
	void battleCalculationsTwo(INF::constINT lostCombatPower, INF::i5array troopsLost, int troopIndex, COMM::commSPTR attackingCommander) override;
	void casualtyReport(INF::constArrayRef troopsLost, INF::constArrayRef injuredTroops) override;

	//Need this for some reason or else the program breaks
	void plaerActionShowHelp();

private:
	static std::vector<Participants> participantsList;
	static INF::i5array trainCosts;
	static int humanPlayers;

	INF::i5array allCommandersArray;
	INF::i5array allProvincesArray;

	COMM::commSPTR selectedCommander; //For ArmyDeploymentMA

	int
		capitalIndex,
		participantIndex;

	PROV::provSPTR capitalProvince;

	std::string kingdomName = " "; 

	std::unordered_map <std::string, COMM::commSPTR> commandersMap;
	std::unordered_map <std::string, PROV::provSPTR> provincesMap;
	std::unordered_map<std::string, COMM::commSPTR>::iterator commIt;

	PROV::provSPTRList provincesVector;
	COMM::commSPTRList commandersVector;

};

namespace PART {
	using partUPTR = std::unique_ptr<Participants>;
	using partSPTR = std::shared_ptr<Participants>;
	using partSPTRList = std::vector<partSPTR>;
}
#endif
