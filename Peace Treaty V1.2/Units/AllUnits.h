#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include "../Misc/ConstValues.h"
#include "../Misc/OF.h"
#include "../Coordinates.h"

/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/
using namespace CV;


class AllUnits : public Coords
{
public:
	//----Constructors----
	//One param overloaded Constructor
	AllUnits(int index);
	//Default Constructor
	AllUnits();


	int getCP();
	int getParticipantIndex();
	

	//----Troop Stuff----
	//Return a troop by index or all troops-- done by type. Pass -1 for troopIndex to return all troops of a type
	template<typename T> 
	T getTroop(CV::MutateTroopType type, int troopIndex, T data);
	//Change a troop by index or all trypes.
	template<typename T>
	T mutateTroop(CV::MutateTroopType type, int troopIndex, T amount, CV::MutateDirection direction);
	



	//Provinces & Commanders
	int getLevel();
	int getFoodConsumption() { return foodConsumption; }


  //resources
	void modifySpecificResource(int index, int amount, bool isAdd);
	void modifyResources(std::array<int, 5> resourcesArray, bool isAdd);
	int getResource(int resourceIndex){return resourcesPresent[resourceIndex];}
	std::array<int,5> getAllResources ();//Add implementation
	void printResources();


	void changeUnitName(std::string name);
	void changeParticipantIndex (int number) {participantIndex = number;}
  std::string getUnitName();


protected:
	std::array<int, 5> resourcesPresent = {0, 0, 0, 0, 0};
	std::array<int, 5> troopsPresent = {0, 0, 0, 0, 0};
	std::array<int, 5> troopsInjured = {0, 0, 0, 0, 0};
	std::array<int, 5> troopsLost = {0, 0, 0, 0, 0};
	int CP;
	int totalTroops;
	int foodConsumption;

	const int initialStats[5] = { 5, 4, 3, 2, 1 };

  //Coordinates;
	int xCoord = 0;
	int yCoord = 0;
	char canSelectThisUnit;
	int participantIndex;
	std::string unitName;
	std::string isCommanderOrProvince;
	int unitLevel;
	
};

#endif