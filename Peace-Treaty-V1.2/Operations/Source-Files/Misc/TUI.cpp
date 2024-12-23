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
Section::Section(int sectionStart, int bodyLength, std::string title, Order order, int* width) {
	this->startIndex = 0;
	this->bodyLength = bodyLength;
	this->sectionStart = sectionStart;
	this->texts = {};
	// Plus 2 for the lines after the section header and after the body
	this->sectionEnd = sectionStart + bodyLength + 2;
	this->title = title;
	this->textsOrder = order;
	this->rightSideTextWidth = width;
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

void Section::addText(std::string text) {
	std::cout << "Text: " << text << "\n";
	std::cout << "rightSideTextWidth: " << rightSideTextWidth << "\n";
	if (textsOrder == BACK_TO_FRONT || text.length() <= *rightSideTextWidth) {
		std::cout << "Emplace back text\n";
		texts.emplace_back(text);
		return;
	}

	std::string firstPortion = text.substr(0, *rightSideTextWidth);
	texts.emplace_back(firstPortion);
	addText(text.substr(*rightSideTextWidth));
}

bool Section::withinSection(int row) const {
	bool frontBound = row >= sectionStart;
	bool backBound = row <= sectionEnd;
	return frontBound && backBound;
}

bool Section::withinBody(int row) const {
	int bodyStart = this->sectionStart + 2;
	bool frontBound = row >= bodyStart;
	bool backBound = row < bodyStart + bodyLength;
	return (frontBound && backBound);
}



Section::Section() : Section(0, 0, "", Order::FRONT_TO_BACK, nullptr) {
	
}

void Section::clearTexts() {
	texts.clear(); 
}
Tui Tui::tui;

Tui::Tui() {


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
	rightSideTextWidth = cols - 3 - mapCols - 4;
	// primeCoords = {};

	debugSection = new Section(
		1,
		3,
		"Debug call stack (0)",
		Section::Order::BACK_TO_FRONT,
		&rightSideTextWidth
	);
	promptSection = new Section(
		debugSection->sectionEnd + 1,
		10,
		"Prompt (1)",
		Section::Order::FRONT_TO_BACK,
		&rightSideTextWidth);
	
}


void Tui::printBar() const  {
	std::cout << indent;
	for (int col = 0; col < cols; col++) {
		std::cout << "=";
	}
	std::cout << "\n";
}

void Tui::printMapXAxis() const {
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

bool Tui::printSection(const Section& section, int row) {
	if (!section.withinSection(row)) {
		return false;
	}

	int rowLength = cols - 3 - mapCols;

	if (row == section.sectionStart) {
		std::cout << Tui::centerText(section.title, rowLength);
	}

	else if (section.withinBody(row)) {
		int bodyStart = section.sectionStart + 2;
		const std::string currText = section.getCurrentText();
		int listNumber = row - bodyStart + 1;
		std::cout << std::setw(2)<< listNumber << ". \033[35m" << currText << "\033[0m"; 

		int rightPadding = rowLength - currText.size() - 4; 
		for (int space = 0; space < rightPadding; space++) { 
			std::cout << " ";
		}
	}

	else if (row == section.sectionStart + 1 || row == section.sectionEnd ) {
		printRightSideHorizontalRow();
	}

	else {
		std::cout << "Something went wrong; out of bounds";
		return false;
	}

	return true;
}


void Tui::printRightSide(int row) {
	int rowLength = cols - 3 - mapCols;
	bool sectionPrinted = false;

	// Print out debugText
	sectionPrinted = sectionPrinted || printSection(*debugSection, row); 
	sectionPrinted = sectionPrinted || printSection(*promptSection, row);


	if (!sectionPrinted) {
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

	printBar();

	// Information for debugText
	int rowLength = cols - 3 - mapCols;

	// Print all rows
	int increment = 0;
	for (int row = 1; row <= rows - 2; row++) {
		debugSection->detCurrentText(row, increment);
		promptSection->detCurrentText(row, increment);
		increment++;

		printLine(row);
	}
	printBar();
}

void Section::detCurrentText(int row, int increment) {
	if (!withinBody(row)) {
		return;
	}
	if (texts.empty()) {
		setCurrentText("");
		return;
	}
	int index = textsOrder == Section::Order::BACK_TO_FRONT ?
		texts.size() - increment - 1 : increment;
	setCurrentText(Tui::concatText(texts.at(index), *rightSideTextWidth));
}

void Section::setCurrentText(std::string text) {
	this->currentText = text;
}

const std::string &Section::getCurrentText() const {
	return currentText;
}

std::string Tui::concatText(std::string text, int length) {
	return text.substr(0, length);
}

void Tui::printDottedHorizontal() const  {
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
#ifdef HIGH_REFRESH
	Tui::tui.printScreen();
#endif
}