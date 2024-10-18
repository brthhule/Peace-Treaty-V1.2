#ifndef TUI_HPP
#define TUI_HPP
#include <string.h>
#include <iostream>

using namespace std;
class TUI {
public:
	TUI();
	static void printScreen();
	// Print screen out
	static void initialize();
	static void printBar();
	static void printDottedHorizontal();
	static void printMapXAxis();

	static void printLeftSide(int row);
	static void printRightSide(int row);
	static void printLine(int row);

	// Uses user coords
	static void setPrimeCoordinates(std::pair<int, int> coords);

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
	static pair<int, int> primeCoords; 
private:
	
};
#endif