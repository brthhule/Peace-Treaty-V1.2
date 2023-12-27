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

#define Array5(x) std::array<x, 5>

namespace INF {
	//----Symbolic Constants-----------
	constexpr int UNIT_AMOUNT = 5;

	using i5array = std::array<int, UNIT_AMOUNT>;
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
		void createArray(i5array arrayArg);
		void addArrayElements(myarray arrayArg);
	};

	template <typename T>
	const T& makeConst(T& object);

	template <typename T>
	T makeCopy(T& object);

	template<class T>
	//Shared pointer of type T
	class sPTR {
	public:
		sPTR<T>(T thing) {
			ptr = std::make_shared<T>(thing);
		}
		sPTR<T>() {
			ptr = nullptr;
		}
		std::shared_ptr<T> get() {
			return ptr;
		}

		static std::shared_ptr<T> makeSPTR(T thing) {
			return std::make_shared<T>(thing);
		}
	private:
		std::shared_ptr<T> ptr;
	};

	class sPTRVector {
	public:
		sPTR<T>(T thing) {
			ptr = std::make_shared<T>(thing);
		}
		sPTR<T>() {
			ptr = nullptr;
		}
		std::shared_ptr<T> get() {
			return ptr;
		}

		static std::shared_ptr<T> makeSPTR(T thing) {
			return std::make_shared<T>(thing);
		}
	private:
		std::shared_ptr<T> ptr;
	};

	//////////////////////////////////////Aliases//////////////////////////////
	


	//----Array/Vector Types-----------
	using s5array = std::array<std::string, UNIT_AMOUNT>;
	using d5array = std::array<double, UNIT_AMOUNT>;

	using ivector = std::vector<int>;
	using myvectorI = myvector<int>;
	using myarrayI5A = myarray<i5array>;
	using constArrayReference = const std::array<int, 5>&;

	//----Other Types------------------
	using String = std::string;
	using ipair = std::pair<int,int>;

	//----Const Values-----------------
	using constINT = const int&;
	using constI5array = std::array<constINT, 5>;

	using string = std::basic_string<char>; //Shenanigans

	///////////////////////////////////Enums/////////////////////////////////
	/*DECREASE = 0, INCREASE = 1*/

	enum ProvinceRelation { 
		ENEMY_PROVINCE, FRIENDLY_PROVINCE };

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
	std::vector<T> concatVectors(std::vector<std::vector<T>> vectorsList);
	
	/*
	template <class T>
	//std::array<T,5> template
	class Array5 {
	public:
		Array5(std::initializer_list<T> list);
		T& at(int index);
	private:
		std::array<T, 5> items;
	};*/

	///////////////////////////////////Variables///////////////////////////////
	extern s5array
		TROOP_NAMES,
		RESOURCE_BUILDING_NAMES,
		OTHER_BUILDING_NAMES,
		RESOURCE_NAMES;

	extern i5array
		Troops_COST,
		INITIAL_VALUES,
		TROOPS_CP,
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
	void printResources(constArrayReference resourcesArray);

	///Checks if a string is an inteer, only works for positive integers
	bool checkIsNumber(std::string number);


	
	
	
	//----void-------------------------
	//CLears the screen
	inline void clearScreen();
	//Prompts the user to enter anything
	inline void enterAnything(int option);
	///Calls enterAnything then clearScreen
	inline void enterAndClear(int option);

	//Text stuff
	void showHelp(int caseNum);
	void printFile(std::string path);
	//More text stuff
	void clearScreenCommand();

	//Adds color to console
	void addColor(COLORS c);
	
	

	//Manipulate vectors
	i5array mutateArray(i5array primeArray, constArrayReference secondaryArray, MutateDirection direction);

	
}

#endif		