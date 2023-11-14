#include "CV.h"

namespace CV {
	////////////////////////////////////////////////Start Variables///////////////////////////////////////
	/*TROOPS_COST = 5, 4, 3, 2, 1 */
	ConstNumerics TROOPS_COST = { 5, 4, 3, 2, 1 };

	/*INITIAL_VALUES = 5, 4, 3, 2, 1 */
	ConstNumerics INITIAL_VALUES = { 5, 4, 3, 2, 1 };

	/*TROOPS_CP = 1, 2, 4, 8, 16*/
	ConstNumerics TROOPS_CP = { 1,2,4,8,16 };

	/*RESOURCE_PRODUCTION = 5, 4, 3, 2, 1 */
	ConstNumerics RESOURCE_PRODUCTION = { 5,4,3,2,1 };


	/*TROOP_NAMES = Militia, Guards, Cavalry, Knights, Paladins*/
	StringArray TROOP_NAMES = {
		"Militia",
		"Guards",
		"Cavalry",
		"Knights",
		"Paladins"
	};

	/*RESOURCE_BUILDING = Farm, Lumber Mill, Quarry, Mine, Church*/
	StringArray RESOURCE_BUILDING_NAMES = {
		"Farm",
		"Lumber Mill",
		"Quarry",
		"Mine",
		"Church"
	};

	/*OTHER_BUILDING = Barracks, Infirmary, Library, Wall, Residences*/
	StringArray OTHER_BUILDING_NAMES = {
				"Barracks",
				"Infirmary",
				"Library",
				"Wall",
				"Residences"
	};

	/*RESOURCE = Food, Wood, Ore, Gold, Mana*/
	StringArray RESOURCE_NAMES = {
				"Food",
				"Wood",
				"Ore",
				"Gold",
				"Mana"
	};

	std::array<std::string, 9> COLORS_STRING = {
			"BLACK",
			"RED",
			"GREEN",
			"YELLOW",
			"BLUE",
			"MAGENTA",
			"CYAN",
			"WHITE",
			"RESET"
	};


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
	std::array<std::string, 11> PROMPTS_STRING = {
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
			"WHAT_REPORT" /*Add stuff for this*/
	};

	
	int continentSize = 0;
	int enemyDifficulty = 0;
	int CPUNum = 0;
	int turn = 0;
	int UNIT_AMOUNT_CV = UNIT_AMOUNT;
	int currentParticipantIndex = 0;
	int maxCommanders = 0;

	const int BARRACKS_PRODUCTION = 2;

	bool debuggingMode = true;

	/// //////////////////////////////////////////////////////End Variables///////////////////////////////////////////

	int CV::getStringIndex(std::string arg) {
		//For debugging
		CV::debugFunction("CV, getStringIndex");

		for (int x = 0; x < (signed)PROMPTS_STRING.size(); x++) {
			if (PROMPTS_STRING[x] == arg) {
				return x;
			}
		}
		//Error case
		return -1;
	}


	void CV::printPerson() {
		//For debugging
		CV::debugFunction("CV, printPerson");

		std::cout << "Hello!";
	}
	void CV::addColor(COLORS c) {
		//For debugging
		CV::debugFunction("CV, addColor");


		/*The color definition is a series of numbers, separated by semicolons. In order to make the text color red (number 31), you can write "\033[31m" which will make any following output red. If you want yellow text (33) on blue background (44), you write "\033[31;44m". To reset everything back to the default colors, you write "\033[0m".

		foreground background
		black        30         40
		red          31         41
		green        32         42
		yellow       33         43
		blue         34         44
		magenta      35         45
		cyan         36         46
		white        37         47*/

		switch (c) {
			case BLACK:
				std::cout << "\033[30m";
				break;
			case RED:
				std::cout << "\033[31m";
				break;
			case GREEN:
				std::cout << "\033[32m";
				break;
			case YELLOW:
				std::cout << "\033[33m";
				break;
			case BLUE:
				std::cout << "\033[34m";
				break;
			case MAGENTA:
				std::cout << "\033[35m";
				break;
			case CYAN:
				std::cout << "\033[36m";
				break;
			case WHITE:
				std::cout << "\033[37m";
				break;
			case RESET:
				std::cout << "\033[0m";
				break;
		}


	}

	std::string CV::promptsToString(PROMPTS p) {
		//For debugging
		CV::debugFunction("CV, promptsToString");

		return PROMPTS_STRING[p];
	}
	//Generates a random name by randomly selecting consonants and vowels
	std::string CV::createRandomName() {
		//For debugging
		debugFunction("OF, createRandomName");

		std::string name = "";
		std::string consonants = "bcdfghjklmnpqrstvwxyz";
		std::string vowels = "aeiou";

		char newCharacter = ' ';
		for (int x = 0; x < 6; x++) {
			if (x % 2 == 0) // if even
			{
				newCharacter = consonants.at(rand() % 21);
			} else if (x % 2 == 1) // if odd
			{
				newCharacter = vowels.at(rand() % 5);
			}
			if (x == 0) {
				newCharacter = toupper(newCharacter);
			}
			name += newCharacter;
		}
		return name;
	}
	

