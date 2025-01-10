#include "..\..\..\Support\Paths.h"
#include LOG_HEADER

const bool LOG::debuggingMode = true; 
int LOG::stack_frame = 0;

//For stand alone color integration
void LOG::addColor(Colors color) {
	std::cout << getColor(color); 
}

//For integration with strings/std::cout statements
string LOG::getColor(Colors color) {
	std::array<string, 9> sequences = {
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

void LOG::PRINT(string message, Colors color) {
	std::cout << getColor(color) << message << getColor(RESET);
}

void LOG::PRINT(string message) {
	PRINT(message, RESET); 
}

void LOG::DEBUG(string message) {
	if (debuggingMode) { 
		std::cout << "DEBUG " << stack_frame;
		for (int i = 0; i < LOG::stack_frame; i++) {
			std::cout << "+";
		}
		PRINT(message, MAGENTA); 
	}
}

void LOG::DEBUG(string file, string function) { 
	LOG::DEBUG(file + ", " + function);
}

void LOG::DEBUG_LN(string message) {
	LOG::DEBUG(message + "\n");
}


void LOG::SYSTEM(string message) {
	PRINT(message, GREEN);
}

void LOG::ERROR(string message) {
	PRINT(message, RED); 
}

string LOG::EMBED(string message, Colors color) {
	return getColor(color) + message + getColor(RESET);
}