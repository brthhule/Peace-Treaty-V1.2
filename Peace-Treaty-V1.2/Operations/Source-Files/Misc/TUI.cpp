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

int TUI::rows = 33;
int TUI::cols = 134;
int TUI::mapCols = 82;
int TUI::indentNum = 2;
std::string TUI::indent = "";
int TUI::zoom = 4;
int TUI::cellWidth = 0;
int TUI::cellHeight = 0;
int TUI::xAxisIndex = 0;
int TUI::yAxisIndex = 0;

void TUI::printBar() {
	std::cout << indent;
	for (int col = 0; col < cols; col++) {
		std::cout << "=";
	}
	std::cout << "\n";
}

void TUI::printMapXAxis() {
	for (int i = 0; i < mapCols; i++) {
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
		for (int col = 1; col <= mapCols; col++) {
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
	int length = cols - 6 - mapCols;
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
	for (int col = 0; col < mapCols; col++) {
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
		textArgs->emplace_back(arg);
		return;
	}
	inputArgs->emplace_back(arg);
}

void TUI::resetArg(TextType type) {
	if (type) {
		textArgs->clear();
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

