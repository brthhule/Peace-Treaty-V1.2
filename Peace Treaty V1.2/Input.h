#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "Misc/ConstValues.h"
#include "Misc/OF.h"

using namespace CV;
using namespace OF;

namespace Input {
	//For prompt input
	std::vector<std::string> getShowPrompt(std::string prompt)
	{
		//For debugging
		OF::debugFunction("Input, showOptions");

		std::fstream newfile;

		//std::cout << "Opening file...\n";
		newfile.open("Prompts.txt", std::ios::in); // open a file to perform read operation using file object
		std::vector<std::string> acceptableValues = { "H" };

		std::string line;
		std::string optionsLine;
		bool startReading = false;
		if (newfile.is_open())
		{
			while (getline(newfile, line)) {
				if (line.substr(0, 7) == "Options") {
					startReading = false;
					optionsLine = line;
				}
				
				if (startReading == true) {
					std::cout << line;
				}

				if (line.substr(0, line.find(" ")) == prompt) {
					startReading = true;
				}
			}
		}
		newfile.close(); // close the file object.

		//Options:S,R	
		optionsLine = optionsLine.substr(8);//S,R
		//While there are more than one values
		while (optionsLine.find(",") != std::string::npos) {
			//Push back the first value
			acceptableValues.push_back(optionsLine.substr(0, optionsLine.find(",")));
			//Cut down the string of values
			optionsLine = optionsLine.substr(optionsLine.find(",") + 1);//R
		}
		//Add the last value
		acceptableValues.push_back(optionsLine);
		return acceptableValues;
	}

	std::string getOptionPrompt(CV::PROMPTS p) {

		//Print prompt, return acceptable values
		std::vector<std::string> AV = getShowPrompt(CV::promptsToString(p));
		
		return getOptionPromptQuery(AV);
	}

	std::string getOptionPromptQuery(std::vector<std::string>AV){
		std::string input;
		std::cout << "Enter an option: ";
		
		getline(std::cin, input);
		for (std::string value : AV) {
			if (input == value) {
				return input;
			}
		}

		std::cout << "Invalid option entered... please try again.\n";
		return getOptionPromptQuery(AV);
	}


	//For text input
	std::string getInputText(std::string text, std::vector<std::string> AV)
	{
		OF::debugFunction("Iput, getInputText");
		std::cout << text << "\n";
		std::string input;

		return getInputQuery(AV);
	}

	std::string getInputQuery(std::vector<std::string>AV) {
		std::cout << "Enter an option: ";
		std::string input;

		CV::addColor(RED);
		getline(std::cin, input);
		CV::addColor(RESET);

		for (std::string value : AV) {
			if (input == value) {
				return value;
			}
		}

		std::cout << "Invalid option... please try again.\n";
		return getInputQuery(AV);
	}
};
#endif