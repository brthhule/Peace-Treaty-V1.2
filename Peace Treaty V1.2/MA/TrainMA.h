//TrainMA.h
//Interface
//Implemented by Participants.h

#ifndef TRAINMA_H
#define TRAINMA_H

#define TRAIN_MA

class TrainMA
{
public:
	virtual void 
		TrainMAFunction() = 0,
		TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops) = 0;
};

#endif

