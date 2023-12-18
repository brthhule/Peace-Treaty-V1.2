#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include MAP_HEADER

Map::ProvincesVector Map::map = std::vector<std::vector<provSPTR>>{};
Map::ProvincesMap Map::mapMap = std::unordered_map<std::string, provSPTR>();


void Map::setMap() {
	//For debugging
	INF::debugFunction("Map, setMap");

	int overallIndex = 0;
	for (int x = 0; x < INF::continentSize; x++) {
		std::vector<provSPTR> tempVector = {};
		for (int y = 0; x < INF::continentSize; y++) {
			provSPTR newProvince = new Provinces(overallIndex);
			newProvince->setOverallIndex(overallIndex);
			overallIndex++;
			tempVector.push_back(newProvince);
			mapMap[newProvince->getUnitName()] = newProvince;
		}
		map.push_back(tempVector);
	}
}

void Map::showMap() {
	//For debugging
	INF::debugFunction("Map, showMap");

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
	INF::debugFunction("Map, meat");

	provSPTR currentProvince = map.at(x).at(y); 
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
	INF::debugFunction("Map, printXAxis");

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
	INF::debugFunction("Map, updateTurnResources");

	INF::debugFunction("main, updateTurnResources");
	for (int x = 0; x < INF::continentSize; x++) {
		for (int y = 0; y < INF::continentSize; y++) {
			map[x][y]->updateProvinceResources();
		}
	}
}



PROV::provSPTR Map::getProvince(CoordsType type, ipair coords) {
	if (type == SYSTEM) {
		return map.at(coords.first).at(coords.second);
	}

	//Ugly-- fix optomize this
	for (int row = 0; row < INF::continentSize; row++) {
		for (int col = 0; col < INF::continentSize; col++) {
			if (map[row][col]->getCoords(CoordsBASE::USER) == userCoords) {
				return map[row][col];
			}
		}
	}

	//Should never happen assuming the province exists
	return nullptr;
}
