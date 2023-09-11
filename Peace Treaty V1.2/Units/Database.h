#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>

//Units
#include "Participants.h"
#include "Provinces.h"
#include "CommanderPRofile.h"
#include "OtherFunctions.h"
#include "LinkedList.h"//might need to move Database up, out of Units, so it can have a larger scope


//Clase for an object that contians everything in the system/game
//Purpose: from now on, create 
class Database {
public:
	//Constructor
	Database();

	void createMap();
	void initializeParticipants(int totalPlayers, int humanPlayers);
	std::vector<Participants*> getParticipantsList ();
	void updateTurnResources();

private:
	OtherFunctions OF;
	std::vector<Participants> participantsList;
	std::unordered_map <int, Provinces*> provincesHH;
	std::vector <std::vector <Provinces>> provincesMap;
	int currentParticipantIndex;
	int turn = 1;
	int continentSize = 0;
	LinkedList provincesLL;
};

#endif