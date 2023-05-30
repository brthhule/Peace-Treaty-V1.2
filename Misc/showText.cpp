#include "showText.h"
#define RED "\033[31m"
#define WHITE "\033[0m"
#define BLUE "\033[;34m"

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

std::vector<std::string> showOptions(int caseNum)
{
	std::string caseNumString = std::to_string(caseNum);
	std::fstream newfile;
	newfile.open("MA/Options.txt", std::ios::in); // open a file to perform read operation using file object
	std::vector<std::string> acceptableValues = {"H"};
	
  if (newfile.is_open()) 
	{
		std::string line;
		bool pause = false;
		bool addToArray = false;
    while (getline(newfile, line)) 
		{
			bool wait = false;
			
			if (line.substr(0,4) == "case")
				pause = true;
			if (line.substr(0,6) == "case " + caseNumString || line == "start")
			{
				pause = false;
				wait = true;
				addToArray = false;
			}
			if (line == "End")
			{
				wait = true;
				pause = true;
			}
			if (line == "Options:")
			{
				addToArray = true;
				wait = true;
			}

			// std::cout << "Pause: " << pause << std::endl;
			// std::cout << "Wait: "  << wait << std::endl;

			if (line.substr(0,1) != "!")
			{
				if (pause == false && wait == false)
				{
					if (addToArray == false)
						std::cout << line << std::endl;
					else if (addToArray == true)
						acceptableValues.push_back(line);
				}
					
			}
			else
			{
				if (line.substr(1) == "RED")
					std::cout << RED;
				else if (line.substr(1) == "BLUE")
					std::cout << BLUE;
				else if (line.substr(1) == "WHITE")
					std::cout << WHITE;
				else if (line.substr(1) == "NEWLINE")
						std::cout << std::endl;
			}
		}
    newfile.close(); // close the file object.
  }
	// std::cout << "AV: \n";
	// for (std::string newString: acceptableValues)
	// 	std::cout << newString << std::endl;
	return acceptableValues;
}

void printOptions (std::string tp, int &type, bool &skip, std::vector<std::string> &acceptableValues)
{
	if (tp == "List of Options:")
		type = 1;
	else if (tp == "Options:")
	{
		type = 2;
		skip = true;
	}
	else if (tp == "End Options")
	{
		skip = true;
		type = 3;
	}

	switch (type)
	{
	case 1:
		std::cout << tp << std::endl;
		break;
	case 2:
		if (skip == true)
		{
			//Do nothing
			skip = false;
		}
		else
			acceptableValues.push_back(tp);
		break;
	case 3:
		if (skip == true)
			skip = false;
		else
			std::cout << tp << " ";
		break;
	}	
}

//Returns that help prompt that correlates with the specified numerical identifier (caseNum)
void showHelp (int caseNum)
{
	std::string caseNumString = std::to_string(caseNum);

	std::fstream newfile;//create file
	newfile.open("Help.txt", std::ios::in);//open Help.txt file, we want to see inside of it
	if (newfile.is_open()) //if it successfully opens
	{
		std::string line;//Creates new line
		bool pause = false;
		while (getline(newfile, line)) 
		{
			bool wait = false;

			if (line.substr(0,3) == "case")
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

void printFile (std::string fileName)
{
	std::cout << "Debug... printFile opened\n";
	
	std::fstream newfile;//create file
	newfile.open(fileName, std::ios::in);//Open file
	if (newfile.is_open())//If the file opens successfully
	{
		std::cout << "File" + fileName + " is open...\n";//Confirmation
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
char getOption (int caseNum)
{
	OtherFunctions OF;
	return OF.getInput ("showOptions" + std::to_string(caseNum), {}, false, false).at(0);
	/*
	In order:
	- showOptions indicates that the options must be printed out, taken from the Options.txt file
	- caseNum indicates the options prompt that must be printed
	- Empty brackets indicate that the acceptable values are unknown at this point and must be found from the Options.txt file
	- third parameter, false, indicates that we want to get a char/letter value in return, not a number
	- the fourth parameter, false, indcates that getInput will be run initially from this call; it is not being reiterated at this point*/
}

// void scoutLogFunction ()
// {
// //case ll
// 	std::string SLFReports[3] = Options:garrisonresourcebuilding
//     for (int x = 0; x < 3; x++) {
//   - View the  << SLFReports <<  report for this province ( << toupper(SLFReports[x].at(0)) << )\n;
  
// Options:GRB
// }

