//PlayeAction.h
//Interface
//Implemented by Participants.h

#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include <iostream>
#include <cmath>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include ARMY_OVERVIEW_MA_HEADER		//Composition (Action)
#include MAP_MA_HEADER					//Composition (Action)
#include TRAIN_MA_HEADER				//Composition (Action)

#include PARTICIPANTS_HEADER			//Compositon (Unit)
#include INF_HEADER						//Utility

/* TODO
* Implement randomAction (AI functionality, way ahead)
* Take a look at pauseGame (I think it saves the data, not sure)
*/
class PlayerAction {
public:
	//----Constructors---------------------------------------------------------
	///Default constructor
	PlayerAction(){}
	///Destructor
	~PlayerAction(){}

	//----Methods--------------------------------------------------------------
	///Choose a random action (AI implementation)
	virtual char randomAction() = 0;
	///Player chooses an action to complete, recurses until end turn
	virtual void chooseAction() = 0;
	///Pauses the game-- ???
	virtual void pauseGame() = 0;

	//Shenanigans
	virtual void choosePauseGame() = 0;	
	virtual void showHelp() = 0;
	virtual void buildAction() = 0;
};

#endif