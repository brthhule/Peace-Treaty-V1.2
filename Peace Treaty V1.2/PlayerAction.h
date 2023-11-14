#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include <iostream>
#include <cmath>

#include "MA/ArmyOverviewMA.h"
#include "MA/TrainMA.h"
#include "MA/MapMA.h"


#include "Units/Misc/INF.h"
#include "Units/Participants.h"

extern int turn;

class PlayerAction
{
public:
	PlayerAction();
	PlayerAction(Participants *newP);
	char randomAction();

	void 
		initialDecision(),
		pauseGame();
private:
	Participants *participant;
};

#endif