#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCE_REPORT_HEADER

ProvinceReport::ProvinceReport(int scouterLevelArg,
	int targetLevelArg,
	std::array<i5array, 7> ListsArg,
	std::array<int, 7> listIntArg,
	std::array<bool, 3> listBoolArg,
	ipair listSystemCoordsArg) {

	//For debugging
	DEBUG_FUNCTION("ProvinceReport.cpp", "ProvinceReport");

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
	DEBUG_FUNCTION("ProvinceReport.cpp", "computeAccuracy");

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
	DEBUG_FUNCTION("ProvinceReport.cpp", "attuneValues");

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
	DEBUG_FUNCTION("ProvinceReport.cpp", "printReport");

	//Complete implementation here
}
const int ProvinceReport::getReportTurn() const {
	//For debugging
	DEBUG_FUNCTION("ProvinceReport.cpp", "getReportTurn");

	return reportTurn;
}

const int ProvinceReport::getAccuracy () const {
	//For debugging
	DEBUG_FUNCTION("ProvinceReport.cpp", "getAccuracy");

	return accuracy;
}

const int ProvinceReport::getTargetLevel() const{
	//For debugging
	DEBUG_FUNCTION("ProvinceReport.cpp", "getTargetLevel");

	return targetLevel;
}

const int ProvinceReport::getScouterLevel() const {
	//For debugging
	DEBUG_FUNCTION("ProvinceReport.cpp", "getScouterLevel");

	return scouterLevel;
}