#include "Input.h"

using namespace Input;

std::vector<std::string> Input::getShowPrompt(std::string prompt)
{
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

std::string Input::getOptionPromptQuery(std::vector<std::string>AV) {
	//For debugging
	INF::debugFunction("Input, getShowPromptQuery");

	std::string input;
	std::cout << "Enter an option: " << getColor(BLUE);
	getline(std::cin, input);
	addColor(RESET);

	for (int x = 0; x < (int) input.size(); x++) {
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

std::string Input::getOptionPrompt(INF::Prompts p) {
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

std::string Input::getInputText(std::string text, std::vector<std::string> AV)
{
	//For debugging
	INF::debugFunction("Iput, getInputText");

	std::cout << text << "\n";
	std::string input;

	return getInputQuery(AV);
}

/*
Severity	Code	Description	Project	File	Line	Suppression State
Error	LNK2005	"class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Input::getInputQuery(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > >)" (?getInputQuery@Input@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@3@@Z) already defined in ArmyOverviewMA.obj	C:\Users\Brennen\Desktop\source\repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2.sln	C:\Users\Brennen\Desktop\source\repos\brthhule\Peace-Treaty-V1.2\ScoutMA.obj	1

*/