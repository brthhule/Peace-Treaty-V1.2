#ifndef Tui_HPP
#define Tui_HPP
#include <string.h>
#include <iostream>
#include <vector>
#include <array>

// Singleton, participants have pointer to Tui/Input?
class Section {
public:
	Section();
	Section(int sectionStart, int bodyLength);
	std::string getText(int index);
	void addText(std::string);
	void resetStart();
	int modifyStartIndex(std::string input);
	const std::vector<std::string> *getTexts();
	bool withinBounds(int row) const;

	int sectionStart;
	int bodyLength;
private:
	std::vector<std::string> texts;
	int startIndex;
};



class Tui {
public:
	enum TextType {
		TEXT, INPUT
	};

	Tui();
	void initialize();
	
	static std::string centerText(std::string, int length);
	static void debug(std::string text);

	Section *debugSection;
	Section *promptSection;
	static Tui tui;
	void printScreen();

private:
	void printBar();
	void printDottedHorizontal();
	void printMapXAxis();
	void setPrimeCoordinates(std::pair<int, int> coords);
	void printLeftSide(int row);
	void printRightSide(int row);
	void printLine(int row);
	void addOutputArg(std::string arg, TextType type);
	void resetArg(TextType type);
	void printRightSideHorizontalRow() const;

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
	std::string currentDebugFunction;

	
};
#endif