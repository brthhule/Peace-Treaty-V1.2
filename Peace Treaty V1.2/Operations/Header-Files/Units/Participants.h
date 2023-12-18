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
		i5array getAllUnitsArray();//???

		///Returns a commander this Participant owns by name
		commSPTR getCommander(std::string name);
		///Return the unordered_map of Commander shared pointers
		std::unordered_map<std::string, COMM::commSPTR> getCommandersMap();

		///Got total number of Provinces in this participant
		int getProvincesNum();
		///Get total number of Commanders in this participant
		int getCommandersNum();
		///Return total number of Commanders + Provinces in this Participant
		int getAllUnitsAmount();
		///Get the index of this participant in the vector of all participants
		int getParticipantIndex();

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

		
			

		ivector calculatePlayerValues(int decision);

		int calculateTotals(int option);

		

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

		COMM::commSPTR pickCommander();

		void setCapital(provSPTR newProvince);
		void showMapOld();

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

		void getAllUnitsArrayCommanders();
		void getAllUnitsArrayProvinces();

		void updateTurnResourcesParticipant();
		void createMapParticipant();

		ARMY_OVERVIEW_MA_ START
			/** printCosts__ Print commander upgrade costs

				@param costs__ array with resource costs amount
				@param phrase__ 1 prints "commander upgrade"
				@return void
			*/
			void printCosts(i5array costs, int phrase);

			/** armyOverviewMain
				Main method for ArmyOverviewMA

				@param void
				@return void
			*/
		void armyOverviewMain();
		void trainCommanders();
		void proceedWithTraining(i5array trainCosts);
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
			void trainMAMain();
		void trainMALoop(int troopTier, int amountOfTroops);

		void moveUnitOne(COMM::commSPTR commander);
		std::vector <provSPTR> moveUnitTwo(COMM::commSPTR commander);
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
		SCOUT_MA END

			ATTACK_MA START
			class AttackMAInfo {
			AttackMAInfo();
			AttackMAInfo(provSPTR defendingProvinceArg);
			AttackMAInfo(provSPTR defenderProvinceArg, COMM::commSPTR commanderArg);

			provSPTR defendingProvince;
			//partSPTR attackingParticipant; is this object
			COMM::commSPTR commander;
			bool defenseCanRetreat;
		};
		void mainAttackMA(
			provSPTR defendingProvince,
			COMM::commSPTR attackingCommander);

		GETTER
			std::vector<COMM::commSPTR> getCommandersCanAttack(provSPTR defendingProvince);
		void playerCommitAttack(provSPTR defendingProvince, COMM::commSPTR attackingCommander);
		COMM::commSPTR pickCommanderAttack(std::vector<COMM::commSPTR> commandersCanAttack);

		GETTER
			void printResourcesGained();
		void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP);

		CALCULATE
			void calculateTroopsLost(COMM::commSPTR commander, int lostCombatPower, i5array& troopsLost, int troopIndex);
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

		std::unordered_map <std::string, COMM::commSPTR> commandersMap;
		std::unordered_map <std::string, provSPTR> provincesMap;
		std::unordered_map<std::string, COMM::commSPTR>::iterator commIt;

		std::vector <provSPTR> provincesVector;
		std::vector <COMM::commSPTR> commandersVector;
	};

	using partSPTR = std::shared_ptr<Participants>;
	using partSPTRList = std::vector<partSPTR>;
}
#endif
