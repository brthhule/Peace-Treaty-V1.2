#ifndef TUI_HPP
#define TUI_HPP
#include <string.h>
#include <iostream>
#include <vector>
#include <array>

// Singleton, participants have pointer to TUI/Input?
class DebugFunctions {
public:
	DebugFunctions();
	std::string getFunction(int index);
	void addFunction(std::string);
	void resetStart();
	int modifyStartIndex(std::string input);
	std::array<std::string, 3> getFunctions();
private:
	std::vector<std::string> functions;
	int startIndex;
};

class TUI {
public:
	enum TextType {
		TEXT, INPUT
	};

	TUI();
	void printBar();
	void printDottedHorizontal();
	void printMapXAxis();
	void setPrimeCoordinates(std::pair<int, int> coords);
	void printLeftSide(int row);
	void printRightSide(int row);
	void printLine(int row);
	void printScreen();
	void initialize();
	void addOutputArg(std::string arg, TextType type);
	void resetArg(TextType type);

	static TUI tui;


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
	std::pair<int, int> primeCoords;
	std::vector <std::string> inputArgs;
	std::vector<std::string> textArgs;
	DebugFunctions debugFunctions;
	
};
#endif