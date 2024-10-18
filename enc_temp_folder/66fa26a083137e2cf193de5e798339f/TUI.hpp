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
private:
	
};
#endif