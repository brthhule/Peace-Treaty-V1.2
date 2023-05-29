#include "AllUnits.h"

//Constructor
AllUnits::AllUnits(int index)
{
	for (int x = 0; x < 5; x++)
	{
		resourcesPresent[x] = initialStats[x];
		troopsPresent[x] = 0;
		troopsInjured[x] = 0;
	}
	CP = 0;
	totalTroops = 0;
	foodConsumption = 0;
	canSelectThisUnit = 'N';
	participantIndex = index;
}

//Accessor Functions

int AllUnits::getTroopsPresent(int troopTypeIndex){
	return troopsPresent[troopTypeIndex];
}

std::array<int, 5> AllUnits::getAllTroopsPresent(){
	return troopsPresent;
}

void AllUnits::modifyTroops(std::array<int, 5> troopsAdd, bool isAdd){
	troopsPresent = OF.modifyArray(troopsPresent, troopsAdd, isAdd);
}

void AllUnits::modifySpecificTroop(int index, int amount, bool isAdd)
{
	if (isAdd)
		troopsPresent[index] += amount;
	else
		troopsPresent[index] -= amount;
}

void AllUnits::addSpecificInjuredTroop(int troopIndex, int amount){
	troopsInjured[troopIndex] += amount;
}
void AllUnits::addInjuredTroops(std::array<int, 5> troops){
	troopsInjured = OF.modifyArray(troopsInjured, troops, true);
}

int AllUnits::getCP(){
	CP = 0;
	for (int x = 0; x < 5; x++){
		CP += troopsPresent[x] * CV.TROOPS_CP[x];
	}
	return CP;
}

int AllUnits::getParticipantIndex()
{
	return participantIndex;
}

void AllUnits::printResources()
{
	std::cout << "Resources currently present in this " << isCommanderOrProvince << ": \n";
    std::cout << "\033[;34m";
	OF.printResources(resourcesPresent);
	std::cout << "\033[;0m";
}

std::string AllUnits::getUnitName()
{
	return unitName;
}
void AllUnits::changeUnitName(std::string name)
{
	unitName = name;
}

//Mutator Functions


void AllUnits::modifySpecificResource(int index, int amount, bool isAdd)
{
	if (isAdd)
		resourcesPresent[index] += amount;
	else
		resourcesPresent[index] -= amount;
}

void AllUnits::modifyResources(std::array<int, 5> resourcesArray, bool isAdd)
{
	OF.modifyArray(resourcesPresent, resourcesArray, isAdd);
}

int AllUnits::getLevel()
{
	return unitLevel;
}

std::string AllUnits::printOutputCoordinates()
{
	int x = yCoord + 1;
	int y = continentSize - xCoord - 1;
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

int AllUnits::translateX(bool isInput)
{
	if (isInput)
		return xCoord - 1;
	else
		return xCoord + 1;
}

int AllUnits::translateY(bool isInput)
{
	if (isInput)
		return abs(yCoord - continentSize);

	return abs(continentSize - yCoord);
}

std::array<int, 2> AllUnits::getCoordinates()
{
	return {xCoord, yCoord};
}

int AllUnits::getCoordinate(char which)
{
	if (which == 'X')
		return xCoord;
	return yCoord;
}

void AllUnits::addSpecificTroopLost(int index, int amount)
{
	troopsLost[index] += amount;
}

void AllUnits::addTroopsLost(std::array<int, 5> troopsArray)
{
	troopsLost = OF.modifyArray(troopsLost, troopsArray, true);
}
std::array<int, 5> AllUnits::getAllTroopsLost()
{
	return troopsLost;
}

std::string AllUnits::printCoordinates()
{
	return OF.printCoordinates({xCoord, yCoord});
}

std::array<int,5> AllUnits::getAllResources()
{
  return resourcesPresent;
}

std::array<int,5> AllUnits::getAllTroopsInjured()
{
	return troopsInjured;
}

int AllUnits::getTotalTroops()
{
	int troopsNum = 0;
	for (int x: troopsPresent)
		troopsNum += x;
	return troopsNum;
}

std::string AllUnits::printRawCoordinates()
{
	return "(" + std::to_string(xCoord) + ", " + std::to_string(yCoord) + ")";
}