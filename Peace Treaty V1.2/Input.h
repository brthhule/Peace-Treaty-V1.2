#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "Misc/ConstValues.h"
#include "Misc/OF.h"

using namespace CV;
using namespace OF;

namespace Input 
{
	//For prompt input
	std::vector<std::string> getShowPrompt(std::string prompt);
	std::string getOptionPromptQuery(std::vector<std::string>AV);

	std::string getOptionPrompt(CV::PROMPTS p);
	std::string getInputQuery(std::vector<std::string>AV);


	//For text input
	std::string getInputText(std::string text, std::vector<std::string> AV);
};
#endif