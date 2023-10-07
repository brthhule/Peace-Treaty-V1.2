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





	const enum PROMPTS { INTRODUCTION };
	const std::array<std::string, 1> PROMPTS_STRING = { "INTRODUCTION" };

	std::string promptsToString(PROMPTS p) {
		return PROMPTS_STRING[p];
	}

	PROMPTS stringToPrompts(std::string arg) {
		return PROMPTS(getStringIndex(arg));
	}

	int getStringIndex(std::string arg) {
		for (int x = 0; x < PROMPTS_STRING.size(); x++) {
			if (PROMPTS_STRING[x] == arg) {
				return x;
			}
		}
		//Error case
		return -1;
	}

	const enum COLORS {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET};
	const std::array<std::string, 9> COLORS_STRING = { "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE", "RESET" };



	void addColor(COLORS c) {
		/*The color definition is a series of numbers, separated by semicolons. In order to make the text color red (number 31), you can write "\033[31m" which will make any following output red. If you want yellow text (33) on blue background (44), you write "\033[31;44m". To reset everything back to the default colors, you write "\033[0m".

		foreground background
		black        30         40
		red          31         41
		green        32         42
		yellow       33         43
		blue         34         44
		magenta      35         45
		cyan         36         46
		white        37         47*/

		switch (c) {
		case BLACK:
			std::cout << "\033[30m";
			break;
		case RED:
			std::cout << "\033[31m";
			break;
		case GREEN:
			std::cout << "\033[32m";
			break;
		case YELLOW:
			std::cout << "\033[33m";
			break;
		case BLUE:
			std::cout << "\033[34m";
			break;
		case MAGENTA:
			std::cout << "\033[35m";
			break;
		case CYAN:
			std::cout << "\033[36m";
			break;
		case WHITE:
			std::cout << "\033[37m";
			break;
		case RESET:
			std::cout << "\033[0m";
			break;
		}
	}


};

#endif