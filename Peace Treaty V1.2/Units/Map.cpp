#include "Map.h"

void Map::setMap() {
	int overallIndex = 0;
	for (int x = 0; x < CV::continentSize; x++) {
		std::vector<Provinces*> tempVector = {};
		for (int y = 0; x < CV::continentSize; y++) {
			Provinces *newProvince = new Provinces(overallIndex);
			newProvince->setOverallIndex(overallIndex);
			overallIndex++;
			tempVector.push_back(newProvince);
			mapMap[newProvince->getUnitName()] = newProvince;
		}
		map.push_back(tempVector);
	}
}

void Map::showMap() {
	int yAxis = CV::continentSize;
	for (int x = 0; x < CV::continentSize; x++) {
		// Y axis stuff
		if (yAxis < 10)
			std::cout << " " << yAxis << "| ";
		else
			std::cout << yAxis << "| ";

		yAxis--;
		// End y axis stuff

		for (int y = 0; y < CV::continentSize; y++) {
			meat(x, y);
		}
		std::cout << std::endl;
	}
}

void Map::meat(int x, int y) {
	char letter = ' ';
	Provinces* currentProvince = map[x][y];

	//Player province
	if (currentProvince->getParticipantIndex() == currentParticipantIndex)
	{
		CV::addColor(BLUE);
		if (currentProvince->isCapital() == true)
			letter = 'C';
		else
			letter = 'p';
	}
	//Enemy province
	else if (currentProvince->getParticipantIndex() != -1)
	{
		CV::addColor(RED);
		if (currentProvince->isCapital() == true)
			letter = 'C';
		else
			letter = 'p';
	}
	//Empty province
	else {
		letter = '0';
	}

	std::cout << letter << currentProvince->commandersNum();
	//std::cout << "  ";
	CV::addColor(RESET);
}

void Map::printXAxis() {
	std::cout << "    ";//4 spaces
	for (int a = 0; a < CV::continentSize - 1; a++) {
		std::cout << "----";
	}
	std::cout << "--";
	std::cout << std::endl;
	std::cout << "    ";
	for (int a = 0; a < CV::continentSize; a++) {
		if (a < 9)
			std::cout << a + 1 << "   ";// 3 spaces
		else
			std::cout << a + 1 << "  ";//2 spaces
	}
	std::cout << "\n\n";
}

//Only for system coords
//First int should be row, second int should be column
Provinces* Map::getSystemProvince(std::pair<int, int> systemCoords) {
	return map[systemCoords.first][systemCoords.second];
}
Provinces* Map::getUserProvince(std::pair<int, int> userCoords) {
	for (int row = 0; row < CV::continentSize; row++) {
		for (int col = 0; col < CV::continentSize; col++) {
			if (map[row][col]->getUserCoords() == userCoords) {
				return map[row][col];
			}
		}
	}

	//This should never occur
	return NULL;
}

void Map::updateTurnResources() {
	OF::debugFunction("main, updateTurnResources");
	for (int x = 0; x < CV::continentSize; x++) {
		for (int y = 0; y < CV::continentSize; y++) {
			map[x][y]->updateBuildingsProduction();
			map[x][y]->updateProvinceResources();
		}
	}
}