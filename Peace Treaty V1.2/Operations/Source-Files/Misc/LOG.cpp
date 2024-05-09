#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include LOG_HEADER

const std::array<std::string, 9> LOG::COLORS_STRING = {
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

//For stand alone color integration
void LOG::addColor(Colors color) {
	//For debugging
	

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
	std::cout << addColor(color) << message << addColor(RESET);  
}

void LOG::PRINT(std::string message) {
	PRINT(message, RESET); 
}

void LOG::DEBUG(std::string message) {
	PRINT(message, MAGENTA); 
}

void LOG::SYSTEM(std::string message) {
	PRINT(message, GREEN);
}

void LOG::ERROR(std::string message) {
	PRINT(message, RED); 
}

static std::string LOG::EMBED(std::string message, Colors color) {
	return addColor(color) + message + addColor(RESET); 
}