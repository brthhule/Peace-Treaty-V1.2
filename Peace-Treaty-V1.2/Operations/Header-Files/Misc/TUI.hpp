#ifndef TUI_HPP
#define TUI_HPP
#include <string.h>
#include <iostream>
#include <vector>

// Singleton, participants have pointer to TUI/Input?
class TUI {
public:
	TUI();
	void printScreen();
	// Print screen out
	void initialize();
	void printBar();
	void printDottedHorizontal();
	void printMapXAxis();

	static enum TextType {
		INPUT = 0, TEXT = 1
	};
	void addOutputArg(std::string arg, TextType type);

	
private:
	int rows;
	int mapCols;
	int cols;
	int indentNum;

	std::string indent;

	int zoom;
	int cellWidth;
	int cellHeight;

	int xAxisIndex;
	int yAxisIndex;
	std::vector <std::string> inputArgs;
	std::vector<std::string> textArgs;
};
#endif