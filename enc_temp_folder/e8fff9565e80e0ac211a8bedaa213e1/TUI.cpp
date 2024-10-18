#include "C:\Users\Darren Zheng\source\repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
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
	std::cout << indent << "||";
	for (int col = 0; col < cols - 4; col++) {
		if (col < mapCols) {
			std::cout << "-";
		} else if (col == mapCols) {
			std::cout << "||";
			col++;
		} else {
			std::cout << " ";
		}
		
	}
	std::cout << "||";
}

void TUI::printScreen() {
	int mapHorizons = rows / ( 2 * zoom);

	int currentHorizon = mapHorizons;
	
	std::cout << "cell height: " << cellHeight << "\n";

	printBar();
	

	// Print all rows
	for (int row = 1; row <= rows - 2; row++) {
		// At halfway, print out axis
		if (row == cellHeight * zoom) {
			printMapXAxis();
		} else if (row % cellHeight == 0 && row != 0) {
			//Edge of province box
			printDottedHorizontal();
			currentHorizon += mapHorizons;
		} else {
			std::cout << indent << "||"; 
			for (int col = 1; col <= cols - 4; col++) {
				if (col < mapCols) {
					if (col % (cellWidth + 1) == 0 && col != 0) {
						std::cout << ".";
					} else {
						std::cout << " ";
					}
				}
				
				
			}
			std::cout << "||";
		}
		std::cout << "\n";
	}
	printBar();
}

void TUI::printDottedHorizontal() {
	int mapVerticals = (cols - mapCols) / (2 * zoom);

	std::cout << indent << "||";
	for (int col = 0; col < cols-2; col++) {
		//Within map
		if (col <= mapCols) {
			// Print Y axis halfway thru map
			if (col == yAxisIndex) {
				std::cout << "|";
			} 
			// Print dotted line, spread dots out so not cluttered
			else if (col % 4 == 0 || col % mapVerticals == 0) {
				std::cout << ".";
			} 
			else {
				std::cout << " ";
			}
		} 
		//Pint bars ending map section
		else if (col == mapCols + 1) {
			std::cout << "||";
			col++;
		}
		//Outside of map section
		else {
			std::cout << " ";
		}
	}
	std::cout << "||";
}

TUI::TUI() {
	// Not implemented
}

void TUI::initialize() { 
	
	for (int i = 0; i < indentNum; i++) {
		indent += "\t";
	}
	cellHeight = (rows - 1) / (zoom * 2); 
	cellWidth = (mapCols - 2) / (zoom * 2);
	yAxisIndex = (cellWidth * 4) + 1;
	xAxisIndex = (cellWidth * 4) + 1;

	std::cout << "cellHeight: " << cellHeight << "\n";
	std::cout << "cellWidth: " << cellWidth << "\n";
}