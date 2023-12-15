//PlayeAction.h
//Interface
//Implemented by Participants.h

#ifndef PLAYERACTION_H
#define PLAYERACTION_H
#define PLAYER_ACTION

#include <iostream>
#include <cmath>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include ARMY_OVERVIEW_MA_HEADER
#include INF_HEADER
#include MAP_MA_HEADER
#include PARTICIPANTS_HEADER
#include TRAIN_MA_HEADER

class PlayerAction
	COMPRISES_
		ARMY_OVERVIEW_MA_
		TRAIN_MA_
		MAP_MA_
		PARTICIPANTS_
	USES_
		INF_
{

public:
	char virtual randomAction() = 0;
	virtual void
		initialDecision() = 0,
		pauseGame() = 0;

};

#endif