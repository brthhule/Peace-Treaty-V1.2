#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "INF.h"
#include "INF.h"

using namespace INF;


namespace Input 
{
	//For prompt input
	std::vector<std::string> getShowPrompt(std::string prompt);

	std::string 
		getOptionPromptQuery(std::vector<std::string>AV),
		getOptionPrompt(INF::PROMPTS p),
		getInputQuery(std::vector<std::string>AV),
		getInputText(std::string text, std::vector<std::string> AV);
};
#endif