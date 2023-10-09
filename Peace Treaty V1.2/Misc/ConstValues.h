#ifndef CONSTVALUES_H
#define CONSTVALUES_H

#include <iostream>
#include <array>

#define UNIT_AMOUNT 5

namespace CV
{
	const std::array<std::string, UNIT_AMOUNT> TROOP_NAMES = { "Militia", "Guards", "Cavalry", "Knights", "Paladins" };
	const std::array<std::string, UNIT_AMOUNT> RESOURCE_BUILDING_NAMES = { "Farm", "Lumber Mill", "Quarry", "Mine", "Church" };
	const std::array<std::string, 5> OTHER_BUILDING_NAMES = { "Barracks","Infirmary","Library","Wall","Residences" };
	const std::array<std::string, UNIT_AMOUNT> RESOURCE_NAMES = { "Food", "Wood", "Ore", "Gold", "Mana" };

	const std::array<int, UNIT_AMOUNT> TROOPS_COST = { 5, 4, 3, 2, 1 };
	const std::array<int, UNIT_AMOUNT> INITIAL_VALUES = { 5, 4, 3, 2, 1 };
	const std::array<int, UNIT_AMOUNT> TROOPS_CP = { 1,2,4,8,16 };
	const std::array<int, UNIT_AMOUNT> RESOURCE_PRODUCTION = { 5,4,3,2,1 };
	const int BARRACKS_PRODUCTION = 2;

	enum PROMPTS { SELECT_ENEMY_ACTION, PLAYER_UNIT_ACTION, INTRODUCTION, PLAYER_ACTION, ARMY_DEPLOYMENT, TRAIN_MA_FUNCTION, PLAYER_BUILD_FUNCTION, VIEW_PLAYER_MAP, SELECT_PLAYER_PROVINCE, SELECT_ENEMY_PROVINCE, WHAT_REPORT};
	std::array<std::string, 11> PROMPTS_STRING = { "SELECT_ENEMY_ACTION", "PLAYER_UNIT_ACTION", "INTRODUCTION", "PLAYER_ACTION", "ARMY_DEPLOYMENT", "TRAIN_MA_FUNCTION", "PLAYER_BUILD_FUNCTION", "VIEW_PLAYER_MAP", "SELECT_PLAYER_PROVINCE", "SELECT_ENEMY_PROVINCE", "WHAT_REPORT" /*Add stuff for this*/};


	enum COLORS {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET};
	std::array<std::string, 9> COLORS_STRING = { "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE", "RESET" };


	std::string promptsToString(PROMPTS p);
	int getStringIndex(std::string arg);
	PROMPTS stringToPrompts(std::string arg);
	void addColor(COLORS c);
}

#endif