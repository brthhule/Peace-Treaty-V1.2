#ifndef CONSTVALUES_H
#define CONSTVALUES_H

#include <iostream>
#include <array>

#define UNIT_AMOUNT 5

namespace CV
{
	/*TROOP_NAMES = Militia, Guards, Cavalry, Knights, Paladins
	RESOURCE_BUILDING = Farm, Lumber Mill, Quarry, Mine, Church
	OTHER_BUILDING = Barracks, Infirmary, Library, Wall, Residences
	RESOURCE = Food, Wood, Ore, Gold, Mana*/
	const std::array<std::string, UNIT_AMOUNT> 
		TROOP_NAMES = { 
			"Militia", 
			"Guards", 
			"Cavalry", 
			"Knights", 
			"Paladins"
		},

		RESOURCE_BUILDING_NAMES = { 
			"Farm",
			"Lumber Mill",
			"Quarry", 
			"Mine", 
			"Church" 
		},

		OTHER_BUILDING_NAMES = { 
			"Barracks",
			"Infirmary",
			"Library",
			"Wall",
			"Residences" 
		},
		
		RESOURCE_NAMES = { 
			"Food",
			"Wood", 
			"Ore", 
			"Gold", 
			"Mana" 
		};

	/*TROOPS_COST = 5, 4, 3, 2, 1 
	* INITIAL_VALUES = 5, 4, 3, 2, 1 
	* TROOPS_CP = 1, 2, 4, 8, 16
	* RESOURCE_PRODUCTION = 5, 4, 3, 2, 1 
	*/
	typedef const std::array<int, UNIT_AMOUNT> ConstNumerics;
	ConstNumerics TROOPS_COST = { 5, 4, 3, 2, 1 },
				  INITIAL_VALUES = { 5, 4, 3, 2, 1 },
				  TROOPS_CP = { 1,2,4,8,16 },
				  RESOURCE_PRODUCTION = { 5,4,3,2,1 };

	const int BARRACKS_PRODUCTION = 2;
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
	/*"	SELECT_ENEMY_ACTION", 
		"PLAYER_UNIT_ACTION",
		"INTRODUCTION", 
		"PLAYER_ACTION",
		"ARMY_DEPLOYMENT", 
		"TRAIN_MA_FUNCTION",
		"PLAYER_BUILD_FUNCTION",
		"VIEW_PLAYER_MAP",
		"SELECT_PLAYER_PROVINCE", 
		"SELECT_ENEMY_PROVINCE", 
		"WHAT_REPORT"*/
	std::array<std::string, 11> PROMPTS_STRING = { 
		"SELECT_ENEMY_ACTION", 
		"PLAYER_UNIT_ACTION",
		"INTRODUCTION", 
		"PLAYER_ACTION",
		"ARMY_DEPLOYMENT", 
		"TRAIN_MA_FUNCTION",
		"PLAYER_BUILD_FUNCTION",
		"VIEW_PLAYER_MAP",
		"SELECT_PLAYER_PROVINCE", 
		"SELECT_ENEMY_PROVINCE", 
		"WHAT_REPORT" /*Add stuff for this*/
	};
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
	std::array<std::string, 9> COLORS_STRING = { 
		"BLACK", 
		"RED", 
		"GREEN", 
		"YELLOW", 
		"BLUE", 
		"MAGENTA", 
		"CYAN", 
		"WHITE", 
		"RESET" 
	};


	std::string promptsToString(PROMPTS p);
	int getStringIndex(std::string arg);
	PROMPTS stringToPrompts(std::string arg);
	

	int continentSize = 0,
		//Implement definition of this
		enemyDifficulty = 0;

	void addColor(COLORS c),
		 printPerson();

	std::array<int, 5> randomArray;
}

#endif		