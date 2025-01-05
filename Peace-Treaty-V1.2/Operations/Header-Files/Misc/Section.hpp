#ifndef SECTION_H
#define SECTION_H

#include <string.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <array>
#include <unordered_map>
#include <iomanip>

// Parent class
class Section {
public:
	enum Order {
		FRONT_TO_BACK,
		BACK_TO_FRONT
	};
	enum Direction {
		UP, DOWN
	};

	static std::string substr(std::string, int length);

	Section();
	Section(int sectionNumber, int sectionStart, int bodyLength, std::string title, Order order, int* width);
	std::string getText(int index);
	void addText(std::string text);
	void resetStart();
	int modifyStartIndex(int amount, Direction direction);
	const std::vector<std::string>* getTexts();
	// Includes everythigng from section title to line below the body
	bool withinSection(int row) const;
	// Body does not include the horizontal lines above and below the body
	bool withinBody(int row) const;
	const std::string& getCurrentText() const;
	void setCurrentText(std::string);
	void clearTexts();
	void detCurrentText(int row);

	int* sectionCols;
	int sectionStart;
	int sectionEnd;
	int bodyLength;
	std::string title;
	bool textsOrder;
	int increment;
	int sectionNumber;


private:
	std::vector<std::string> texts;
	int startIndex;
	std::string currentText;
};











// Create debugSection because detCurrentText has a different format for debug
// debugSection also utilizes Function objects to keep track of the function call stack
class DebugSection : public Section {
public:
	// POD
	struct Functions {
		std::string functionText;
		int stackFrameNum;
		std::string retValue;
	};

	DebugSection(int sectionNumber, int sectionStart, int bodyLength, std::string title, Order order, int* width);

	void addText(std::string text);

	static int currentStackFrame;

private:
	std::vector<Functions> functions;
	std::unordered_map<std::string, Functions> functionsMap;
}; 




#endif