	CV::PROMPTS CV::stringToPrompts(std::string arg) {
		//For debugging
		CV::debugFunction("CV, stringToPrompts");

		return PROMPTS(CV::getStringIndex(arg));
	}

	std::array<int, 5> CV::modifyArray(std::array<int, 5> primeArray, std::array<int, 5> secondaryArray, bool isAdd) {
		//For debugging
		debugFunction("OF, modifyArray");

		if (isAdd)
			for (int& x : primeArray)
				x += secondaryArray[x];
		else
			for (int& x : primeArray)
				x -= secondaryArray[x];
		return primeArray;
	}

	CV::myvector<int>::myvector(std::vector<int> vectorArg) {
		vector(vectorArg.begin(), vectorArg.end());
	}
	void CV::myvector<int>::addVectorElements(CV::myvector<int> vectorInstance) {
		for (int x = 0; x < this->size(); x++) {
			at(x) += vectorInstance.at(x);
		}
	}

	void CV::myarray<std::array<int,5>>::createArray(std::array<int, 5> arrayArg) {
		for (int x = 0; x < 5; x++) {
			this->at(x) = arrayArg.at(x);
		}
	}

	void CV::myarray<std::array<int,5>>::addArrayElements(CV::myarray<std::array<int,5>> arrayArg) {
		for (int x = 0; x < 5; x++) {
			at(x) += arrayArg[x];
		}
	}
}



//Clears the screen
void CV::clearScreen() {
	//For debugging
	debugFunction("OF, clearScreen");

	addColor(RED);
	std::cout << "Clearing screen. \n";
	addColor(RESET);

	std::chrono::seconds dura(1);
	std::this_thread::sleep_for(dura);
	clearScreenCommand();
}

void CV::clearScreenCommand() {
	std::cout << "\033[2J\033[1;1H";
}


//The user is prompted to enter anything.
void CV::enterAnything() {
	debugFunction("OtherFunctions, enterAnything");
	std::string emptyString = " ";
	std::cout << "Enter anything to return to the previous menu: \033[31m";
	getline(std::cin, emptyString);
	println("\n\033[0m")
}

/*functionName is styled as "file name, function name*/
void CV::debugFunction(std::string functionName) {
	if (debuggingMode == true)
		std::cout << "\033[35mFunction: " << functionName << "\033[0m\n";
}

/*
1 - selectEnemyAction
2 - playerUnitAction
3 - introduction
4 - playerAction
6 - TrainMAFunction
7 - playerBuildFunction
8 - viewPlayerMap
9 - selectPlayerProvince
10 - selectEnemyProvince
11 - scoutLogFunction
12 - upgradeBuildings
*/


//Returns that help prompt that correlates with the specified numerical identifier (caseNum)
void CV::showHelp(int caseNum) {
	//For debugging
	CV::debugFunction("OF, showHelp");

	std::string caseNumString = std::to_string(caseNum);

	std::fstream newfile;//create file
	newfile.open("Help.txt", std::ios::in);//open Help.txt file, we want to see inside of it
	if (newfile.is_open()) //if it successfully opens
	{
		std::string line;//Creates new line
		bool pause = false;
		while (std::getline(newfile, line)) {
			bool wait = false;

			if (line.substr(0, 3) == "case")
				pause = true;
			if (line == "case " + caseNumString) {
				pause = false;
				wait = true;
			}
			if (line == "End") {
				wait = true;
				pause = false;
			}

			if (pause == false && wait == false)
				std::cout << line;
		}
		newfile.close(); // close the file object.
	}
}

//Print a text file
void CV::printFile(std::string path) {
	//For debugging
	debugFunction("OF, printFile");

	//Create file
	std::fstream newfile;
	newfile.open(path, std::ios::in);

	if (!newfile.is_open()) {
		std::cout << "File cannot be opened...\n";
		return;
	}

	std::string line;
	//Iterate through file
	while (getline(newfile, line)) {
		//If this line is a special qualifier, do some specific text modifier
		if (line.substr(0, 1) == "!") {
			switch (line.at(1)) {
				case 'R':
					addColor(RED);
					break;
				case 'B':
					addColor(BLUE);
					break;
				case 'W':
					addColor(WHITE);
					break;
				case 'N':
					std::cout << std::endl;
					break;
			}
		} else {
			//print line as normal
			std::cout << line << std::endl;
		}

	}
	//close file
	newfile.close();
	return;
}
