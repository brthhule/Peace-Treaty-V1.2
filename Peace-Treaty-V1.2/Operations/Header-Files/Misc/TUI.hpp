#ifndef Tui_HPP
#define Tui_HPP
#include <string.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <array>
#include <iomanip>

#define HIGH_REFRESH_

// Singleton, participants have pointer to Tui/Input?
class Section {
public:
	enum Order {
		FRONT_TO_BACK,
		BACK_TO_FRONT
	};

	Section();
	Section(int sectionStart, int bodyLength, std::string title, Order order, int* width);
	std::string getText(int index);
	void addText(std::string);
	void resetStart();
	int modifyStartIndex(std::string input);
	const std::vector<std::string> *getTexts();
	// Includes everythigng from section title to line below the body
	bool withinSection(int row) const;
	// Body does not include the horizontal lines above and below the body
	bool withinBody(int row) const;
	const std::string &getCurrentText() const;
	void setCurrentText(std::string);
	void clearTexts();
	void detCurrentText(int row, int increment);

	int *rightSideTextWidth;
	int sectionStart;
	int sectionEnd;
	int bodyLength;
	std::string title;
	bool textsOrder;

private:
	std::vector<std::string> texts;
	int startIndex;
	std::string currentText;
};



class Tui {
public:
	enum TextType {
		TEXT, INPUT
	};

	Tui();
	void initialize();
	
	static std::string centerText(std::string, int length);
	static std::string concatText(std::string, int length);
	static void debug(std::string text);

	Section *debugSection;
	Section *promptSection;
	static Tui tui;
	void printScreen();

	bool printSection(const Section& section, int row);

private:
	void printBar() const;
	void printDottedHorizontal() const;
	void printMapXAxis() const;
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
	int rightSideTextWidth;

	int xAxisIndex;
	int yAxisIndex;
	std::pair<int, int> primeCoords;
	std::vector <std::string> inputArgs;
	std::vector<std::string> textArgs;

	
};
#endif