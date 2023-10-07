#ifndef OF_H
#define OF_H

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
#include <fstream>

#include "ConstValues.h"

using namespace CV;

extern int continentSize;
extern int currentParticipantIndex;


namespace OF {
	static const bool debuggingMode = true;
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
	static void nothing() {};

	//Text stuff
	void showHelp(int caseNum);
	void printFile(std::string fileName);

	
}

#endif