//Second level class

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

#include "..\..\..\Support\Paths.h"

#include LOG_HEADER
#include TUI_HEADER

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

	/*template <typename T>
	const T& makeConst(T& object);

	template <typename T>
	T makeCopy(T& object);*/

	/*
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

	template<typename T>
	class sPTRVector {
	public:
		sPTRVector<T>() {
			sharedPointersVector = {};
		}
		
		std::vector<std::shared_ptr<T>> get() { 
			return sharedPointersVector;
		}

		void push_back(sPTR<T> element) {
			sharedPointersVector.push_back(element);
		}

		void remove(int index) {
			sharedPointersVector.erase(sharedPointersVector.begin() + index);
		}

	private: 
		std::vector<sPTR<T>> sharedPointersVector;
	};
	*/
	//////////////////////////////////////Aliases//////////////////////////////
	


	//----Array/Vector Types-----------
	using s5array = std::array<std::string, UNIT_AMOUNT>;
	using d5array = std::array<double, UNIT_AMOUNT>;

	using ivector = std::vector<int>;
	using myvectorI = myvector<int>;
	using myarrayI5A = myarray<i5array>;
	using constArrayRef = const std::array<int, 5>&;

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


	

	///FARM, WOOD, STONE, ORE, MANA
	enum ResourceType {
		FARM = 0,
		WOOD,
		STONE,
		ORE,
		MANA
	};

	std::string str(int);

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
	extern s5array RESOURCE_NAMES;

	extern i5array INITIAL_VALUES;
	extern int
		continentSize,
		enemyDifficulty,
		CPUNum,
		turn,
		currentParticipantIndex;

	

	

	
	///////////////////////////////////Functions///////////////////////////////
	
	//----String-----------------------
	
	

	std::string createRandomName();

	///Takes an array of resources, formats and prints them out
	void printResources(constArrayRef resourcesArray);

	///Checks if a string is an inteer, only works for positive integers
	bool checkIsNumber(std::string number);


	
	
	
	//----void-------------------------
	//CLears the screen
	void clearScreen();
	//Prompts the user to enter anything
	void enterAnything(int option);
	///Calls enterAnything then clearScreen
	void enterAndClear(int option);

	//Text stuff
	void showHelp(int caseNum);
	void printFile(std::string path);
	//More text stuff
	void clearScreenCommand();

	
	std::string getText(std::string target);
	

	//Manipulate vectors
	i5array mutateArray(i5array primeArray, constArrayRef secondaryArray, MutateDirection direction);
}

#endif		