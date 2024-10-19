#include "..\..\..\..\..\..\Support\Paths.h"

#include BARRACKS_HEADER  
#include BUILDINGS_BASE_HEADER

Barracks::Barracks() : BuildingsBASE({ 1, 1, 1, 1, 0.2 }) {  
	troopsTrainedThisTurn = 0;  
}

INF::constINT Barracks::getTroopsTrainedThisTurn() { 
	return troopsTrainedThisTurn;
}

void Barracks::resetTroopsTrainedThisTurn() {
	troopsTrainedThisTurn = 0;
}

void Barracks::addTroopsTrainedThisTurn(int amount) {
	troopsTrainedThisTurn += amount;
}