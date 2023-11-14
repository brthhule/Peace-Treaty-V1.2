#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "CV.h"
#include "CV.h"

using namespace CV;


namespace Input 
{
	//For prompt input
	std::vector<std::string> getShowPrompt(std::string prompt);

	std::string 
		getOptionPromptQuery(std::vector<std::string>AV),
		getOptionPrompt(CV::PROMPTS p),
		getInputQuery(std::vector<std::string>AV),
		getInputText(std::string text, std::vector<std::string> AV);
};
#endif