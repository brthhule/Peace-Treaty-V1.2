#ifndef INF_H
#define INF_H

#include <array>
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

#include "INF.h"

#define UNIT_AMOUNT 5

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
#define Systemoutprintln(x) std::cout << x;

namespace INF
{
	/////////////////////////////////////Aliases///////////////////////////////
	using s5array = std::array<std::string, UNIT_AMOUNT>;
	using i5array = std::array<int, UNIT_AMOUNT>;
	using d5array = std::array<double, UNIT_AMOUNT>;

	using ivector = std::vector<int>;
	using String = std::string;
	using ipair = std::pair<int, int>;

	using INTEGER = int;
	using STRING = std::string;
	using VOID = void;
	using BOOL = bool;

	///////////////////////////////////Templates///////////////////////////////
	//Creating my own vector version to enable vector element addition
	template <typename T>
	class myvector : std::vector<int> {
	public:
		myvector(std::vector<int> vectorArg);
		void addVectorElements(myvector vectorArg);
	private:
	};

	template <typename T>
	class myarray : std::array<int, 5> {
	public:
		void createArray(INF::i5array arrayArg);
		void addArrayElements(myarray arrayArg);
	};

	using myvectorI = myvector<int>;
	using myarrayI5A = myarray<std::array<int, 5>>;
	
	/////////////////////////////////Variables/////////////////////////////////
	extern s5array
		TROOP_NAMES,
		RESOURCE_BUILDING_NAMES,
		OTHER_BUILDING_NAMES,
		RESOURCE_NAMES;

	extern i5array
		Troops_COST,
		INITIAL_VALUES,
		Troops_CP,
		RESOURCE_PRODUCTION;

	extern const int BARRACKS_PRODUCTION;

	extern int 
		continentSize, 
		enemyDifficulty,
		CPUNum,
		turn,
		UNIT_AMOUNT_CV,
		currentParticipantIndex,
		maxCommanders;

	extern bool debuggingMode;

	/*"BLACK",
		"RED",
		"GREEN",
		"YELLOW",
		"BLUE",
		"MAGENTA",
		"CYAN",
		"WHITE",
		"RESET" */
	extern std::array<std::string, 9> COLORS_STRING;

	/////////////////////////////////////Enums/////////////////////////////////

	/*REGULAR, 
		INJURED,
		LOST */
	enum TroopCondition { 
		REGULAR, 
		INJURED,
		LOST 
	};

	/*DECREASE = 0, 
		INCREASE = 1*/
	enum MutateDirection {
		DECREASE = 0, 
		INCREASE = 1
	};
	/*SINGLE = 0, 
		ALL = 1*/
	enum Quantity {
		SINGLE = 0, 
		ALL = 1
	};

	
	/*BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		RESET*/
	enum COLORS {
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		RESET
	};

	
	//////////////////////////////Functions////////////////////////////////////
	
	//////////////string///////////////
	//Get command to print certain color to console
	std::string getColor(COLORS color);

	std::string createRandomName();

	
	
	
	//////////////void/////////////////
	//CLears the screen
	void clearScreen();
	//Prompts the user to enter anything
	void enterAnything(int option);
	//Debugging purposes
	void debugFunction(std::string functionName);
	//Text stuff
	void showHelp(int caseNum);
	void printFile(std::string path);
	//More text stuff
	void clearScreenCommand();

	//Adds color to console
	void addColor(COLORS c);
	
	

	//Manipulate vectors
	i5array mutateArray(i5array primeArray, i5array secondaryArray, MutateDirection direction);

	//For if/ternary statements with no "else"
	static void nothing() {};
	
}

#endif		