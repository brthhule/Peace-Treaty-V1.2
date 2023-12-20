#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INF_HEADER

namespace INF {
	////////////////////////////////////////////////Start Variables///////////////////////////////////////
	

	/*INITIAL_VALUES = 5, 4, 3, 2, 1 */
	i5array INITIAL_VALUES = { 5, 4, 3, 2, 1 };

	

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

	template <typename T>
	Array5<T>::Array5(std::initializer_list<T> list) : items(list) {
	
	}
	
	template <typename T>
	T& Array5<T>::get(int index) {
		return items.at(index);
	}

	int continentSize = 0;
	int enemyDifficulty = 0;
	int CPUNum = 0;
	int turn = 0;
	int currentParticipantIndex = 0;

	bool debuggingMode = true;

	//////////////////////////////////////End Variables////////////////////////

	//For stand alone color integration
	void INF::addColor(COLORS color) {
		//For debugging
		DEBUG_FUNCTION("CV, addColor");
		std::cout << getColor(color);
		
	}

	//For integration with strings/std::cout statements
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

		return sequences.at(color);
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
			// if even
			if (x % 2 == 0) {
				newCharacter = consonants.at(rand() % 21);
			} else {
				// if odd
				newCharacter = vowels.at(rand() % 5);
			}

			name += newCharacter;
		}
		//Capitalize name
		name.at(0) = toupper(name.at(0));
		return name;
	}

	//Can change this-> look at concatVectors as a template-- use a pair of arrays instead of passing two arrays
	i5array INF::mutateArray(
		i5array primeArray, 
		constArrayReference secondaryArray,
		MutateDirection direction) 
	{
		//For debugging
		debugFunction("OF, mutateArray");

		switch (direction) {
			case INCREASE:
				for (int index = 0; index < 5; index++) {
					primeArray.at(index) += secondaryArray.at(index);
				}
				break;
			case DECREASE:
			default:
				for (int index = 0; index < 5; index++) {
					primeArray.at(index) -= secondaryArray.at(index);
				}
				break;
		}
			
		return primeArray;
	}

	INF::myvector<int>::myvector(std::vector<int> vectorArg) {
		vector(vectorArg.begin(), vectorArg.end());
	}
	void INF::myvector<int>::addVectorElements(INF::myvector<int> vectorInstance) {
		for (int x = 0; x < (int) this->size(); x++) {
			at(x) += vectorInstance.at(x);
		}
	}

	void INF::myarray<i5array>::createArray(i5array arrayArg) {
		for (int x = 0; x < 5; x++) {
			this->at(x) = arrayArg.at(x);
		}
	}

	void INF::myarray<i5array>::addArrayElements(INF::myarray<i5array> arrayArg) {
		for (int x = 0; x < 5; x++) {
			at(x) += arrayArg[x];
		}
	}
};

bool INF::checkIsNumber(std::string numberString) {
	std::string AV = "0123456789";
	for (char letter : numberString) {
		if (AV.find(letter) == std::string::npos) {
			return false;
		}
	}
	return true;
}

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
	debugFunction("OtherFunctions, enterAnything");
	std::array<std::string, 2> phrases = { "proceed", "return to the previous menu" }; 
	std::string line = phrases.at(option - 1);

	std::cout << "Enter anything to " << line +
		" (screen will clear): " << INF::getColor(BLUE);
	std::string emptyString = " "; 
	getline(std::cin, emptyString);
	INF::addColor(BLUE);
}

/*functionName is styled as "file name, function name*/
void DEBUG_FUNCTION(std::string functionName) {
	if (debuggingMode == true) {
		std::cout << "\033[35mFunction: " << functionName << "\033[0m\n";
	}
}

/*Returns help prompt that correlates with the specified numerical 
identifier(caseNum)*/
void INF::showHelp(int caseNum) {
	//For debugging
	DEBUG_FUNCTION("OF, showHelp");

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


template <typename T>
//Takes a list of vectors, concatentate them together. List goes in order of earliest to latest index
std::vector<T> INF::concatVectors(std::vector<std::vector<T>> vectorsList) {
	std::vector<T> baseList = vectorsList.at(0);

	for (int list = 1; list < vectorsList.size(); list++) {
		std::vector<T> currentList = vectorsList.at(list);
		for (int currentElement = 0; currentElement < currentList.size(); currentElement++) {
			baseList.push_back(currentList.at(currentElement));
		}
	}

	return baseList;
}

void INF::printResources(constArrayReference resourcesArray) {
	//For debugging
	DEBUG_FUNCTION("PrimeUnits, printResources");

	for (int x = 0; x < 5; x++) {
		std::cout << "- " << INF::RESOURCE_NAMES.at(x) << ": " << resourcesArray.at(x) << std::endl;
	}

	std::cout << std::endl;
}

void INF::enterAndClear(int option) {
	enterAnything(option);
	clearScreen();
}

