#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INF_HEADER

using namespace INF;


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

	std::string promptsToString(Prompts p);
	extern std::array<std::string, 13> PROMPTS_STRING;
	int getStringIndex(std::string arg);
	Prompts stringToPrompts(std::string arg);

	//For prompt input
	std::vector<std::string> getShowPrompt(std::string prompt);

	std::string 
		getOptionPromptQuery(std::vector<std::string>AV),
		getOptionPrompt(Prompts p),
		getInputQuery(std::vector<std::string>AV),
		getInputText(std::string text, std::vector<std::string> AV);
};
#endif