//PlayeAction.h
//Interface
//Implemented by Participants.h

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
	char virtual randomAction() = 0;
	void virtual
		initialDecision() = 0,
		pauseGame() = 0;

};

#endif