#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include MAP_HEADER

using namespace INF;
using namespace PROV;
using namespace COORD;
using namespace Input;

std::vector<std::vector<Provinces>> Map::mapVectors = std::vector<std::vector<Provinces>>{}; 
Map::ProvincesMap Map::mapMap = std::unordered_map<std::string, provSPTR>(); 

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
		for (int y = 0; x < INF::continentSize; y++, mapIndex++) {  
			Provinces newProvince(mapIndex, -1);
			mapIndex++;
			tempVector.push_back(newProvince);
		}
		mapVectors.push_back(tempVector);
	}

	for (std::vector<Provinces> provinceVector : mapVectors) { 
		for (int x = 0; x < (int) provinceVector.size(); x++) {
			Provinces* province = &provinceVector.at(x);
			mapMap[province->getName()] = std::make_shared<Provinces>(*province);
			delete province; 
		}
	}
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

	provSPTR currentProvince = std::make_shared<Provinces>(mapVectors.at(x).at(y)); 
	//If it's a capital province, 'C', if regular, 'P'
	char letter = (currentProvince->isCapital()) ? 'C' : 'P'; 
	constINT currentIndex = currentParticipantIndex; 
	constINT thisIndex = currentProvince->getParticipantIndex(); 

	//If current participant's province
	if (thisIndex == currentIndex){ INF::addColor(BLUE);}
	//Enemy province (any other participant)
	else if (thisIndex != 0) {INF::addColor(RED);}
	//Empty province
	else {letter = '0';}

	std::cout << letter << currentProvince->getCommandersNum();
	INF::addColor(RESET);
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

	if (coords.first < 0 || coords.first >= INF::continentSize) {
		return false;
	}
	if (coords.second < 0 || coords.second >= INF::continentSize) {
		return false;
	}

	return true;
}
