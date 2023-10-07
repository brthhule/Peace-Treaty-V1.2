#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "Misc/ConstValues.h"
#include "Misc/OtherFunctions.h"

using namespace CV;

class Input {
public:
	static OtherFunctions OF;
	static std::vector<std::string> getShowPrompt(std::string prompt)
	{
		//For debugging
		OF.debugFunction("Input, showOptions");

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

	static std::string getOptionPrompt(CV::PROMPTS p) {

		//Print prompt, return acceptable values
		std::vector<std::string> AV = getShowPrompt(CV::promptsToString(p));
		
		return getOptionPromptQuery(AV);
	}

	static std::string getOptionPromptQuery(std::vector<std::string>AV){
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


private:

};
#endif