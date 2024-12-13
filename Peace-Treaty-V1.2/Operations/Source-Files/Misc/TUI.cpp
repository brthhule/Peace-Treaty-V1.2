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
DebugFunctions::DebugFunctions() {
	functions = {"", "", ""};
	startIndex = 0;
}

void DebugFunctions::resetStart() {
	startIndex = 0;
}

std::array<std::string, 3> DebugFunctions::getFunctions() {
	std::array<std::string, 3> returnArray{"", "", ""};
	for (int i = 0; i < 3; i++) {
		returnArray[i] = getFunction(startIndex + i);
	}
	return returnArray;

}

int DebugFunctions::modifyStartIndex(std::string input) {
	char inputChar = toupper(input.at(0));
	// Move up
	if (inputChar == 'P') {
		if (startIndex != 0) {
			startIndex--;
			return 0;
		}
	}
	else if (inputChar == 'L') {
		if (startIndex < functions.size() - 1) {
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

std::string DebugFunctions::getFunction(int index){
	if (index >= functions.size()) {
		return "";
	}
	return functions[index];
}

void DebugFunctions::addFunction(std::string function) {
	functions.emplace_back(function);
}

TUI TUI::tui;

TUI::TUI() {
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


void TUI::printBar() {
	std::cout << indent;
	for (int col = 0; col < cols; col++) {
		std::cout << "=";
	}
	std::cout << "\n";
}

void TUI::printMapXAxis() {
	for (int i = 0; i < mapCols - 3; i++) {
		std::cout << "-";
	}
}

void TUI::setPrimeCoordinates(std::pair<int, int> coords) {
	primeCoords = coords;
}

void TUI::printLeftSide(int row) { 
	std::cout << indent << "||";
	if (row == cellHeight * zoom) { 
		printMapXAxis();
	} else if (row % cellHeight == 0 && row != 0) {
		//Edge of province box
		printDottedHorizontal();
	} else {
		int cellsSinceBorder = 0;

		int yDisplacement = 4 * (cellHeight + 1);
		yDisplacement -=  row / (cellHeight + 1);
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

void TUI::printRightSide(int row) {
	int length = cols - 3 - mapCols;
	std::array<std::string, 3> debugFunctions = this->debugFunctions.getFunctions();
	for (int i = 0; i < 3; i++) {
		if (debugFunctions[i].size() - 3 >= length) {
			debugFunctions[i] = debugFunctions[i].substr(0, length - 4);
		}
	}

	if (row < 4) {
		std::cout << row << ". " << debugFunctions[row-1];
		for (int space = 0; space < length - debugFunctions[row -1].size(); space++) {
			std::cout << space;
		}
		std::cout << "||\n";
		return;
	}

	if (row == 4) {
		for (int i = 0; i < length; i++) {
			std::cout << "-";
		}
		std::cout << "||\n";
		return;
	}

	for (int i = 0; i < length; i++) {
		std::cout << " ";
	}
	std::cout << "||\n";
}

void TUI::printLine(int row) {
	printLeftSide(row); 
	//Middle barrier
	std::cout << "||"; 
	printRightSide(row); 
}

void TUI::printScreen() {
	std::cout << "cell height: " << cellHeight << "\n";
	std::cout << "YAxisIndex: " << yAxisIndex << "\n";

	printBar();

	// Print all rows
	for (int row = 1; row <= rows - 2; row++) {
		// At halfway, print out axis
		printLine(row);
	}
	printBar();
}

void TUI::printDottedHorizontal() {
	for (int col = 0; col < mapCols - 3; col++) {
		// Print Y axis halfway thru map
		if (col == yAxisIndex) {
			std::cout << "|";
		} 
		// Print dotted line, spread dots out so not cluttered
		else if (col % 3 == 0) {
			std::cout << ".";
		} 
		else {
			std::cout << " ";
		}		
	}
}

void TUI::addOutputArg(std::string arg, TextType type) { 
	// If TEXT type
	if (type) {
		textArgs.emplace_back(arg);
		return;
	}
	inputArgs.emplace_back(arg); 
}

void TUI::resetArg(TextType type) {
	if (type) {
		textArgs.clear();
		return;
	}
}

void TUI::initialize() { 
	for (int i = 0; i < indentNum; i++) {
		indent += "\t";
	}
	cellHeight = (rows - 1) / (zoom * 2); 
	cellWidth = (mapCols - 7) / (zoom * 2);
	yAxisIndex = (cellWidth * 4) + 3;
	xAxisIndex = (cellWidth * 4) + 1;

	std::cout << "cellHeight: " << cellHeight << "\n";
	std::cout << "cellWidth: " << cellWidth << "\n";
}

