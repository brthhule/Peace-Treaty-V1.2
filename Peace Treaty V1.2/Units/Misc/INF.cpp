#include "INF.h"

namespace INF {
	////////////////////////////////////////////////Start Variables///////////////////////////////////////
	/*Troops_COST = 5, 4, 3, 2, 1 */
	i5array Troops_COST = { 5, 4, 3, 2, 1 };

	/*INITIAL_VALUES = 5, 4, 3, 2, 1 */
	i5array INITIAL_VALUES = { 5, 4, 3, 2, 1 };

	/*Troops_CP = 1, 2, 4, 8, 16*/
	i5array Troops_CP = { 1,2,4,8,16 };

	/*RESOURCE_PRODUCTION = 5, 4, 3, 2, 1 */
	i5array RESOURCE_PRODUCTION = { 5,4,3,2,1 };


	/*TROOP_NAMES = Militia, Guards, Cavalry, Knights, Paladins*/
	s5array TROOP_NAMES = {
		"Militia",
		"Guards",
		"Cavalry",
		"Knights",
		"Paladins"
	};

	/*RESOURCE_BUILDING = Farm, Lumber Mill, Quarry, Mine, Church*/
	s5array RESOURCE_BUILDING_NAMES = {
		"Farm",
		"Lumber Mill",
		"Quarry",
		"Mine",
		"Church"
	};

	/*OTHER_BUILDING = Barracks, Infirmary, Library, Wall, Residences*/
	s5array OTHER_BUILDING_NAMES = {
				"Barracks",
				"Infirmary",
				"Library",
				"Wall",
				"Residences"
	};

	/*RESOURCE = Food, Wood, Ore, Gold, Mana*/
	s5array RESOURCE_NAMES = {
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
			"WHAT_REPORT" /*Add stuff for this*/,
			"BATTLE_FORMATION" /*May not be used*/
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

	//////////////////////////////////////End Variables////////////////////////

	int INF::getStringIndex(std::string arg) {
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


	void INF::addColor(COLORS c) {
		//For debugging
		INF::debugFunction("CV, addColor");


		/*The color definition is a series of numbers, separated by semicolons.
		In order to make the text color red (number 31), you can write 
		"\033[31m" which will make any following output red. If you want yellow
		text (33) on blue background (44), you write "\033[31;44m". To reset 
		everything back to the default colors, you write "\033[0m".

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

	std::string INF::getColor(COLORS color) {
		std::array<std::string, 9> sequences = {
			"\033[30m", //Black
			"\033[31m", //Red
			"\033[32m", //Green
			"\033[33m", //Yellow
			"\033[34m", //Blue
			"\033[35m", //Magenta
			"\033[36m", //Cyan
			"\033[37m", //White
			"\033[0m" //Reset
		};

		return sequences[color];
	}

	std::string INF::promptsToString(Prompts p) {
		//For debugging
		INF::debugFunction("CV, promptsToString");

		return PROMPTS_STRING[p];
	}
	//Generates a random name by randomly selecting consonants and vowels
	std::string INF::createRandomName() {
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
	

	INF::Prompts INF::stringToPrompts(std::string arg) {
		//For debugging
		INF::debugFunction("CV, stringToPrompts");

		return PROMPTS(INF::getStringIndex(arg));
	}

	std::array<int, 5> INF::modifyArray(i5array primeArray, 
										i5array secondaryArray, 
										bool isAdd) {
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

	INF::myvector<int>::myvector(std::vector<int> vectorArg) {
		vector(vectorArg.begin(), vectorArg.end());
	}
	void INF::myvectorI::addVectorElements(INF::myvectorI vectorInstance) {
		for (int x = 0; x < (int) this->size(); x++) {
			at(x) += vectorInstance.at(x);
		}
	}

	void INF::myarray<i5array>::createArray(i5array arrayArg) {
		for (int x = 0; x < 5; x++) {
			this->at(x) = arrayArg.at(x);
		}
	}

	void INF::myarrayI5A::addArrayElements(INF::myarrayI5A arrayArg) {
		for (int x = 0; x < 5; x++) {
			at(x) += arrayArg[x];
		}
	}
};



//Clears the screen
void INF::clearScreen() {
	//For debugging
	debugFunction("OF, clearScreen");

	addColor(RED);
	std::cout << "Clearing screen. \n";
	addColor(RESET);

	std::chrono::seconds dura(1);
	std::this_thread::sleep_for(dura);
	clearScreenCommand();
}

void INF::clearScreenCommand() {
	//For debugging
	debugFunction("OF, clearScreenCommand");
	std::cout << "\033[2J\033[1;1H";
}


/*The user is prompeted to enter anything
option = 1, says enter anything to proceed
option = 2, says enter anything to return to previous menu*/
void INF::enterAnything(int option) {
	std::string line;
	switch (option) {
		case 1:
			line = "proceed";
			break;
		case 2:
			line = "return to the previous menu";
			break;
	}
	debugFunction("OtherFunctions, enterAnything");
	std::string emptyString = " ";
	std::cout << "Enter anything to " << line +
		" (screen will clear): " << INF::getColor(BLUE);
	getline(std::cin, emptyString);
	INF::addColor(BLUE);
}

/*functionName is styled as "file name, function name*/
void INF::debugFunction(std::string functionName) {
	if (debuggingMode == true) {
		std::cout << "\033[35mFunction: " << functionName << "\033[0m\n";
	}
		
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


/*Returns help prompt that correlates with the specified numerical 
identifier(caseNum)*/
void INF::showHelp(int caseNum) {
	//For debugging
	INF::debugFunction("OF, showHelp");

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
void INF::printFile(std::string path) {
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
