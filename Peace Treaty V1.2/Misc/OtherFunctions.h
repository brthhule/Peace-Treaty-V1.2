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
#include <fstream>

#include "ConstValues.h"

using namespace CV;

extern int continentSize;
extern int currentParticipantIndex;


class OtherFunctions {
public:
	//Constructor
	OtherFunctions();

	// Check input-- maybe use template for this?
	std::string getInputPrompt(std::string text, std::vector<std::string> AV);
	std::string getInputValue(std::vector<std::string> AV);

	// Map stuff
	int translateCoordinate(int coordinate, char indicator, char whichWay);
	int translateCoordinateInput(int coordinate, char indicator);
	int translateCoordinateOutput(int coordinate, char indicator);
	std::string printCoordinates(std::array<int, 2> coordinates);
	int translateCoordinateToLL(int x, int y);

	// Name Functionality
	std::string createRandomName();

	// Other stuff
	static void clearScreen();
	static void enterAnything();

	//Manipulate vectors
	static std::array<int, 5> modifyArray(std::array<int, 5> primeArray, std::array<int, 5> secondaryArray, bool isAdd);
	static void printResources(std::array<int, 5> resourcesArray);

	//Debugging
	static void debugFunction(std::string functionName);

	//For if/ternary statements with no "else"
	static void nothing() {};

	//Text stuff
	std::vector<std::string> showOptions(int caseNum);
	char getOption(int caseNum);
	void printOptions(std::string tp, int& type, bool& skip, std::vector<std::string>& acceptableValues);
	void showHelp(int caseNum);
	void printFile(std::string fileName);

	char getOptionTwo(std::string type);



private:
	static bool debuggingMode;
};

#endif