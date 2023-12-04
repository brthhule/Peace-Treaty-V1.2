#include "Input.h"

namespace Input {
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
	std::array<std::string, 13> PROMPTS_STRING = {
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
			"WHAT_REPORT" /*Add stuff for this*/,
			"BATTLE_FORMATION" /*May not be used*/,
			"TRAIN_MA_FUNCTION_UNITS"
	};

	std::vector<std::string> getShowPrompt(std::string prompt) {
	//For debugging
		INF::debugFunction("Input, getShowPrompt");

		std::fstream newfile;
		"C:\\Users\\Brennen\\Source\\Repos\\brthhule\\Peace-Treaty-V1.2\\Peace Treaty V1.2\\Units\\Misc\\TxtFiles\\Synopsis.txt";

		std::string path = "C:\\Users\\Brennen\\Source\\Repos\\brthhule\\Peace-Treaty-V1.2\\Peace Treaty V1.2\\Units\\Misc\\TxtFiles\\Prompts.txt";

		std::vector<std::string> acceptableValues = { "H" };
		std::cout << "List of options: \n";
		std::string line;
		std::string optionsLine;
		bool startReading = false;

		// open a file to perform read operation using file object
		newfile.open(path, std::ios::in);

		if (!newfile.is_open()) {
			addColor(GREEN);
			std::cout << "Error occurred opening file...\n";
			addColor(RESET);
			return {};
		}

		while (getline(newfile, line)) {
			if (line.substr(0, 7) == "Options") {
				startReading = false;
				optionsLine = line;
			}

			if (startReading == true) {
				std::cout << line << "\n";
			}

			if (line.substr(0, line.find(" ")) == prompt) {
				startReading = true;
			}
		}



		newfile.close(); // close the file object.
		std::cout << "- Return to previous menu (M)\n";

		//Options:S,R	
		try {
			optionsLine = optionsLine.substr(8);//S,R
		} catch (...) {
			std::cout << "Error occurred in Input file\n";
		}

		//While there are more than one values
		while (optionsLine.find(",") != std::string::npos) {
			//Push back the first value
			acceptableValues.push_back(optionsLine.substr(0, optionsLine.find(",")));
			//Cut down the string of values
			optionsLine = optionsLine.substr(optionsLine.find(",") + 1);//R
		}
		//Add the last value (besides go back to previous menu)
		acceptableValues.push_back(optionsLine);
		acceptableValues.push_back("M");//go back to previous menu
		return acceptableValues;
	}

	std::string getOptionPromptQuery(std::vector<std::string>AV) {
		//For debugging
		INF::debugFunction("Input, getShowPromptQuery");

		std::string input;
		std::cout << "Enter an option: " << getColor(BLUE);
		getline(std::cin, input);
		addColor(RESET);

		for (int x = 0; x < (int)input.size(); x++) {
			input.at(x) = toupper(input.at(x));
		}

		for (std::string value : AV) {
			if (input == value) {
				return input;
			}
		}

		std::cout << "Invalid option entered... please try again.\n";
		return getOptionPromptQuery(AV);
	}

	std::string Input::getOptionPrompt(Prompts p) {
		//For debugging
		INF::debugFunction("Input, getOptionPrompt");

		//Print prompt, return acceptable values
		std::vector<std::string> AV = getShowPrompt(INF::promptsToString(p));

		return getOptionPromptQuery(AV);
	}

	std::string Input::getInputQuery(std::vector<std::string>AV) {
		//For debugging
		INF::debugFunction("Input, getInputQuery");

		std::cout << "Enter an option: " << getColor(BLUE);
		std::string input;
		getline(std::cin, input);
		INF::addColor(RESET);

		for (std::string value : AV) {
			if (input == value) {
				return value;
			}
		}

		std::cout << "Invalid option... please try again.\n";
		return getInputQuery(AV);
	}

	std::string getInputText(std::string text, std::vector<std::string> AV) {
		//For debugging
		INF::debugFunction("Iput, getInputText");

		std::cout << text << "\n";
		std::string input;

		return getInputQuery(AV);
	}

	std::string Input::promptsToString(Prompts p) {
		//For debugging
		INF::debugFunction("CV, promptsToString");

		return PROMPTS_STRING[p];
	}

	int Input::getStringIndex(std::string arg) {
		//For debugging
		INF::debugFunction("CV, getStringIndex");

		for (int x = 0; x < (signed)PROMPTS_STRING.size(); x++) {
			if (PROMPTS_STRING[x] == arg) {
				return x;
			}
		}
		//Error case
		return -1;
	}

	Prompts INF::stringToPrompts(std::string arg) {
		//For debugging
		INF::debugFunction("CV, stringToPrompts");

		return Prompts(INF::getStringIndex(arg));
	}
};
