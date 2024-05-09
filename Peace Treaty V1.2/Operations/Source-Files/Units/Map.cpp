#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include MAP_HEADER

using namespace INF;
using namespace PROV;
using namespace COORD;
using namespace Input;

prov2Vector Map::mapVectors = std::vector<std::vector<Provinces>>{}; 
provMAP Map::mapMap = std::unordered_map<std::string, provSPTR>(); 

Map::Map() {

}

Map::~Map() {

}

void Map::setMap() {
	//For debugging
	DEBUG_FUNCTION("Map.cpp", "setMap"); 

	int mapIndex = 0;
	for (int x = 0; x < INF::continentSize; x++) { 
		std::vector<Provinces> tempVector = {}; 
		for (int y = 0; y < INF::continentSize; y++, mapIndex++) {  
			Provinces newProvince(mapIndex, -1);
			tempVector.push_back(newProvince);
		}
		mapVectors.push_back(tempVector);
	}

	for (std::vector<Provinces> provinceVector : mapVectors) { 
		for (int x = 0; x < (int) provinceVector.size(); x++) {
			provSPTR province = make_provSPTR(provinceVector.at(x)); 
			mapMap.insert(std::make_pair(province->getName(), province));
			//mapMap's are originally created using mapIndex instead of name
			mapMap.erase(std::to_string(province->getMapIndex()));
		}
	}

	//Work out surrounding provinces
}

void Map::showMap() {
	//For debugging
	DEBUG_FUNCTION("Map.cpp", "showMap");

	//Can potentially add a lamda statement here to replace the inside of the for loop

	int yAxis = INF::continentSize;
	for (int x = 0; x < INF::continentSize; x++) {
		// Y axis stuff
		if (yAxis < 10) { std::cout << " " << yAxis << "| "; }
		else { std::cout << yAxis << "| "; }

		yAxis--;
		// End y axis stuff

		for (int y = 0; y < INF::continentSize; y++) { meat(x, y); }
		std::cout << std::endl;
	}
}

void Map::meat(int x, int y) {
	//For debugging
	DEBUG_FUNCTION("Map.cpp", "meat"); 

	const Provinces& currentProvince = mapVectors.at(x).at(y); 

	//If it's a capital province, 'C', if regular, 'P'
	char letter = (currentProvince.isCapital()) ? 'C' : 'P'; 
	constINT currentIndex = currentParticipantIndex; 
	constINT thisIndex = currentProvince.getParticipantIndex(); 

	//If current participant's province
	if (thisIndex == currentIndex){ LOG::addColor(LOG::BLUE);} 
	//Enemy province (any other participant)
	else if (thisIndex != 0) {LOG::addColor(LOG::RED);}
	//Empty province
	else {letter = '0';}

std::cout << letter << currentProvince.getCommandersNum();
LOG::addColor(RESET);
}

void Map::printXAxis() {
	//For debugging
	DEBUG_FUNCTION("Map.cpp", "printXAxis");

	std::cout << "    ";//4 spaces
	for (int a = 0; a < INF::continentSize - 1; a++) {
		std::cout << "----";
	}
	std::cout << "--";
	std::cout << std::endl;
	std::cout << "    ";
	for (int a = 0; a < INF::continentSize; a++) {
		if (a < 9)
			std::cout << a + 1 << "   ";// 3 spaces
		else
			std::cout << a + 1 << "  ";//2 spaces
	}
	std::cout << "\n\n";
}



void Map::updateTurnResources() {
	//For debugging
	DEBUG_FUNCTION("Map.cpp", "updateTurnResources");

	for (int x = 0; x < INF::continentSize; x++) {
		for (int y = 0; y < INF::continentSize; y++) {
			mapVectors.at(x).at(y).updateProvinceResources();
		}
	}
}



PROV::provSPTR Map::getProvince(CoordsType type, ipair coords) {
	if (type == USER) {
		coords = CoordsBASE::translateCoords(coords, USER);
	}

	return std::make_shared<Provinces>(mapVectors.at(coords.first).at(coords.second));
}


ipair Map::pickCoords() {
	int xCoordinate, yCoordinate;
	xCoordinate = Input::getNumber("Enter an X Coordinate (-1 to cancel): ");
	yCoordinate = Input::getNumber("Enter a Y Coordinate (-1 to cancel): ");

	ipair userCoords = std::make_pair(xCoordinate, yCoordinate);

	if (checkInBounds(userCoords, USER) == false) {
		std::cout << getColor(RED) << "Coordinates out of bounds... please try again\n" << getColor(RESET);
		pickCoords();
	}

	if (xCoordinate == -1 || yCoordinate == -1) {
		return std::make_pair<int, int>(-1, -1);
	}

	return userCoords;
}

bool Map::checkInBounds(ipair coords, CoordsType type) {
	if (type == USER) {
		coords.first -= 1;
		coords.second -= 1;
	}

	return	(coords.first < 0 || coords.first >= INF::continentSize) ? false :
		(coords.second < 0 || coords.second >= INF::continentSize) ? false :
		true;

}


void Map::assignSurroundingProvinces() {
	//Set everything except boundary provinces
	for (int rowIndex = 1; rowIndex < mapVectors.size() - 1; rowIndex++) {
		for (int colIndex = 1; colIndex < mapVectors.at(0).size() - 1; colIndex++) {
			Provinces* currentProvince = &mapVectors.at(rowIndex).at(colIndex);
			assignSurroundingProvincesAux(rowIndex, colIndex, currentProvince);
		}
	}
}

void Map::assignSurroundingProvincesAux(int rowIndex, int colIndex, Provinces* currentProvince) {
	int count = 0;
	for (int outer = -1; outer <= 1; outer++) { 
		for (int inner = -1, inner <= 1; inner++) { 
			bool inBounds = checkInBounds(std::make_pair(rowIndex + outer, colIndex + inner));
			Provinces* relativeProvince = (inBounds) ? nullptr : &mapVectors.at(rowIndex + inner).at(colIndex + outer);
			currentProvince->setRelativeProvince((ProvinceRelation)count, relativeProvince);
			count++;
		}
	}
}