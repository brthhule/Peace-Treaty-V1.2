#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include MAP_HEADER

Map::ProvincesVector Map::map = std::vector<std::vector<provSPTR>>{};
Map::ProvincesMap  Map::mapMap = std::unordered_map<std::string, provSPTR>();

Map::Map() {
	//For debugging
	INF::debugFunction("Map, Map");

}

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

	int yAxis = INF::continentSize;
	for (int x = 0; x < INF::continentSize; x++) {
		// Y axis stuff
		if (yAxis < 10)
			std::cout << " " << yAxis << "| ";
		else
			std::cout << yAxis << "| ";

		yAxis--;
		// End y axis stuff

		for (int y = 0; y < INF::continentSize; y++) {
			meat(x, y);
		}
		std::cout << std::endl;
	}
}

void Map::meat(int x, int y) {
	//For debugging
	INF::debugFunction("Map, meat");

	char letter = ' ';
	provSPTR currentProvince = map[x][y];

	//Player province
	if (currentProvince->getParticipantIndex() == currentParticipantIndex)
	{
		INF::addColor(BLUE);
		if (currentProvince->isCapital() == true)
			letter = 'C';
		else
			letter = 'p';
	}
	//Enemy province
	else if (currentProvince->getParticipantIndex() != -1)
	{
		INF::addColor(RED);
		if (currentProvince->isCapital() == true)
			letter = 'C';
		else
			letter = 'p';
	}
	//Empty province
	else {
		letter = '0';
	}

	std::cout << letter << currentProvince->getCommandersNum();
	//std::cout << "  ";
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

//Only for system coords
//First int should be row, second int should be column
provSPTR Map::getSystemProvince(ipair systemCoords) {
	//For debugging
	INF::debugFunction("Map, getSystemProvince");

	return map[systemCoords.first][systemCoords.second];
}


provSPTR Map::getUserProvince(ipair userCoords) {
	//For debugging
	INF::debugFunction("Map, getUserProvince");

	for (int row = 0; row < INF::continentSize; row++) {
		for (int col = 0; col < INF::continentSize; col++) {
			if (map[row][col]->getCoords(Coords::USER) == userCoords) {
				return map[row][col];
			}
		}
	}

	//This should never occur
	return NULL;
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