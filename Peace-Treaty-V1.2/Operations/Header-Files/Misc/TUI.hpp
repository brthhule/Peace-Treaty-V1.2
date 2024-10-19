#ifndef TUI_HPP
#define TUI_HPP
#include <string.h>
#include <iostream>
#include <vector>

// Singleton, participants have pointer to TUI/Input?
class TUI {
	static enum TextType {
		TEXT, INPUT
	};

	static void printBar();
	static void printDottedHorizontal();
	static void printMapXAxis();
	static void setPrimeCoordinates(std::pair<int, int> coords);
	static void printLeftSide(int row);
	static void printRightSide(int row);
	static void printLine(int row);
	static void printScreen();
	static void initialize();
	static void addOutputArg(std::string arg, TextType type);
	static void resetArg(TextType type);


	static int rows;
	static int mapCols;
	static int cols;
	static int indentNum;

	static std::string indent;

	static int zoom;
	static int cellWidth;
	static int cellHeight;

	static int xAxisIndex;
	static int yAxisIndex;
	static std::pair<int, int> primeCoords;
	static std::vector <std::string>* inputArgs;
	static std::vector<std::string>* textArgs;

private:
	
};
#endif