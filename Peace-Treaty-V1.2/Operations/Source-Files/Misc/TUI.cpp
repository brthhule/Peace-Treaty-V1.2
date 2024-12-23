#include "..\..\..\Support\Paths.h"
#include TUI_HEADER


/*
Sections :
- Map section
- Text section
- Input section

			==================================================================================================
			||		.		.		.		|							||					Text			||
			||		.		.		.		|							||==================================||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
			||		.		.		.		|							||									||
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
Section::Section(int sectionStart, int bodyLength) {
	this->startIndex = 0;
	this->bodyLength = bodyLength;
	this->sectionStart = sectionStart;
	for (int i = 0; i < bodyLength; i++) {
		texts.emplace_back("NA");
	}
}

void Section::resetStart() {
	startIndex = 0;
}

const std::vector<std::string> *Section::getTexts() {
	return &texts;
}

int Section::modifyStartIndex(std::string input) {
	char inputChar = toupper(input.at(0));
	// Move up
	if (inputChar == 'P') {
		if (startIndex != 0) {
			startIndex--;
			return 0;
		}
	} else if (inputChar == 'L') {
		if (startIndex < texts.size() - 1) {
			startIndex++;
			return 0;
		}
	}
	// If input is not valid
	else {
		return 1;
	}
	// If startIndex could not be modified
	return 2;
}

std::string Section::getText(int index) {
	if (index >= texts.size()) {
		return "";
	}
	return texts[index];
}

void Section::addText(std::string function) {
	texts.emplace_back(function); 
}

bool Section::withinBounds(int row) const {
	int sectionStart = this->sectionStart + 2;
	bool frontBound = row >= sectionStart;
	bool backBound = row < sectionStart + bodyLength;
	return (frontBound && backBound);
}



Section::Section() : Section(0, 0) {
	
}

Tui Tui::tui;

Tui::Tui() {
	debugSection = new Section(1, 3);
	promptSection = new Section(debugSection->sectionStart + debugSection->bodyLength + 3, 10);

	rows = 33;
	cols = 134;
	mapCols = 82;
	indentNum = 2;
	indent = "";
	zoom = 4;
	cellWidth = 0;
	cellHeight = 0;
	xAxisIndex = 0;
	yAxisIndex = 0;
	textArgs = {};
	inputArgs = {};
	// primeCoords = {};

	
}


void Tui::printBar() {
	std::cout << indent;
	for (int col = 0; col < cols; col++) {
		std::cout << "=";
	}
	std::cout << "\n";
}

void Tui::printMapXAxis() {
	for (int i = 0; i < mapCols - 3; i++) {
		std::cout << "-";
	}
}

void Tui::setPrimeCoordinates(std::pair<int, int> coords) {
	primeCoords = coords;
}

void Tui::printLeftSide(int row) {
	std::cout << indent << "||";
	if (row == cellHeight * zoom) {
		printMapXAxis();
	} else if (row % cellHeight == 0 && row != 0) {
		//Edge of province box
		printDottedHorizontal();
	} else {
		int cellsSinceBorder = 0;

		int yDisplacement = 4 * (cellHeight + 1);
		yDisplacement -= row / (cellHeight + 1);
		for (int col = 1; col <= mapCols - 3; col++) {
			if (col == yAxisIndex + 1) {
				std::cout << "|";
				cellsSinceBorder = 0;
			} else if (col % (cellWidth + 1) == 0) {
				std::cout << ".";
			} else {
				std::cout << " ";
			}
		}
	}
}

void Tui::printRightSideHorizontalRow() const {
	int rowLength = cols - 3 - mapCols;
	for (int i = 0; i < rowLength; i++) {
		std::cout << "-";
	}
	return;
}

std::string Tui::centerText(std::string text, int length) {
	if (text.length() >= length) {
		return text;
	}

	int leftPadding = length - text.length();
	leftPadding /= 2;
	int currentIndex = 0;
	std::string returnString = "";
	for (int i = 0; i < length; i++) {
		std::string letter = " ";
		if (i >= leftPadding && currentIndex < text.length()) {
			letter = text.at(currentIndex);
			currentIndex++;
		}
		returnString.append(letter + "\0");
	}
	return returnString;

}

void Tui::printRightSide(int row) {
	int rowLength = cols - 3 - mapCols;

	if (row == debugSection->sectionStart) {
		std::cout << Tui::centerText("Debug call stack (0)", rowLength);
	} 
	// Print out debugText
	else if (debugSection->withinBounds(row)) { 
		int sectionStart = debugSection->sectionStart + 2;
		std::cout << row - sectionStart + 1 << ". \033[35m" << currentDebugFunction << "\033[0m";
		for (int space = 0; space < rowLength - currentDebugFunction.size() - 3; space++) {
			std::cout << " ";
		}
	} 
	
	else if (row == debugSection->sectionStart + 2 + debugSection->bodyLength ||
		row == debugSection->sectionStart + 1 ||
		row == promptSection->sectionStart + 1
		) {
		printRightSideHorizontalRow();
	}

	else if (row == promptSection->sectionStart) {
		std::cout << Tui::centerText("Action prompt (1)", rowLength);
	}

	//else if (promptSection->withinBounds(row)) { 
	//	int index = row - (promptSection->sectionStart + 1);
	//	// std::cout << 
	//}

	else {
		for (int i = 0; i < rowLength; i++) {
			std::cout << " ";
		}
	}
	std::cout << "||\n";
}

void Tui::printLine(int row) {
	printLeftSide(row);
	//Middle barrier
	std::cout << "||";
	printRightSide(row);
}

void Tui::printScreen() {
	//clear screen
	/*
	#ifdef _WIN32
		system("cls");
	#else 
		system("clear");
	#endif

	*/
	for (int i = 0; i < 5; i++) {
		std::cout << "\n";
	}
	

	printBar();

	// Information for debugText
	int rowLength = cols - 3 - mapCols;
	const std::vector<std::string> *debugText = this->debugSection->getTexts(); 

	// Print all rows
	int debugIncrement = 1;
	for (int row = 1; row <= rows - 2; row++) {
		if (debugSection->withinBounds(row)) {
			int index = debugText->size() - debugIncrement;
			debugIncrement++;
			currentDebugFunction = debugText->at(index).substr(0, rowLength - 4);
		}
		printLine(row);
	}
	printBar();
}

