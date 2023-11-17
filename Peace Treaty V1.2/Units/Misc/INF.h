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
	using ivector = std::vector<int>;
	using String = std::string;

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
		void createArray(std::array<int,5> arrayArg);
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
	extern std::array<std::string, 11> PROMPTS_STRING;

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
	/*	GUARDS,
		INFANTRY,
		ARCHERS,
		CAVALRY,
		ARTILLARY*/
	enum TroopTypes {
		GUARDS,
		INFANTRY,
		ARCHERS,
		CAVALRY,
		ARTILLARY
	};
	/*	SELECT_ENEMY_ACTION, 
		PLAYER_UNIT_ACTION, 
		INTRODUCTION, 
		PLAYER_ACTION, 
		ARMY_DEPLOYMENT, 
		TRAIN_MA_FUNCTION, 
		PLAYER_BUILD_FUNCTION, 
		VIEW_PLAYER_MAP, 
		SELECT_PLAYER_PROVINCE,
		SELECT_ENEMY_PROVINCE,
		WHAT_REPORT*/
	enum Prompts { 
		SELECT_ENEMY_ACTION, 
		PLAYER_UNIT_ACTION, 
		INTRODUCTION, 
		PLAYER_ACTION, 
		ARMY_DEPLOYMENT, 
		TRAIN_MA_FUNCTION, 
		PLAYER_BUILD_FUNCTION, 
		VIEW_PLAYER_MAP, 
		SELECT_PLAYER_PROVINCE,
		SELECT_ENEMY_PROVINCE,
		WHAT_REPORT
	};

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
	std::string promptsToString(Prompts p);
	//Get command to print certain color to console
	std::string getColor(COLORS color);

	std::string createRandomName();

	int getStringIndex(std::string arg);
	Prompts stringToPrompts(std::string arg);
	
	
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
	i5array modifyArray(i5array primeArray, i5array secondaryArray, bool isAdd);

	//For if/ternary statements with no "else"
	static void nothing() {};
	
}

#endif		