#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>

//Units
#include "Participants.h"
#include "Provinces.h"
#include "CommanderPRofile.h"
#include "../Misc/OF.h"
#include "../Misc/LinkedList.h"//might need to move Database up, out of Units, so it can have a larger scope
#include "Map.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

//constexpr int size = 10; // modern C++ same thing as #define SIZE 10



//Clase for an object that contians everything in the system/game
//Purpose: from now on, create 
class Database : public Map
{
public:
	//Constructor
	Database();

	void 
		createMap(),
		initializeParticipants(int totalPlayers, int humanPlayers),
		updateTurnResources(),
		setContinentSize(int num),
		setMaxCommanders(int num),
		setCurrentParticipant(Participants* p);

	
	std::vector<Participants>* getParticipantsList();
	
	int
		getContinentSize(),
		getMaxCommanders();

	Participants* getCurrentParticipant();

private:
	
	std::vector<Participants> participantsList;
	std::unordered_map <int, Provinces*> provincesUM;
	Participants* currentParticipant;

	int 
		currentParticipantIndex,
		continentSize,
		maxCommanders,
		pNum; //have to fix this; current points to nothing
};

#endif