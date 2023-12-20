#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCE_REPORT_HEADER

ProvinceReport::ProvinceReport(int scouterLevelArg,
	int targetLevelArg,
	std::array<i5array, 7> ListsArg,
	std::array<int, 7> listIntArg,
	std::array<bool, 3> listBoolArg,
	ipair listSystemCoordsArg) {

	//For debugging
	DEBUG_FUNCTION("ProvinceReport, ProvinceReport");

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
	//For debugging
	DEBUG_FUNCTION("ProvinceReport, computeAccuracy");

	int bigger = 0;
	int smaller = 0;


	if (scouterLevel > targetLevel) {
		bigger = scouterLevel;
		smaller = targetLevel;
	} else {
		bigger = targetLevel;
		smaller = scouterLevel;
	}

	double divided = double(bigger) / smaller;
	divided = divided * 10;
	//Max accuracy: 95, min: 10
	//Accuracy starts at 50 by default-- same level = 50
	//If scouting a higher level target
	if (scouterLevel < targetLevel) {
		divided *= -1;
	}

	accuracy = 50 + int(divided);
	if (accuracy > 95) {
		accuracy = 95;
	} else if (accuracy < 5) {
		accuracy = 5;
	}
}

void ProvinceReport::attuneValues() {
	//For debugging
	DEBUG_FUNCTION("ProvinceReport, attuneValues");

	int newAccuracy = 100 - accuracy;
	int currentValue, mediumValue, upperValue, lowerValue;
	srand((unsigned) time(NULL));

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
	//For debugging
	DEBUG_FUNCTION("ProvinceReport, printReport");

	//Complete implementation here
}
int ProvinceReport::getReportTurn() {
	//For debugging
	DEBUG_FUNCTION("ProvinceReport, getReportTurn");

	return reportTurn;
}

int ProvinceReport::getAccuracy() {
	//For debugging
	DEBUG_FUNCTION("ProvinceReport, getAccuracy");

	return accuracy;
}

int ProvinceReport::getTargetLevel() {
	//For debugging
	DEBUG_FUNCTION("ProvinceReport, getTargetLevel");

	return targetLevel;
}

int ProvinceReport::getScouterLevel() {
	//For debugging
	DEBUG_FUNCTION("ProvinceReport, getScouterLevel");

	return scouterLevel;
}