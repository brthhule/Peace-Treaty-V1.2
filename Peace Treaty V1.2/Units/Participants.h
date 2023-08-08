#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <iostream>
#include <vector>

#include <string.h>
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>  
#include <ctime>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <map>
#include <unordered_map>

#include "AllUnits.h"
#include "Provinces.h"
#include "CommanderProfile.h"

#include "../Misc/OtherFunctions.h"
#include "../Misc/ConstValues.h"
#include "../Misc/LinkedList.h"

extern LinkedList provincesLL;
extern std::unordered_map<int, Provinces*> provincesHH;
using namespace CV;
extern int continentSize;
extern std::vector <std::vector <Provinces>> provincesMap;


class Participants
{
public:
	//constructors
	Participants(int pIndex);


	//Capital stuff
	Provinces* getCapital();
	void setCapital(Provinces *newProvince);
	std::string getNewName ();
	void showMapOld();
	void showMap();
	void showMapCoordinates();

	//Commander stuff
	int commandersNum();
	void addCommander();
	CommanderProfile* getCommander(int index);
	int getMaxCommanders ();
	std::array<int, 5> getTrainCosts();
	bool hasCommander(std::string name);
	CommanderProfile* getCommanderByName(std::string name);
  std::unordered_map<std::string, CommanderProfile*> getCommandersMap(){return commandersList;}
			
	//Province stuff
	int provincesNum();
	Provinces *findProvince(int x, int y);
	void addProvince(Provinces *newProvince);
	Provinces *getProvince (int index);
	void printListOfProvinces();
	bool subtractCheckResources(std::string provinceName, std::array<int, 5> resourcesArray);
	Provinces* getProvinceByName(std::string name);
  bool hasProvince (std::string name);
  //Provinces* selectRandomProvince();



	//Create participant
	void setKingdomName(std::string newName);
	std::string getKingdomName();
	void initialCapRSS();
	void createCapital();
	int findAllUnits();//Create funciton
	void setParticipantIndex(int num);
	int getParticipantIndex();

	//AI
	void createAsPlayer (bool choice);
	bool isAlive();
	bool isPlayer(){return playerStatus;}
  void setPlayerStatus (bool status){playerStatus = status;}

	//Stats
	std::vector<int> calculatePlayerValues (int decision);
	void viewAllStatsFunction();
	void viewStats();


	int calculateTotals (int option);
	std::array<int, 5> calculateEach(int option);


	//Coordinate stuff
	
	Provinces* getCoords(int identifier);
	Provinces* getYourProvince(int identifier);
	int getRandomCoordinate();

	//Scout stuff
	void scoutProvince(Provinces *targetProvince, int accuracy);

	void printParticipantStats(int option);

	//ArmyDeploymentMA stuff
	void displayCommanders();
	std::string selectCommander();
	CommanderProfile* getSelectedCommander(){return selectedCommander;}
  


private:
	std::string kingdomName = " ";
	bool playerStatus;//true = player, false = AI

	std::vector <Provinces*> provincesList;
	std::unordered_map <std::string, CommanderProfile*> commandersList;
	int capitalIndex;

	//Figure out sizes later
	int AIMainAction [5];
	int AIBuildMA [2];
	int AITroopMA [3];
std::array <int, 5> trainCosts = {5, 4, 3, 2, 1};
	int maxCommanders;
	int participantIndex;

	std::array <int, 5> troopsLost = { 0,0,0,0,0 };
	std::vector<std::vector<Provinces>> scoutMap;
	OtherFunctions OF;
  std::unordered_map<std::string, CommanderProfile*>::iterator it;
	CommanderProfile* selectedCommander; //For ArmyDeploymentMA
};

#endif