void Tui::printDottedHorizontal() {
	for (int col = 0; col < mapCols - 3; col++) {
		// Print Y axis halfway thru map
		if (col == yAxisIndex) {
			std::cout << "|";
		}
		// Print dotted line, spread dots out so not cluttered
		else if (col % 3 == 0) {
			std::cout << ".";
		} else {
			std::cout << " ";
		}
	}
}


void Tui::addOutputArg(std::string arg, TextType type) {
	// If TEXT type
	if (type) {
		textArgs.emplace_back(arg);
		return;
	}
	inputArgs.emplace_back(arg);
}

void Tui::resetArg(TextType type) {
	if (type) {
		textArgs.clear();
		return;
	}
}

void Tui::initialize() {
	for (int i = 0; i < indentNum; i++) {
		indent += "\t";
	}
	cellHeight = (rows - 1) / (zoom * 2);
	cellWidth = (mapCols - 7) / (zoom * 2);
	yAxisIndex = (cellWidth * 4) + 3;
	xAxisIndex = (cellWidth * 4) + 1;

	std::cout << "cellHeight: " << cellHeight << "\n";
	std::cout << "cellWidth: " << cellWidth << "\n";
	std::cout << "String : foobar\n";
	std::string newString = Tui::centerText("Foobar", 10);
	std::cout << "Formatted: \n" << newString;
}

void Tui::debug(std::string text) {
	Tui::tui.debugSection->addText(text);  
	Tui::tui.printScreen();
}