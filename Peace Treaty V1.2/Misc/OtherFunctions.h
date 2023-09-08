#ifndef OTHERFUNCTIONS_H
#define OTHERFUNCTIONS_H

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

#include "ConstValues.h"

using namespace CV;

extern int continentSize;
extern int currentParticipantIndex;
extern bool debuggingMode;

class OtherFunctions {
public:
	//Constructor
	OtherFunctions();

	// Check input-- maybe use template for this?
	std::string getInput(bool isSO, int caseNumArg, std::string text, std::vector<std::string> AV, bool isNumber, bool redo);

	// Map stuff
	int translateCoordinate(int coordinate, char indicator, char whichWay);
	int translateCoordinateInput(int coordinate, char indicator);
	int translateCoordinateOutput(int coordinate, char indicator);
	std::string printCoordinates(std::array<int, 2> coordinates);
	int translateCoordinateToLL(int x, int y);

	// Name Functionality
	std::string createRandomName();

	// Other stuff
	void clearScreen();
	void enterAnything();

	//Manipulate vectors
	std::array<int, 5> modifyArray(std::array<int, 5> primeArray, std::array<int, 5> secondaryArray, bool isAdd);
	void printResources(std::array<int, 5> resourcesArray);

	//Debugging
	void debugFunction(std::string functionName);

	//For if/ternary statements with no "else"
	void nothing() {};

	//Text stuff
	std::vector<std::string> showOptions(int caseNum);
	char getOption(int caseNum);
	void printOptions(std::string tp, int& type, bool& skip, std::vector<std::string>& acceptableValues);
	void showHelp(int caseNum);
	void printFile(std::string fileName);



private:
};

#endif