#ifndef BARRACKS_H
#define BARRACKS_H

#include "..\..\..\..\..\..\Support\Paths.h"
#include BUILDINGS_BASE_HEADER

class Barracks : public BuildingsBASE {
public:
	Barracks();
	~Barracks(){}
	INF::constINT getTroopsTrainedThisTurn();
	void resetTroopsTrainedThisTurn();
	void addTroopsTrainedThisTurn(int amount);
private:
	int troopsTrainedThisTurn;
};

#endif