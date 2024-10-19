#include "..\..\..\Support\Paths.h"
#include INPUT_HEADER
#include LOG_HEADER

using namespace INF;

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

std::vector<std::string> showOptions(std::string prompt) {
	DEBUG_FUNCTION("Input.cpp", "showOptions");
	LOG::DEBUG("prompt: " + prompt + "\n");
	std::fstream newfile;
	std::string path = "C:/Users/Brennen/source/repos/brthhule/Peace-Treaty-V1.2/Peace-Treaty-V1.2/Support/TxtFiles/Prompts.txt";

	std::vector<std::string> acceptableValues = { "H" };
	LOG::addColor(LOG::GREEN);
	std::cout << "List of options: \n";

	// open a file to perform read operation using file object
	newfile.open(path, std::ios::in);
	if (!newfile.is_open()) {
		LOG::ERROR("Error occurred opening file...\n");
		return {};
	}
	
	bool startReading = false;
	std::string line = "";
	std::string optionsLine = "";

	while (getline(newfile, line)) {
		if (line.substr(0, 7) == "Options" && startReading == true) {
			startReading = false;
			optionsLine = line;
			break;
		}

		if (startReading == true) {
			std::cout << line << "\n";
		}

		if (line == prompt) {
			startReading = true;
		}
	}



	newfile.close(); // close the file object.
	std::cout << "- Return to previous menu (M)\n";

	//Options:S,R	
	try {
		optionsLine = optionsLine.substr(8);//S,R
	} catch (...) {
		LOG::ERROR("Error occurred in Input file\n");
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

	LOG::addColor(LOG::RESET);
}

std::string getPrompt(Prompts p) {
	//For debugging
	DEBUG_FUNCTION("Input.cpp", "getPrompt");

	//Print prompt, return acceptable values
	std::vector<std::string> AV = showOptions(promptsToString(p));

	return selectOption(AV);
}

std::string selectOption(std::vector<std::string>AV) {
	//For debugging
	DEBUG_FUNCTION("Input.cpp", "selectOption");

	std::cout << "Enter an option: " << LOG::getColor(LOG::BLUE);  
	std::string input;
	getline(std::cin, input);
	for (int i = 0; i < input.size(); i++) {
		input[i] = toupper(input[i]);
	}
	LOG::addColor(LOG::RESET);

	for (std::string value : AV) {
		if (input == value) {
			return value;
		}
	}

	std::cout << "Invalid option... please try again.\n";
	return selectOption(AV);
}

std::string getInputText(std::string text, std::vector<std::string> AV) {
	//For debugging
	DEBUG_FUNCTION("Input", "getInputText");

	std::cout << text << "\n";

	if (AV.size() != 0) {
		return selectOption(AV);
	}
		
	std::string input = "";
	getline(std::cin, input);
	return input;
}

std::string promptsToString(Prompts p) {
	//For debugging
	DEBUG_FUNCTION("Input.cpp" ,"promptsToString");

	return PROMPTS_STRING.at(p);
}

int getStringIndex(std::string arg) {
	//For debugging
	DEBUG_FUNCTION("Input.cpp", "getStringIndex");

	for (int x = 0; x < (signed)PROMPTS_STRING.size(); x++) {
		if (PROMPTS_STRING.at(x) == arg) {
			return x;
		}
	}
	//Error case
	return -1;
}

Prompts stringToPrompts(std::string arg) {
	//For debugging
	DEBUG_FUNCTION("Input.cpp", "stringToPrompts");

	return Prompts(getStringIndex(arg));
}

int getNumber(std::string text) {
	std::string numberString = getInputText(text, {});
	if (INF::checkIsNumber(numberString) == false) {
		if (numberString == "-1") {
			return -1;
		}
		std::cout << "Invalid entry entered, please try again...\n";
		getNumber(text);
	}

	return std::stoi(numberString);
}

};

