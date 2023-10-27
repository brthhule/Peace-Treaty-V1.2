#include "../Peace Treaty V1.2/Misc/ConstValues.h"

using namespace CV;

void CV::addColor(COLORS c) {

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

void CV::printPerson() {
	std::cout << "Hello!";
}

std::string CV::promptsToString(PROMPTS p) {
	return PROMPTS_STRING[p];
}

int CV::getStringIndex(std::string arg) {
	for (int x = 0; x < PROMPTS_STRING.size(); x++) {
		if (PROMPTS_STRING[x] == arg) {
			return x;
		}
	}
	//Error case
	return -1;
}

CV::PROMPTS CV::stringToPrompts(std::string arg) {
	return PROMPTS(CV::getStringIndex(arg));
}
