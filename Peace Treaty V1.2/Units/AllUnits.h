#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include "../Misc/ConstValues.h"
#include "../Misc/OF.h"

/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/
using namespace CV;


class AllUnits
{
public:
	//----Constructors----
	//One param overloaded Constructor
	AllUnits(int index);
	//Default Constructor
	AllUnits();


	int getCP();
	int getParticipantIndex();
	
	//--------Troop Functions--------
	
	//----Accessors----
	//Return troops of type index from this unit. Oldname; getTroopsPresent
	int getTroop(int troopIndex);
	std::array<int, 5> getAllTroops();
	//Change troops of type index at this unit by amount
	
	//----Mutators----
	
	void mutateTroop(CV::MutateTroopType type, int troopIndex, int amount, CV::MutateDirection direction);

	void AllUnits::mutateAllTroops(CV::MutateTroopType type, std::array<int, 5> amounts, CV::MutateDirection direction)

	void mutateAllTroops(std::array<int, 5> amounts, bool isAdd);
	void addInjuredTroops(std::array<int, 5> troops);
	std::array<int,5> getAllTroopsInjured();

	void addSpecificTroopLost(int index, int amount);
	void addTroopsLost(std::array<int, 5> troopsArray);
	std::array<int, 5> getAllTroopsLost();
	int getTotalTroops ();
	int getFoodConsumption (){return foodConsumption;}

	//Provinces & Commanders
	int getLevel();

	//Coordinate Stuff
	std::array<int, 2> getCoordinates();
	int getCoordinate(char which);
	std::string printOutputCoordinates();
	int translateX (bool isInput);
	int translateY (bool isInput);


  //resources
	void modifySpecificResource(int index, int amount, bool isAdd);
	void modifyResources(std::array<int, 5> resourcesArray, bool isAdd);
	int getResource(int resourceIndex){return resourcesPresent[resourceIndex];}
	std::array<int,5> getAllResources ();//Add implementation
	void printResources();
	std::string printCoordinates();
	std::string printRawCoordinates();


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