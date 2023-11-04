#include "Input.h"

using namespace Input;

std::vector<std::string> Input::getShowPrompt(std::string prompt)
{
	//For debugging
	OF::debugFunction("Input, showOptions");

	std::fstream newfile;

	//std::cout << "Opening file...\n";
	newfile.open("Prompts.txt", std::ios::in); // open a file to perform read operation using file object
	std::vector<std::string> acceptableValues = { "H" };
	std::cout << "List of options: \n";
	std::string line;
	std::string optionsLine;
	bool startReading = false;
	if (newfile.is_open())
	{
		std::cout << "File open";
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
	else {
		std::cout << "File closed";
	}
	
	newfile.close(); // close the file object.
	std::cout << "Return to previous menu (M)\n";

	//Options:S,R	
	optionsLine = optionsLine.substr(8);//S,R
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

std::string Input::getOptionPromptQuery(std::vector<std::string>AV) {
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

std::string Input::getOptionPrompt(CV::PROMPTS p) {

	//Print prompt, return acceptable values
	std::vector<std::string> AV = getShowPrompt(CV::promptsToString(p));

	return getOptionPromptQuery(AV);
}

std::string Input::getInputQuery(std::vector<std::string>AV) {
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

std::string Input::getInputText(std::string text, std::vector<std::string> AV)
{
	OF::debugFunction("Iput, getInputText");
	std::cout << text << "\n";
	std::string input;

	return getInputQuery(AV);
}

/*
Severity	Code	Description	Project	File	Line	Suppression State
Error	LNK2005	"class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Input::getInputQuery(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > >)" (?getInputQuery@Input@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@3@@Z) already defined in ArmyOverviewMA.obj	C:\Users\Brennen\Desktop\source\repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2.sln	C:\Users\Brennen\Desktop\source\repos\brthhule\Peace-Treaty-V1.2\ScoutMA.obj	1

*/