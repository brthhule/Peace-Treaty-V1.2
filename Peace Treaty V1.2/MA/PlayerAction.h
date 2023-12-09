//PlayeAction.h
//Interface
//Implemented by Participants.h

#ifndef PLAYERACTION_H
#define PLAYERACTION_H
#define PLAYER_ACTION

#include <iostream>
#include <cmath>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include ARMY_OVERVIEW_MA_HEADER
#include TRAIN_MA_HEADER
#include MAP_MA_HEADER
#include INF_HEADER
#include PARTICIPANTS_HEADER

class PlayerAction
{
public:
	char virtual randomAction() = 0;
	virtual void
		initialDecision() = 0,
		pauseGame() = 0;

};

#endif