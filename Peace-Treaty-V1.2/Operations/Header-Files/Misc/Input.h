#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
C:\Users\Darren Zheng\source\repos
#include INF_HEADER

namespace Input 
{
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
		WHAT_REPORT,
		BATTLE_FORMATION,
		TRAIN_MA_FUNCTION_UNITS
	};

	//Turn Prompts element to a string
	std::string promptsToString(Input::Prompts prompt);

	extern std::array<std::string, 13> PROMPTS_STRING;

	int getStringIndex(std::string arg);
	Input::Prompts stringToPrompts(std::string arg);

	//For prompt input
	std::string getPrompt(Input::Prompts p);
	std::vector<std::string> showOptions(std::string prompt);
	std::string selectOption(std::vector<std::string>AV);
	std::string getInputText(std::string text, std::vector<std::string> AV);

	int getNumber(std::string text);
};
#endif