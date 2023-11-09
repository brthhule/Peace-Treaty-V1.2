#ifndef CV_H
#define CV_H

#include <array>
#include <iostream>
#include <vector>
#include <array>

#include "OF.h"

#define UNIT_AMOUNT 5

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

namespace CV
{
	using StringArray = const std::array<std::string, UNIT_AMOUNT>;
	using ConstNumerics = const std::array<int, UNIT_AMOUNT>;
	
	
	extern StringArray
		TROOP_NAMES,
		RESOURCE_BUILDING_NAMES,
		OTHER_BUILDING_NAMES,
		RESOURCE_NAMES;

	

	extern ConstNumerics
		TROOPS_COST,
		INITIAL_VALUES,
		TROOPS_CP,
		RESOURCE_PRODUCTION;

	extern const int BARRACKS_PRODUCTION;

	/*	GUARDS,
		INFANTRY,
		ARCHERS,
		CAVALRY,
		ARTILLARY*/
	enum TROOPS {
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
	enum PROMPTS { 
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
	
	extern std::array<std::string, 11> PROMPTS_STRING;

	/*REGULAR, 
		INJURED,
		LOST */
	enum MutateTroopType { 
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

	

	std::string promptsToString(PROMPTS p);
	int getStringIndex(std::string arg);
	PROMPTS stringToPrompts(std::string arg);
	
	void debugFunction(std::string functionName);

	extern int
		continentSize,
		enemyDifficulty,
		CPUNum,
		turn,
		UNIT_AMOUNT_CV,
		currentParticipantIndex,
		maxCommanders;
	extern bool debuggingMode;;

	void printPerson();

	using ARRAY = std::array<int, 5>;
	using INTEGER = int;
	using STRING = std::string;
	using VOID = void;
	using INT_VECTOR = std::vector<int>;
	using BOOL = bool;
}

#endif		