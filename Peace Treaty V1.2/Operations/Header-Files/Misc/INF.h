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


namespace INF {
	//////////////////////////////////////Aliases//////////////////////////////
	//----Symbolic Constants-----------
	constexpr int UNIT_AMOUNT = 5;

	//----Array/Vector Types-----------
	using s5array = std::array<std::string, UNIT_AMOUNT>;
	using i5array = std::array<int, UNIT_AMOUNT>;
	using d5array = std::array<double, UNIT_AMOUNT>;

	using ivector = std::vector<int>;
	using myvectorI = myvector<int>;
	using myarrayI5A = myarray<i5array>;

	//----Other Types------------------
	using String = std::string;
	using ipair = std::pair<int,int>;

	//----Const Values-----------------
	using constINT = const int&;
	using constI5array = std::array<constINT, 5>;

	using string = std::basic_string<char>; //Shenanigans

	///////////////////////////////////Enums/////////////////////////////////
	/*DECREASE = 0, INCREASE = 1*/
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

	enum SortType {
		ALPHABETICAL,
		LEVEL
	};


	/*BLACK = 0, RED, GREEN, YELLOW, BLUE, MAGENTA = 5, CYAN, WHITE, RESET*/
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

	///FARM, WOOD, STONE, ORE, MANA
	enum ResourceType {
		FARM = 0,
		WOOD,
		STONE,
		ORE,
		MANA
	};

	///////////////////////////////////Templates///////////////////////////////
	//---Vector/Array Implementations--
	template <typename T>
	class myvector : std::vector<int> {
	public:
		myvector(std::vector<int> vectorArg);
		void addVectorElements(myvector vectorArg);
	private:
	};

	template <typename T>
	class myarray : i5array {
	public:
		void createArray(INF::i5array arrayArg);
		void addArrayElements(myarray arrayArg);
	};

	

	template <typename T>
	std::vector<T> concatVectors(std::vector<std::vector<T>> vectorsList);
	

	template <class T>
	//std::array<T,5> template
	class Array5 {
	public:
		Array5(std::initializer_list<T> list);
		T& get(int index);
	private:
		std::array<T, 5> items;
	};
	///////////////////////////////////Variables///////////////////////////////
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

	extern int 
		continentSize, 
		enemyDifficulty,
		CPUNum,
		turn,
		currentParticipantIndex;

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

	

	
	///////////////////////////////////Functions///////////////////////////////
	
	//----String-----------------------
	//Get command to print certain color to console
	std::string getColor(COLORS color);
	

	std::string createRandomName();

	///Takes an array of resources, formats and prints them out
	void printResources(i5array resourcesArray);


	
	
	
	//----void-------------------------
	//CLears the screen
	inline void clearScreen();
	//Prompts the user to enter anything
	inline void enterAnything(int option);
	///Calls enterAnything then clearScreen
	inline void enterAndClear(int option);

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
	void nothing() {};
}

#endif		