#ifndef Tui_HPP
#define Tui_HPP
#include <string.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <array>
#include <exception>
#include <iomanip>
#include <unordered_set>
#include <set>
#include "..\..\..\Support\Paths.h"

#define HIGH_REFRESH_
#include SECTION_HEADER

// Singleton, participants have pointer to Tui/Input?
class Tui {
public:
	enum TextType {
		TEXT, INPUT
	};

	Tui();
	void initialize();
	
	static std::string centerText(std::string, int length);
	static void debug(std::string text);
	static int sectionsNum;

	Section *debugSection;
	Section *promptSection;
	static Tui tui;
	void printScreen();

	bool printSection(const Section& section, int row);
	static int tuiFormat(std::string text);
	Section* getSection(char sectionNum);


private:
	void printBar() const;
	void printLeftDottedHorizontal() const;
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
	int tuiCols;
	int indentNum;

	std::string indent;

	int zoom;
	int cellWidth;
	int cellHeight;
	int sectionCols;

	int xAxisIndex;
	int yAxisIndex;
	std::pair<int, int> primeCoords;


	std::set<std::string> sectionNums;

	
};
#endif





/*
Sections :
- Map section
- Text section
- Input section

			==================================================================================================
			||		.		.		.		|							||			Debug Section (0)		||
			||		.		.		.		|							||==================================||
			||		.		.		.		|							||      Func Name   | frame |  ret  ||
			||		.		.		.		|							||------------------|---------------||
			||		.		.		.		|							|| 1.				|		|		||
			||		.		.		.		|							|| 2.				|		|		||
			||		.		.		.		|							|| 3.				|		|		||
			||		.		.		.		|							|| 4.				|		|		||
			||		.		.		.		|							||...				|		|		||
			||		.		.		.		|							||					|		|		||
			||------------------------(-1)--|---------------------------||====================================
			||		.		.		.		|							||					Input			||
			||		.		.		.		|							||====================================
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			|| 		.		.		.		|							||									||
			==================================================================================================

*/