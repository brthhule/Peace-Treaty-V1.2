#pragma once
#include "ProvinceReport.h"

ProvinceReport::ProvinceReport(int scouterLevelArg,
	int targetLevelArg,
	std::array<std::array<int, 5>, 7> ListsArg,
	std::array<int, 7> listIntArg,
	std::array<bool, 3> listBoolArg,
	std::pair<int, int> listSystemCoordsArg) {

	scouterLevel = scouterLevelArg;
	targetLevel = targetLevelArg;

	computeAccuracy();

	Lists = ListsArg;
	listInt = listIntArg;
	listBool = listBoolArg;
	listSystemCoords = listSystemCoordsArg;

	attuneValues();

}


void ProvinceReport::computeAccuracy() {
	int bigger = 0;
	int smaller = 0;

	switch (scouterLevel > targetLevel)
	{
	case 0:
		bigger = targetLevel;
		smaller = scouterLevel;
		break;
	case 1:
		bigger = scouterLevel;
		smaller = targetLevel;
		break;
	}

	double divided = double(bigger) / smaller;
	divided = divided * 10;
	//Max accuracy: 95, min: 10
	//Accuracy starts at 50 by default-- same level = 50
	//If scouting a higher level target
	if (scouterLevel < targetLevel)
	{
		divided *= -1;
	}
	accuracy = 50 + int(divided);
	if (accuracy > 95) {
		accuracy = 95;
	}
	else if (accuracy < 5) {
		accuracy = 5;
	}
}

void ProvinceReport::attuneValues() {
	int newAccuracy = 100 - accuracy;
	int currentValue, mediumValue, upperValue, lowerValue;
	srand(time(NULL));

	for (int row = 0; row < 7; row++) {
		for (int col = 0; col < 5; col++) {
			currentValue = Lists[row][col];
			mediumValue = currentValue * (newAccuracy / 100);
			upperValue = currentValue + mediumValue;
			lowerValue = currentValue - mediumValue;
			Lists[row][col] = rand() % (upperValue - lowerValue) + lowerValue;
		}

		//For listInt
		currentValue = listInt[row];
		mediumValue = currentValue * (newAccuracy / 100);
		upperValue = currentValue + mediumValue;
		lowerValue = currentValue - mediumValue;
		listInt[row] = rand() % (upperValue - lowerValue) + lowerValue;
	}
}

void ProvinceReport::printReport() {
	//Complete implementation here
}