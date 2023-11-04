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

#include "CV.h"

using namespace CV;


namespace OF {
	static const bool debuggingMode = true;

	// Name Functionality
	std::string createRandomName();

	// Other stuff
	void clearScreen();
	void enterAnything();

	//Manipulate vectors
	std::array<int, 5> modifyArray(std::array<int, 5> primeArray, std::array<int, 5> secondaryArray, bool isAdd);

	//Debugging
	void debugFunction(std::string functionName);

	//For if/ternary statements with no "else"
	static void nothing() {};

	//Text stuff
	void showHelp(int caseNum);
	void printFile(std::string fileName);

	
}

#endif