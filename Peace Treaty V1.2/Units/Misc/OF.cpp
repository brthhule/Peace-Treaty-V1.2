#include "OF.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;



//Generates a random name by randomly selecting consonants and vowels
std::string OF::createRandomName() {
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

//Clears the screen
void OF::clearScreen() {
	//For debugging
	debugFunction("OF, clearScreen");

	std::cout << "\033[32mClearing screen. \n";
	std::cout << "\033[0m";
	std::chrono::seconds dura(1);
	std::this_thread::sleep_for(dura);
	system("clear"); /*Non-Windows*/
}

// std::vector<int> OF::modifyVector(std::vector<int> primeVector, std::vector<int> secondaryVector, bool isAdd)
// {
// 	debugFunction("OtherFunctions, modifyVector");
// 	if (isAdd)
// 		for (int &x: primeVector)
// 			x += secondaryVector[x];
// 	else
// 		for (int &x: primeVector)
// 			x -= secondaryVector[x];
// 	return primeVector;
// }

//Takes two arrays and a boolean expression. Adds the elemnts of the second array to the elements of the first array and returns the product.
std::array<int, 5> OF::modifyArray(std::array<int, 5> primeArray, std::array<int, 5> secondaryArray, bool isAdd) {
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

//The user is prompted to enter anything.
void OF::enterAnything() {
	debugFunction("OtherFunctions, enterAnything");
	std::string emptyString = " ";
	std::cout << "Enter anything to return to the previous menu: \033[31m";
	getline(std::cin, emptyString);
	println("\n\033[0m")
}

/*functionName is styled as "file name, function name*/
void OF::debugFunction(std::string functionName) {
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
void OF::showHelp(int caseNum) {
	//For debugging
	OF::debugFunction("OF, showHelp");

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
void OF::printFile(std::string filename) {
	//For debugging
	debugFunction("OF, printFile");

	//Create file
	std::fstream newfile;
	//Open file
	newfile.open(filename, std::ios::in);
	//If the file opens successfully
	if (newfile.is_open())
	{
		std::string line;
		while (getline(newfile, line)) //Iterate through file
		{
			if (line.substr(0, 1) == "!")//If this line is a special qualifier, do some specific text modifier
			{
				switch (line.at(1)) {
					case 'R':
						std::cout << RED;
						break;
					case 'B':
						std::cout << BLUE;
						break;
					case 'W':
						std::cout << WHITE;
						break;
					case 'N':
						std::cout << std::endl;
						break;
				}
			} else//print line as normal
			{
				std::cout << line << std::endl;
			}

		}
		newfile.close();//close file
	}
	std::cout << std::endl;//add space

}

//Gets an input from the user that pertains to choosing an option from one of the showOptions prompts




// void scoutLogFunction ()
// {
// //case ll
// 	std::string SLFReports[3] = Options:garrisonresourcebuilding
//     for (int x = 0; x < 3; x++) {
//   - View the  << SLFReports <<  report for this province ( << toupper(SLFReports[x].at(0)) << )\n;

// Options:GRB
// }


namespace OF {
	void OF::addColor(COLORS c) {
		//For debugging
		OF::debugFunction("CV, OtherBuildingsToString");


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

}