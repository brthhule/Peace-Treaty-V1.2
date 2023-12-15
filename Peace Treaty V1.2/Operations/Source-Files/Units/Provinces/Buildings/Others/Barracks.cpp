#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include BARRACKS_HEADER 

Barracks::Barracks() : BuildingsBASE({ 1, 1, 1, 1, 0.2 }) { 
	troopsTrainedThisTurn = 0; 
}

const int& Barracks::getTroopsTrainedThisTurn() {
	return troopsTrainedThisTurn;
}