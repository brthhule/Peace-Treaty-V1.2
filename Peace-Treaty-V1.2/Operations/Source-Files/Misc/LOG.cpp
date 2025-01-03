#include "..\..\..\Support\Paths.h"
#include LOG_HEADER



//For stand alone color integration
void LOG::addColor(Colors color) {
	std::cout << getColor(color); 
}

//For integration with strings/std::cout statements
std::string LOG::getColor(Colors color) {
	std::array<std::string, 9> sequences = {
		"\033[30m", //Black
		"\033[31m", //Red
		"\033[32m", //Green
		"\033[33m", //Yellow
		"\033[34m", //LOG::BLUE
		"\033[35m", //Magenta
		"\033[36m", //Cyan
		"\033[37m", //White
		"\033[0m" //Reset
	};

	return sequences.at(color);
}

void LOG::PRINT(std::string message, Colors color) {
	std::cout << getColor(color) << message << getColor(RESET);
}

void LOG::PRINT(std::string message) {
	PRINT(message, RESET); 
}

void LOG::DEBUG(std::string message) {
	if (debuggingMode) { PRINT(message, MAGENTA); }
}

void LOG::DEBUG(string file, string function) {
	LOG::DEBUG(file + ", " + function);
}


void LOG::SYSTEM(std::string message) {
	PRINT(message, GREEN);
}

void LOG::ERROR(std::string message) {
	PRINT(message, RED); 
}

std::string LOG::EMBED(std::string message, Colors color) {
	return getColor(color) + message + getColor(RESET);
}