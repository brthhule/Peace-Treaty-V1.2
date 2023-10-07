#include "OtherFunctions.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
#define RED "\033[31m"
#define WHITE "\033[0m"
#define BLUE "\033[;34m"

OtherFunctions::OtherFunctions() {}

//Gets user input and returns a valid response. Parameters: (string text, vector<string> acceptable values, bool isNumber, bool redo)
std::string OtherFunctions::getInput(bool isSO/*is showOptions*/, int caseNumArg, std::string text, std::vector<std::string> AV, bool isNumber, bool redo)
{

	//bool redo is to keep track of whether the function has been recursed or not
	debugFunction("OtherFunctions, getInput");

	std::string input;

	//If first time running through getInput
	if (redo == false)
	{
		//std::cout << "String: " << text.substr(0,10) << std::endl;
		if (isSO)
		{
			int caseNum = caseNumArg;
			std::cout << "CaseNum: " << caseNum << std::endl;
			AV = showOptions(caseNum);
			isNumber = false;//want a letter option
			std::cout << "Enter an option: ";
		}
		else
		{
			std::cout << text;
		}
		
		std::cout << "\033[31m";
		std::getline(std::cin, input);
		std::cout << "\033[0m";
	} 
	else if (redo == true)
	{
		std::cout << std::endl;
		std::cout << "Invalid character entered. Please try again. \nPlease enter a valid character: \033[31m";
		std::getline(std::cin, input);
		std::cout << "\033[0m";
	}

  if (input.length() == 1 && isNumber == false)
	{
		char letter = toupper(input.at(0));
		input.clear();
		input.push_back(letter);
	}


  // if (AV[0] != "number")
  	for (std::string option: AV)
  		if (input == option)
  			return input;
  // else
  //   for (int number: AVInt)
  //     if (number == inputInt)
  //       return std::to_string(inputInt);
	
  return getInput(false, -1, text, AV, isNumber, true);
  
}

std::string OtherFunctions::createRandomName() {
	debugFunction("OtherFunctions, createRandomName");
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

void OtherFunctions::clearScreen() 
{
	debugFunction("OtherFunctions, clearScreen");
	std::cout << "\033[32mClearing screen. \n";
	std::cout << "\033[0m";
	std::chrono::seconds dura(1);
	std::this_thread::sleep_for(dura);
	system("clear"); /*Non-Windows*/
}

int OtherFunctions::translateCoordinate(int coordinate, char indicator, char whichWay) 
{
	debugFunction("OtherFunctions, translateCoordinate");
  /*replacement = xCoordinate;
  xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
  yCoordinate = translateCoordinate (replacement, 'x', 'I');*/
  int translation = 0;
  switch (whichWay) {
  case 'I':
    return translateCoordinateInput(coordinate, indicator);
    break;
  case 'O':
    return translateCoordinateOutput(coordinate, indicator);
    break;
  }
  //Error case
  return 0;
}

int OtherFunctions::translateCoordinateInput(int coordinate, char indicator) 
{
	debugFunction("OtherFunctions, translateCoordinateInput");
  switch (indicator) {
  case 'x':
    return coordinate - 1;
    break;
  case 'y':
    return abs(coordinate - continentSize);
    break;
  }
  return NULL;
}

int OtherFunctions::translateCoordinateOutput(int coordinate, char indicator) 
{
debugFunction("OtherFunctions, translateCoordinateOutput");
  switch (indicator) {
  case 'x':
    return coordinate + 1;
    break;
  case 'y':
    return abs(continentSize - coordinate);
    break;
  }
  return NULL;
}

std::string OtherFunctions::printCoordinates(std::array<int, 2> coordinates)
{
	debugFunction("OtherFunctions, printCoordinates");
  //std::string x = std::to_string(translateCoordinate(coordinates[0], 'x', 'O'));
  //std::string y = std::to_string(translateCoordinate(coordinates[1], 'y', 'O'));
	std::string x = std::to_string(coordinates[0] + 1);
	std::string y = std::to_string(coordinates[1]);
	std::string coordinatesString = "(" + x + ", " + y + ") ";
	return coordinatesString;
}

// std::vector<int> OtherFunctions::modifyVector(std::vector<int> primeVector, std::vector<int> secondaryVector, bool isAdd)
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

std::array<int, 5> OtherFunctions::modifyArray(std::array<int, 5> primeArray, std::array<int, 5> secondaryArray, bool isAdd)
{
	debugFunction("OtherFunctions, modifyArray");
	if (isAdd)
		for (int &x: primeArray)
			x += secondaryArray[x];
	else
		for (int &x: primeArray)
			x -= secondaryArray[x];
	return primeArray;
}

void OtherFunctions::printResources(std::array<int, 5> resourcesArray)
{
	debugFunction("OtherFunctions, printResources");
	for (int x = 0; x < 5; x++)
		std::cout << "- " << CV::RESOURCE_NAMES[x] << ": " << resourcesArray[x] <<  std::endl;
	
	std::cout <<  std::endl;
}

void OtherFunctions::enterAnything()
{
	debugFunction("OtherFunctions, enterAnything");
	std::string emptyString = " ";
	std::cout << "Enter anything to return to the previous menu: \033[31m";
	getline(std::cin, emptyString);
	println("\n\033[0m")
}

int OtherFunctions::translateCoordinateToLL (int x, int y)
{
	debugFunction("OtherFunctions, translateCoordinateToLL");
	int LLNumber = 0;
	LLNumber = 25 - (5*y) + x;
	return LLNumber;
}

void OtherFunctions::debugFunction(std::string functionName)
{
	/*functionName is styled as "file name, function name*/
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
void OtherFunctions::showHelp(int caseNum)
{
	std::string caseNumString = std::to_string(caseNum);

	std::fstream newfile;//create file
	newfile.open("Help.txt", std::ios::in);//open Help.txt file, we want to see inside of it
	if (newfile.is_open()) //if it successfully opens
	{
		std::string line;//Creates new line
		bool pause = false;
		while (std::getline(newfile, line))
		{
			bool wait = false;

			if (line.substr(0, 3) == "case")
				pause = true;
			if (line == "case " + caseNumString)
			{
				pause = false;
				wait = true;
			}
			if (line == "End")
			{
				wait = true;
				pause = false;
			}

			if (pause == false && wait == false)
				std::cout << line;
		}
		newfile.close(); // close the file object.
	}
}

void OtherFunctions::printFile(std::string filename)
{
	debugFunction("showText, printFile");
	std::cout << "File name: " << filename << std::endl;
	std::fstream newfile;//create file
	newfile.open(filename, std::ios::in);//Open file
	if (newfile.is_open())//If the file opens successfully
	{
		std::string line;
		while (getline(newfile, line)) //Iterate through file
		{
			if (line.substr(0, 1) == "!")//If this line is a special qualifier, do some specific text modifier
			{
				switch (line.at(1))
				{
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
			}
			else//print line as normal
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

bool OtherFunctions::debuggingMode = true;