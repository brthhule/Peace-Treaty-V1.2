#include "..\..\..\Support\Paths.h"

#include INF_HEADER

////////////////////////////////////////////////Start Variables///////////////////////////////////////
	
/*template <typename T>
const T& makeConst(T& object) {
	return object;
}

template<typename T>
T makeCopy(T& object) {
	return T(object);
}*/

/*INITIAL_VALUES = 5, 4, 3, 2, 1 */
INF::i5array INF::INITIAL_VALUES = { 5, 4, 3, 2, 1 };

/*
template <typename T>
Array5<T>::Array5(std::initializer_list<T> list) : items(list) {
	
}
	
template <typename T>
T& Array5<T>::at(int index) {
	return items.at(index);
}*/


int INF::continentSize = 0; 
int INF::enemyDifficulty = 0;
int INF::CPUNum = 0;
int INF::turn = 0;
int INF::currentParticipantIndex = 0;

//////////////////////////////////////End Variables////////////////////////



//Generates a random name by randomly selecting consonants and vowels
std::string INF::createRandomName() {
	//For debugging
	DEBUG_FUNCTION("INF.cpp", "createRandomName(void)");

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
INF::i5array INF::mutateArray(
	i5array primeArray, 
	constArrayRef secondaryArray,
	MutateDirection direction) 
{
	//For debugging
	DEBUG_FUNCTION("INF.cpp", "mutateArray(i5array, constArrayRef, MutateDirection)");

	int modifier = 1;
	if (direction == DECREASE) { modifier = -1; }

	for (int index = 0; index < 5; index++) {
		primeArray.at(index) += secondaryArray.at(index) * modifier;
	}

	return primeArray;
}

INF::myvector<int>::myvector(std::vector<int> vectorArg) { 
	//vector(vectorArg.begin(), vectorArg.end());
}
void INF::myvector<int>::addVectorElements(myvector<int> vectorInstance) { 
	for (int x = 0; x < (int) this->size(); x++) {
		at(x) += vectorInstance.at(x);
	}
}

void INF::myarray<INF::i5array>::createArray(i5array arrayArg) {
	for (int x = 0; x < 5; x++) {
		this->at(x) = arrayArg.at(x);
	}
}

void INF::myarray<INF::i5array>::addArrayElements(myarray<i5array> arrayArg) {
	for (int x = 0; x < 5; x++) {
		at(x) += arrayArg[x];
	}
}

/*RESOURCE = Food, Wood, Ore, Gold, Mana*/
INF::s5array INF::RESOURCE_NAMES = { 
	"Food",
	"Wood",
	"Ore",
	"Gold",
	"Mana"
};

bool INF::checkIsNumber(std::string numberString) {
	DEBUG_FUNCTION("INF.cpp", "checkIsNumber(std::string)")
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
	DEBUG_FUNCTION("INF.cpp", "clearScreen(void)");

	LOG::PRINT("Clearing screen.\n", LOG::RED); 

	std::chrono::seconds dura(1);
	std::this_thread::sleep_for(dura);
	clearScreenCommand();
}

void INF::clearScreenCommand() {
	//For debugging
	DEBUG_FUNCTION("INF.cpp", "clearScreenCommand(void)");
	std::cout << "\033[2J\033[1;1H";
}

std::string INF::getText(std::string target) {
	DEBUG_FUNCTION("INF.cpp", "getText");
	std::string filename = "C:/Users/Brennen/Source/Repos/brthhule/Peace-Treaty- V1.2/Peace Treaty V1.2/Support/TxtFiles/Text.txt";

	std::ifstream file(filename);

	if (!file.is_open()) {
		LOG::ERROR("Could not open file\n");
	}
	std::string str, text;
	while (std::getline(file, str)) {
		if (str.find(target) != -1) {
			text = str.substr(target.find(" "));
			break;
		}
	}

	if (text.find("BREAK") == -1) {
		return text;
	}

	std::string returnText = "";
	while (text.find("BREAK") != -1) {
		int point = (int)text.find("BREAK");
		returnText += text.substr(0, point) + "\n";
		text = text.substr(point);
		//Can't have BREAK at the end (will break everything)
		text = text.substr(text.find("K") + 1);
	}
	return returnText;
}

/*The user is prompeted to enter anything
option = 1, says enter anything to proceed
option = 2, says enter anything to return to previous menu*/
void INF::enterAnything(int option) {
	DEBUG_FUNCTION("INF.cpp", "enterAnything(int)");
	LOG::SYSTEM("Enter anything to proceed (screen will clear): ");
	LOG::addColor(LOG::BLUE);
	std::cin.get(); 

}

/*Returns help prompt that correlates with the specified numerical
identifier(caseNum)*/
void INF::showHelp(int caseNum) {
	//For debugging
	DEBUG_FUNCTION("INF.cpp", "showHelp(int)");

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
	DEBUG_FUNCTION("INF.cpp", "printFile(std::string)");
	Tui::debug("INF, printFile");  

	//Create file
	std::fstream newfile;
	newfile.open(path, std::ios::in);

	if (!newfile.is_open()) {
		LOG::ERROR("File cannot be opened\n");
		return;
	}

	std::string line;
	//Iterate through file
	while (getline(newfile, line)) {
		//If this line is a special qualifier, do some specific text modifier
		if (line.substr(0, 1) == "!") {
			switch (line.at(1)) {
				case 'R':
					LOG::addColor(LOG::RED);
					break;
				case 'B':
					LOG::addColor(LOG::BLUE);
					break;
				case 'W':
					LOG::addColor(LOG::WHITE);
					break;
				case 'G':
					LOG::addColor(LOG::GREEN);
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

std::string INF::str(int arg) {
	return std::to_string(arg); 
}

template <typename T>
//Takes a list of vectors, concatentate them together. List goes in order of earliest to latest index
std::vector<T> INF::concatVectors(std::vector<std::vector<T>> vectorsList) {
	DEBUG_FUNCTION("INF.cpp", "concatVectors(std::vector<std::vector<T>>)")
	std::vector<T> baseList = vectorsList.at(0); 

	for (int list = 1; list < vectorsList.size(); list++) {
		std::vector<T> currentList = vectorsList.at(list);
		for (int currentElement = 0; currentElement < currentList.size(); currentElement++) {
			baseList.push_back(currentList.at(currentElement));
		}
	}

	return baseList;
}

void INF::printResources(constArrayRef resourcesArray) {
	//For debugging
	DEBUG_FUNCTION("INF.cpp", "printResources(constArrayRef)");

	for (int x = 0; x < 5; x++) {
		std::cout << "- " << RESOURCE_NAMES.at(x) << ": " << resourcesArray.at(x) << std::endl;
	}

	std::cout << std::endl;
}

void INF::enterAndClear(int option) {
	DEBUG_FUNCTION("INF.cpp", "enterAndClear(int)")
	enterAnything(option);
	clearScreen();
}


/*void LOG::FILE_METHOD(std::string file, std::string method) {
#define DEBUGGING_MODE 
#ifndef DEBUGGING_MODE 
	return;
#else
	std::cout << getColor(MAGENTA)
#endif
}*/