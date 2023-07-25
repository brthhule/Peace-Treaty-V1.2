#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include <iostream>
#include <cmath>

#include "MA/ArmyOverviewMA.h"
#include "MA/BuildMA.h"
#include "MA/TrainMA.h"
#include "MA/MapMA.h"


#include "Misc/OtherFunctions.h"
#include "Misc/showText.h"
#include "Units/Participants.h"

class PlayerAction
{
public:
	PlayerAction();
	PlayerAction(Participants *newP);
	char randomAction();
	void initialDecision();
	void pauseGame();
private:
	Participants *participant;
	OtherFunctions OF;
};

#endif