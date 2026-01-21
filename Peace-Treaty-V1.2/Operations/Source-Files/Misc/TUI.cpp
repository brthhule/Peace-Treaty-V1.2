#include "..\..\..\Support\Paths.h"
#include TUI_HEADER



int Tui::sectionsNum = 2;

Tui Tui::tui;

Tui::Tui() {
	sectionNums = {};
	rows = 33;

	//Prev 134
	tuiCols = 180;
	mapCols = 82;
	indentNum = 2;
	indent = "";
	zoom = 4;
	cellWidth = 0;
	cellHeight = 0;
	xAxisIndex = 0;
	yAxisIndex = 0;

	sectionCols = tuiCols - mapCols - 5;
	// primeCoords = {};

	debugSection = new Section(
		0,
		1,
		3,
		"Debug call stack (1)",
		Section::Order::BACK_TO_FRONT,
		&sectionCols
	);
	promptSection = new Section(
		1,
		debugSection->sectionEnd + 1,
		10,
		"Prompt (2)",
		Section::Order::FRONT_TO_BACK,
		&sectionCols);

	sectionNums.insert("0"); // For for debug section
	sectionNums.insert("1"); // For prompt section
	sectionNums.insert("M"); // For map
}


void Tui::printBar() const  {
	std::cout << indent;
	for (int col = 0; col < tuiCols; col++) {
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
	row -= 2;

	std::cout << indent << "||";

	if (row == -1) {
		std::cout << Tui::centerText("Map (M)", mapCols - 3);
		return;
	}
	if (row == 0) {
		for (int col = 1; col <= mapCols - 3; col++) {
			std::cout << "~";
		}
		return;
	}

	if (row == cellHeight * zoom) {
		printMapXAxis();
	} else if (row % cellHeight == 0 && row != 0) {
		//Edge of province box
		printLeftDottedHorizontal();
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

void Tui::printRightDottedHorizontal() const {
	int rowLength = tuiCols - 3 - mapCols;
	for (int i = 0; i < rowLength; i++) {
		std::cout << "~";
	}
	return;
}

std::string Tui::centerText(std::string text, int length) {
	if (text.length() >= length) {
		return text;
	}

	int leftPadding = length - (int) text.length();
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

/// <summary>
///		Prints out a section's text values
/// </summary>
/// <param name="section">const reference to a section</param>
/// <param name="row">the row number for a particular line</param>
/// <returns>
///		true - The row within the bounds of the section arg, printing occurs
///		false - the row is not within the section's bounds, no printing happens
/// </returns>
bool Tui::printSection(const Section& section, int row) {
	if (!section.withinSection(row)) {
		return false;
	}

	int rowLength = tuiCols - 3 - mapCols;

	if (row == section.sectionStart) {
		std::cout << Tui::centerText(section.title, rowLength);
	}

	else if (section.withinBody(row)) {
		int bodyStart = section.sectionStart + 2;
		const std::string currText = section.getCurrentText();
		int listNumber = row - bodyStart + 1;
		std::cout << std::setw(2) << listNumber << ". \033[35m" << currText << "\033[0m";

		int rightPadding = rowLength - (int) currText.size() - 4;
		for (int space = 0; space < rightPadding; space++) {
			std::cout << " ";
		}
	}

	else if (row == section.sectionStart + 1 || row == section.sectionEnd) {
		printRightDottedHorizontal();
	}

	else {
		std::cout << "Something went wrong; out of bounds";
		return false;
	}

	return true;
}

/// <summary>
///		Print the right side of the screen
/// </summary>
/// <param name="row">The row number for a particular line</param>
void Tui::printRightSide(int row) {
	int rowLength = tuiCols - 3 - mapCols;
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








/// @brief Determines whether a user's input is intended to modify the TUI interface.
///	
/// If the TUI is meant to be modified, any action is enacted accordingly
///	
/// @param The user's text input
/// 
/// @return A status of whether the TUI has been updated based on the input
///		0 - the TUI is modified as intended
///		1 - Length of the user's input isn't 2 or 3
///		2 - The section number is invalid/section could not be found
///		3 - The second character is not '+' or '-'
///		5 - If thre are 3 characters, the third character is not a number
int Tui::tuiFormat(std::string text) {
	int length = (int) text.length();

	if (length != 2 && length != 3) {
		return 1;
	}

	Section* section = tui.getSection(text.at(0));

	if (section == nullptr) { 
		return 2;
	}
	
	if (text.at(1) != '+' && text.at(1) != '-') {
		return 3;
	}

	// Determines whether we start at the start or end of a section's texts
	Section::Direction direction = Section::UP;
	if (text.at(1) == '-') {
		direction = Section::DOWN;
	}

	int amount = 0;
	if (text.length() == 2) {
		amount = 1;
	} else if ((text.at(2) != '+' && text.at(2) != '-')) {
		try {
			amount = std::stoi(text.at(2) + "");
		}
		catch (std::invalid_argument const& ex) {
			return 5;
		}
	}

	section->modifyStartIndex(amount, direction); 
	return true;
}


/// @brief Returns a pointer to a Section based on a sectionNumber
/// 
/// Each section corresponds to a diferent part of the TUI
/// There are three sections:
/// 1) Map section
/// 2) Debugging section
/// 3) Prompt section
/// TODO: Add case for map section
/// 
/// @param the character representing a particular section
/// @return Section* if the sectionNum arg is valid, nullptr if arg is invalid
Section* Tui::getSection(char sectionNum) {
	switch (sectionNum) {
		case '1': 
			return debugSection;
			break;
		case '2':
			return promptSection;
			break;
		case 'M':
			//return 
			return nullptr;
			break;
		default:
			return nullptr;
	}
}

/// @brief Prints out the TUI
/// 
/// has optionality to clear screen before printing out the new TUI
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

	std::string guide = "Input \"[section num][num][+/-]\" to navigate a section. Enter \"GUIDE\" to access an extended guide.";
	std::cout << indent;
	std::cout << "||";
	std::cout << Tui::centerText(guide, tuiCols - 4);
	std::cout << "||\n";


	printBar();
	// Information for debugText
	int rowLength = tuiCols - 3 - mapCols;

	// Print all rows
	debugSection->increment = 0;
	promptSection->increment = 0;
	
	for (int row = 1; row <= rows; row++) {
		debugSection->detCurrentText(row);
		promptSection->detCurrentText(row);
		printLine(row);
	}
	printBar();
}

///	@brief Prints a dotted horizontal line on the left side of the screen (x-axis)
void Tui::printLeftDottedHorizontal() const  {
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

/// @brief Initializes sizes for the TUI
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
}

/// @brief Adds text to the debug section of the screen
void Tui::debug(std::string text) {
	Tui::tui.debugSection->addText(text);
#ifdef HIGH_REFRESH
	Tui::tui.printScreen();
#endif
}