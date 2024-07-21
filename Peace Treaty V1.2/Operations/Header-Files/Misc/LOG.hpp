//First level

#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <array>

using std::string;

class LOG {
public:
	/*BLACK = 0, RED, GREEN, YELLOW, LOG::BLUE, MAGENTA = 5, CYAN, WHITE, RESET*/
	static enum Colors {
		BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET
	};

	static void PRINT(string message, Colors color);
	static void PRINT(string message);

	static string EMBED(string message, Colors color);

	//Always red
	static void ERROR(string message);
	static void DEBUG(string message);
	static void SYSTEM(string message);

	static void addColor(Colors c);
	static string getColor(Colors color);

private:
	/*"BLACK", "RED", "GREEN", "YELLOW", "LOG::BLUE", "MAGENTA", "CYAN", "WHITE",
		"RESET" */
	const std::array<std::string, 9> COLORS_STRING = { 
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

	//Get command to print certain color to console
	
	//Adds color to console
	
	static const bool debuggingMode = false; 
};
#endif