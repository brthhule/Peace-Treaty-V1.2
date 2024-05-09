//First level

#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <array>

class LOG {
public:
	/*BLACK = 0, RED, GREEN, YELLOW, LOG::BLUE, MAGENTA = 5, CYAN, WHITE, RESET*/
	static enum Colors {
		BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET
	};

	static void PRINT(std::string message, Colors color);
	static void PRINT(std::string message);

	static std::string EMBED(std::string message, Colors color);

	//Always red
	static void ERROR(std::string message);
	static void DEBUG(std::string message);
	static void SYSTEM(std::string message);

	void addColor(Colors c);
private:
	/*"BLACK", "RED", "GREEN", "YELLOW", "LOG::BLUE", "MAGENTA", "CYAN", "WHITE",
		"RESET" */
	const std::array<std::string, 9> COLORS_STRING;  

	//Get command to print certain color to console
	std::string getColor(Colors color);
	//Adds color to console
	

	const bool debuggingMode = false;
};
#endif