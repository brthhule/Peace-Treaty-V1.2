#ifndef CV_H
#define CV_H

#include <array>
#include <iostream>
#include <vector>

#define UNIT_AMOUNT 5

namespace CV
{
	typedef const std::array<std::string, UNIT_AMOUNT> StringArray;
	typedef const std::array<int, UNIT_AMOUNT> ConstNumerics;
	
	
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

	std::string promptsToString(PROMPTS p);
	int getStringIndex(std::string arg);
	PROMPTS stringToPrompts(std::string arg);
	

	extern int 
		continentSize,
		enemyDifficulty,
		CPUNum,
		turn,
		UNIT_AMOUNT_CV,
		currentParticipantIndex;

	void addColor(COLORS c),
		 printPerson();

	typedef std::array<int, 5> ARRAY;
	typedef int INTEGER;
	typedef std::string STRING;
	typedef void VOID;
	typedef std::vector<int> INT_VECTOR;
	typedef bool BOOL;
}

#endif		